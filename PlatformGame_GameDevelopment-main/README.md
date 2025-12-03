# Video Game Development – CITM UPC

This repository is part of the Video Game Development course at the
CITM (Center for Imaging and Multimedia Technology), Universitat Politècnica de Catalunya (UPC).

# 🎮 PlatformGame - Proyecto de Desarrollo de Videojuegos

Un juego de plataformas 2D completo desarrollado como proyecto de la asignatura de Desarrollo de Videojuegos. Este proyecto proporciona una base sólida para construir un juego de plataformas rico en características a través de tres asignaciones progresivas, integrando SDL3, física Box2D, soporte de mapas Tiled y sistemas de juego avanzados.

## 👥 Equipo de Desarrollo

**Grupo 4**:
- **Miembro 1**: Marc Pladellorens Pérez
- **Miembro 2**: Montserrat Medina Chávez

**Repositorio GitHub**: https://github.com/MarcPladellorensPerez/PlatformGame_GameDevelopment

---

## 🎯 Descripción del Juego

Un juego de plataformas 2D desafiante donde controlas a un personaje que debe superar obstáculos, evitar trampas mortales y recolectar monedas mientras navega por niveles llenos de peligros. El juego presenta mecánicas de movimiento fluidas con salto doble y dash, física realista mediante Box2D, y un sistema de checkpoints para guardar tu progreso.

---

## 🕹️ Cómo Jugar

### Controles Principales
- **W/A/S/D** - Movimiento del jugador
  - **A** - Mover a la izquierda
  - **D** - Mover a la derecha
  - **W** - (Modo Dios F10) Volar hacia arriba
  - **S** - (Modo Dios F10) Volar hacia abajo

- **SPACE** - Saltar
  - Primera pulsación: Salto simple
  - Segunda pulsación (en el aire): Salto doble

- **SHIFT + A/D** - Dash
  - SHIFT + A: Dash hacia la izquierda
  - SHIFT + D: Dash hacia la derecha
  - Cooldown: 500ms entre dashes

- **T** - Teletransportarse al punto de spawn/checkpoint activo

### Teclas de Debug (Desarrollo)
- **H** - Mostrar/Ocultar menú de ayuda
- **F9** - Visualizar colisionadores (debug)
- **F10** - Modo Dios (vuelo libre, invulnerabilidad)
- **F11** - Alternar límite de FPS (30/60)
- **ESC** - Salir del juego

### Teclas de Cámara (Debug)
- **Flechas** - Mover cámara manualmente
  - ⬆️ - Mover cámara arriba
  - ⬇️ - Mover cámara abajo
  - ⬅️ - Mover cámara izquierda
  - ➡️ - Mover cámara derecha

---

## ✨ Características Implementadas (Assignment 1)

### Sistema de Jugador
- ✅ **Movimiento fluido** con física Box2D
- ✅ **Sistema de animaciones** (idle, move, jump, death)
- ✅ **Salto doble** - Mecánica avanzada de movimiento
- ✅ **Dash** - Impulso rápido con cooldown
- ✅ **Cámara follow-up** que sigue al jugador
- ✅ **Sistema de muerte y respawn**
  - Muerte por caída fuera del mapa
  - Muerte por contacto con trampas/pinchos
  - Animación de muerte elaborada (flash + absorción + caída)
  - Pantalla "You Died" con fade-in
- ✅ **Sistema de checkpoints** - Puntos de guardado en el nivel
- ✅ **Modo Dios** para testing

### Física y Colisiones (Box2D)
- ✅ **Plataformas normales** - Colisiones sólidas
- ✅ **Plataformas one-way** - Se puede saltar a través desde abajo
- ✅ **Trampas de daño** - Pinchos que matan al jugador
- ✅ **Colisionadores dinámicos** creados desde capas del mapa TMX
- ✅ **Física realista** con gravedad y velocidad

### Sistema de Mapas
- ✅ **Carga de mapas TMX** desde Tiled Map Editor
- ✅ **Múltiples capas**:
  - Background (fondo con parallax)
  - Platforms (plataformas jugables)
  - Collisions (colisiones invisibles)
  - Damage (trampas mortales)
  - Objects (spawn points, checkpoints, items)
- ✅ **Background con repetición** para mapas largos
- ✅ **Sistema de spawn** desde objetos del mapa
- ✅ **Checkpoints** dinámicos desde el mapa

