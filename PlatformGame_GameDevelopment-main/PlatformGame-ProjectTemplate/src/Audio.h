#pragma once

#include "Module.h"
#include <SDL3/SDL.h>
#include <vector>
#include <string>

#define DEFAULT_MUSIC_FADE_TIME 2.0f
#define MAX_SFX_CHANNELS 8

struct _Mix_Music;

class Audio : public Module
{
public:

    Audio();
    virtual ~Audio();

    bool Awake();
    bool CleanUp();

    // Play a music file
    bool PlayMusic(const char* path, float fadeTime = DEFAULT_MUSIC_FADE_TIME);

    // Load a WAV in memory
    int LoadFx(const char* path);

    // Play a previously loaded WAV with global FX volume
    bool PlayFx(int fx, int repeat = 0);

    // Play a previously loaded WAV with custom volume (0.0 to 1.0)
    bool PlayFx(int fx, float volume, int repeat = 0);

    // Set volume for music (0.0 to 1.0)
    void SetMusicVolume(float volume);

    // Set global volume for sound effects (0.0 to 1.0)
    void SetFxVolume(float volume);

    // Stop all sounds on SFX channels
    void StopAllFx();

private:

    struct SoundData {
        SDL_AudioSpec spec{};
        Uint8* buf{ nullptr };
        Uint32 len{ 0 };
    };

    struct SfxChannel {
        SDL_AudioStream* stream{ nullptr };
        bool inUse{ false };
    };

    // Device and default output format
    SDL_AudioDeviceID device_{ 0 };
    SDL_AudioSpec     device_spec_{};

    // Streams
    SDL_AudioStream* music_stream_{ nullptr };
    std::vector<SfxChannel> sfx_channels_;

    // Loaded sounds
    SoundData music_data_{};
    std::vector<SoundData> sfx_;

    // Volume controls (0.0 to 1.0)
    float music_volume_{ 1.0f };
    float fx_volume_{ 1.0f };

    // Helper functions
    bool LoadWavFile(const char* path, SoundData& out);
    void FreeSound(SoundData& s);
    bool EnsureDeviceOpen();
    bool EnsureStreams();
    int GetAvailableChannel();
};