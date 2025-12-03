#include "Audio.h"
#include "Log.h"

Audio::Audio() {
    name = "audio";
}

Audio::~Audio() {

}

bool Audio::LoadWavFile(const char* path, SoundData& out) {
    if (!SDL_LoadWAV(path, &out.spec, &out.buf, &out.len)) {
        SDL_Log("SDL_LoadWAV failed for %s: %s", path, SDL_GetError());
        return false;
    }
    return true;
}

void Audio::FreeSound(SoundData& s) {
    if (s.buf) {
        SDL_free(s.buf);
        s.buf = nullptr;
        s.len = 0;
        s.spec = SDL_AudioSpec{};
    }
}

bool Audio::EnsureDeviceOpen() {
    if (device_ != 0) return true;

    SDL_AudioSpec want{};
    want.format = SDL_AUDIO_F32;
    want.channels = 2;
    want.freq = 48000;

    device_ = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &want);
    if (device_ == 0) {
        LOG("Audio: SDL_OpenAudioDevice failed: %s", SDL_GetError());
        return false;
    }

    if (!SDL_GetAudioDeviceFormat(device_, &device_spec_, nullptr)) {
        LOG("Audio: SDL_GetAudioDeviceFormat failed: %s", SDL_GetError());
        SDL_CloseAudioDevice(device_);
        device_ = 0;
        return false;
    }

    SDL_ResumeAudioDevice(device_);
    return true;
}

bool Audio::EnsureStreams() {
    if (!EnsureDeviceOpen()) return false;

    if (!music_stream_) {
        music_stream_ = SDL_CreateAudioStream(nullptr, &device_spec_);
        if (!music_stream_) {
            LOG("Audio: SDL_CreateAudioStream (music) failed: %s", SDL_GetError());
            return false;
        }
        if (!SDL_BindAudioStream(device_, music_stream_)) {
            LOG("Audio: SDL_BindAudioStream (music) failed: %s", SDL_GetError());
            SDL_DestroyAudioStream(music_stream_);
            music_stream_ = nullptr;
            return false;
        }
    }

    if (sfx_channels_.empty()) {
        sfx_channels_.resize(MAX_SFX_CHANNELS);
        for (size_t i = 0; i < sfx_channels_.size(); i++) {
            sfx_channels_[i].stream = SDL_CreateAudioStream(nullptr, &device_spec_);
            if (!sfx_channels_[i].stream) {
                LOG("Audio: SDL_CreateAudioStream (sfx channel %zu) failed: %s", i, SDL_GetError());
                return false;
            }
            if (!SDL_BindAudioStream(device_, sfx_channels_[i].stream)) {
                LOG("Audio: SDL_BindAudioStream (sfx channel %zu) failed: %s", i, SDL_GetError());
                SDL_DestroyAudioStream(sfx_channels_[i].stream);
                sfx_channels_[i].stream = nullptr;
                return false;
            }
            sfx_channels_[i].inUse = false;
        }
        LOG("Audio: Created %d SFX channels", MAX_SFX_CHANNELS);
    }

    return true;
}

int Audio::GetAvailableChannel() {
    int targetChannel = 0;
    int minBytesPending = SDL_GetAudioStreamAvailable(sfx_channels_[0].stream);

    for (size_t i = 0; i < sfx_channels_.size(); ++i) {
        int pending = SDL_GetAudioStreamAvailable(sfx_channels_[i].stream);

        if (!sfx_channels_[i].inUse && pending == 0) {
            return static_cast<int>(i);
        }

        if (pending < minBytesPending) {
            minBytesPending = pending;
            targetChannel = static_cast<int>(i);
        }
    }

    return targetChannel;
}

bool Audio::Awake() {
    LOG("Audio: initializing SDL3 audio");
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) != true) {
        LOG("SDL_INIT_AUDIO failed: %s", SDL_GetError());
        active = false;
        return true;
    }

    if (!EnsureDeviceOpen()) {
        active = false;
        return true;
    }

    return true;
}