### Objetos y Entidades
- ✅ **Sistema de entidades** base con Entity Manager
- ✅ **Items coleccionables** (monedas)
  - Creación dinámica desde el mapa
  - Física circular con Box2D
  - Efecto de sonido al recolectar
- ✅ **Arquitectura extensible** para futuros enemigos

### Audio
- ✅ **Música de fondo** con control de volumen
- ✅ **Efectos de sonido**:
  - Salto del jugador
  - Dash
  - Recolección de monedas
  - Daño recibido
  - Muerte del jugador
- ✅ **Sistema de audio SDL3** con múltiples canales

### Sistema de Configuración
- ✅ **config.xml** - Configuración del engine
  - Resolución de ventana
  - FPS objetivo
  - VSync
- ✅ **player_config.xml** - Parámetros del jugador
  - Velocidad de movimiento
  - Fuerza de salto
  - Parámetros de dash
  - Rutas de texturas y audio
- ✅ **Animaciones desde TSX** de Tiled

### Optimización y Performance
- ✅ **FPS cap estable a 60 FPS** sin vsync
- ✅ **Delta time normalizado** - Movimiento consistente en diferentes máquinas
- ✅ **Título de ventana informativo**:
  ```
  FPS: 60 / Avg.FPS: 59.98 / Last-frame MS: 16.67 / Vsync: off
  ```
- ✅ **Sistema de timer** de alta precisión (PerfTimer)
- ✅ **Renderizado optimizado** por capas

### Herramientas de Debug
- ✅ **Menú de ayuda visual** (tecla H)
- ✅ **Visualización de colisionadores** (F9)
- ✅ **Modo Dios** con vuelo libre (F10)
- ✅ **Toggle de FPS cap** 30/60 (F11)
- ✅ **Sistema de logging** detallado
- ✅ **Teletransporte** para testing (T)

---

## 🏗️ Tecnologías y Bibliotecas

### SDL3
Acceso completo a las capacidades de SDL3:
- **Gráficos**: Renderizado 2D con soporte de backend GPU
- **Input**: Soporte de teclado, ratón y gamepad
- **Audio**: Reproducción de música y efectos de sonido
- **Ventana**: Múltiples ventanas, soporte de pantalla completa
- **Archivos**: Operaciones de archivos multiplataforma
- **Threading**: Soporte multihilo

### Box2D Physics (v3.1.1+)
Simulación de física 2D realista:
- Dinámica de cuerpos rígidos
- Detección y respuesta de colisiones
- Sistema de joints y constraints
- Detección continua de colisiones (CCD)
- Broad-phase collision eficiente

### Tiled Map Support
Integración de mapas TMX con pugixml:
- Renderizado de mapas ortográficos
- Soporte de múltiples capas
- Generación dinámica de colisionadores desde object layers
- Gestión de tilesets
- Soporte de propiedades personalizadas

### Características de Performance
- **Control de Frame Rate**: Cap estable de 60 FPS
- **Delta Time**: Normalización de movimiento
- **Toggle de VSync**: Control de vsync en tiempo de ejecución
- **Display de FPS**: Monitoreo de rendimiento en tiempo real

---

## 📁 Estructura del Proyecto