bool Audio::CleanUp() {
    if (!active || !SDL_WasInit(SDL_INIT_AUDIO)) {
        music_stream_ = nullptr;
        sfx_channels_.clear();
        device_ = 0;
        sfx_.clear();
        FreeSound(music_data_);
        return true;
    }

    LOG("Audio: cleaning up");

    if (device_ != 0) SDL_PauseAudioDevice(device_);

    if (music_stream_) {
        SDL_DestroyAudioStream(music_stream_);
        music_stream_ = nullptr;
    }
    FreeSound(music_data_);

    for (auto& channel : sfx_channels_) {
        if (channel.stream) {
            SDL_DestroyAudioStream(channel.stream);
            channel.stream = nullptr;
        }
    }
    sfx_channels_.clear();

    for (auto& s : sfx_) FreeSound(s);
    sfx_.clear();

    if (device_ != 0) {
        SDL_CloseAudioDevice(device_);
        device_ = 0;
    }

    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    active = false;
    return true;
}

bool Audio::PlayMusic(const char* path, float fadeTime) {
    if (!active) return false;
    if (!EnsureStreams()) return false;

    if (music_stream_) {
        SDL_ClearAudioStream(music_stream_);
    }
    FreeSound(music_data_);

    if (!LoadWavFile(path, music_data_)) {
        LOG("Audio: cannot load music %s: %s", path, SDL_GetError());
        return false;
    }

    if (!SDL_SetAudioStreamFormat(music_stream_, &music_data_.spec, &device_spec_)) {
        LOG("Audio: SDL_SetAudioStreamFormat(music) failed: %s", SDL_GetError());
        return false;
    }

    SDL_SetAudioStreamGain(music_stream_, music_volume_);

    if (!SDL_PutAudioStreamData(music_stream_, music_data_.buf, music_data_.len)) {
        LOG("Audio: SDL_PutAudioStreamData(music) failed: %s", SDL_GetError());
        return false;
    }

    LOG("Audio: playing music %s at volume %.2f", path, music_volume_);
    return true;
}

int Audio::LoadFx(const char* path) {
    if (!active) return 0;
    if (!EnsureStreams()) return 0;

    SoundData s{};
    if (!LoadWavFile(path, s)) {
        LOG("Audio: cannot load fx %s: %s", path, SDL_GetError());
        return 0;
    }

    sfx_.push_back(s);
    LOG("Audio: loaded fx #%zu from %s", sfx_.size(), path);
    return static_cast<int>(sfx_.size());
}

bool Audio::PlayFx(int id, int repeat) {
    return PlayFx(id, fx_volume_, repeat);
}

bool Audio::PlayFx(int id, float volume, int repeat) {
    size_t index = static_cast<size_t>(id - 1);

    if (!active || index >= sfx_.size() || !EnsureStreams()) {
        return false;
    }

    const SoundData& soundEffect = sfx_[index];
    volume = (volume < 0.0f) ? 0.0f : (volume > 1.0f ? 1.0f : volume);

    int targetIdx = GetAvailableChannel();
    SfxChannel& targetChannel = sfx_channels_[targetIdx];

    SDL_ClearAudioStream(targetChannel.stream);

    if (SDL_SetAudioStreamFormat(targetChannel.stream, &soundEffect.spec, &device_spec_) < 0) {
        LOG("Audio: SDL_SetAudioStreamFormat failed on channel %d: %s", targetIdx, SDL_GetError());
        return false;
    }

    SDL_SetAudioStreamGain(targetChannel.stream, volume);

    int copiesToSend = repeat + 1;
    while (copiesToSend > 0) {
        if (SDL_PutAudioStreamData(targetChannel.stream, soundEffect.buf, soundEffect.len) < 0) {
            LOG("Audio: SDL_PutAudioStreamData failed on channel %d: %s", targetIdx, SDL_GetError());
            return false;
        }
        copiesToSend--;
    }

    targetChannel.inUse = true;
    return true;
}

void Audio::SetMusicVolume(float volume) {
    music_volume_ = (volume < 0.0f) ? 0.0f : (volume > 1.0f ? 1.0f : volume);

    if (music_stream_) {
        SDL_SetAudioStreamGain(music_stream_, music_volume_);
    }

    LOG("Audio: Music volume updated to %.2f", music_volume_);
}

void Audio::SetFxVolume(float volume) {
    fx_volume_ = (volume < 0.0f) ? 0.0f : (volume > 1.0f ? 1.0f : volume);
    LOG("Audio: Global FX volume updated to %.2f", fx_volume_);
}

void Audio::StopAllFx() {
    for (auto& sfxCh : sfx_channels_) {
        if (sfxCh.stream) {
            SDL_ClearAudioStream(sfxCh.stream);
            sfxCh.inUse = false;
        }
    }
    LOG("Audio: Stopped all FX streams");
}