```
PlatformGame-ProjectTemplate/
├── src/                         # Código fuente (.cpp)
│   ├── Engine/                  # Sistema del motor
│   │   ├── Engine.cpp           # Core del motor
│   │   ├── Module.h             # Clase base de módulos
│   │   ├── Window.cpp           # Gestión de ventana
│   │   ├── Input.cpp            # Sistema de entrada
│   │   ├── Render.cpp           # Sistema de renderizado
│   │   ├── Textures.cpp         # Gestión de texturas
│   │   ├── Audio.cpp            # Sistema de audio SDL3
│   │   ├── Physics.cpp          # Integración Box2D
│   │   ├── Map.cpp              # Carga de mapas TMX
│   │   ├── EntityManager.cpp    # Gestor de entidades
│   │   └── Animation.cpp        # Sistema de animaciones
│   │
│   ├── Game/                    # Lógica del juego
│   │   ├── Scene.cpp            # Gestión de escenas
│   │   ├── Player.cpp           # Jugador con física
│   │   ├── Item.cpp             # Items coleccionables
│   │   └── Entity.h             # Clase base de entidades
│   │
│   ├── Utils/                   # Utilidades
│   │   ├── Log.cpp              # Sistema de logging
│   │   ├── Timer.cpp            # Timer de baja resolución
│   │   ├── PerfTimer.cpp        # Timer de alta precisión
│   │   └── Vector2D.cpp         # Matemáticas de vectores 2D
│   │
│   └── PlatformGame.cpp         # Punto de entrada
│
├── Assets/                      # Assets del juego
│   ├── Textures/                # Sprites y tilesets
│   │   ├── player2_spritesheet.png
│   │   ├── goldCoin.png
│   │   ├── playerDie1_spritesheet.png
│   │   ├── playerDie2_spritesheet.png
│   │   ├── you_died.png
│   │   ├── help_menu.png
│   │   └── player2_Spritesheet.tsx
│   │
│   ├── Maps/                    # Mapas Tiled
│   │   ├── MapTemplate.tmx
│   │   ├── decorative.png
│   │   ├── MapData2.png
│   │   ├── MapMetadata.png
│   │   ├── platforms.png
│   │   ├── tmw_desert_spacing.png
│   │   └── background1.png
│   │
│   ├── Audio/                   # Audio
│   │   ├── Music/
│   │   │   └── background_music.wav
│   │   └── Fx/
│   │       ├── coin_pickup.wav
│   │       ├── player_jump.wav
│   │       ├── player_dash.wav
│   │       ├── player_damage.wav
│   │       └── player_death.wav
│   │
│   └── Config/                  # Archivos de configuración
│       └── player_config.xml
│
├── config.xml                  # Configuración del engine
├── PlatformGame.sln            # Solución de Visual Studio
├── PlatformGame.vcxproj        # Proyecto de Visual Studio
├── vcpkg.json                  # Dependencias (vcpkg)
├── LICENSE                     # Licencia MIT
└── README.md                   # Este archivo
```

---

## 🚀 Compilación y Ejecución

### Requisitos Previos
- **Visual Studio 2022** (o superior)
- **vcpkg** (se instala automáticamente)
- **Windows 10/11** (x64)

### Pasos para Compilar

1. **Clonar el repositorio**:
   ```bash
   git clone [URL_DE_TU_REPO]
   cd PlatformGame-ProjectTemplate
   ```

2. **Abrir en Visual Studio**:
   - Abrir `PlatformGame.sln` con Visual Studio 2022
   - Visual Studio descargará automáticamente las dependencias via vcpkg

3. **Compilar**:
   - **Debug**: `Ctrl+Shift+B` o `Build > Build Solution`
   - **Release**: Cambiar a configuración `Release` y compilar

4. **Ejecutar**:
   - Presionar `F5` o `Debug > Start Debugging`
   - El ejecutable estará en `x64/Debug/` o `x64/Release/`

### Dependencias (automáticas via vcpkg)
- SDL3
- SDL3_image (con soporte PNG/JPEG)
- Box2D (v3.1.1+)
- pugixml
- libpng
- libjpeg-turbo

---

## 🐛 Problemas Conocidos

- Ninguno reportado actualmente

---

## 📚 Recursos de Aprendizaje

### Documentación Oficial
- **SDL3**: [SDL3 Wiki](https://wiki.libsdl.org/SDL3)
- **Box2D**: [Box2D Documentation](https://box2d.org/documentation/)
- **Tiled**: [Tiled Map Editor](https://doc.mapeditor.org/)

### Tutoriales y Guías
- **Diseño de Plataformas**: [The Guide to Implementing 2D Platformers](http://higherorderfun.com/blog/2012/05/20/the-guide-to-implementing-2d-platformers/)
- **Box2D Tutorials**: [iforce2d's Box2D Tutorials](https://www.iforce2d.net/b2dtut/)
- **Patrones de Arquitectura**: [Game Programming Patterns](https://gameprogrammingpatterns.com/)

### Recursos de Assets
- **Open Game Art**: [OpenGameArt.org](https://opengameart.org/)
- **Kenney Assets**: [kenney.nl](https://kenney.nl/assets)
- **itch.io**: [Game Assets on itch.io](https://itch.io/game-assets)

---

## 📄 Licencia

Este proyecto está licenciado bajo la Licencia MIT - ver el archivo [LICENSE](LICENSE) para más detalles.

**Copyright (c) 2025 MarcPladellorensPerez**


---

## 📞 Contacto

Para preguntas o problemas:
- **GitHub Issues**: https://github.com/MarcPladellorensPerez/PlatformGame_GameDevelopment/issues
- **Email**: marc.pladellorens@estudiantat.upc.edu o montserrat.medina@estudiantat.upc.edu

---

**Versión**: Alpha v0.1 (Assignment 1)  
**Última actualización**: Noviembre 2025