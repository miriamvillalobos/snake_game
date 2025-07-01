# 🐍 Snake Game - Proyecto C++

Un juego clásico de Snake desarrollado en *C++* utilizando *SFML, implementando principios de **Programación Orientada a Objetos* con arquitectura modular y patrones de diseño.

![Snake Game](docs/screenshots/game_preview.png)

## 📋 Características Principales

- ✅ *Arquitectura Orientada a Objetos* con 6 clases principales
- ✅ *Gráficos 2D* usando sprites personalizados y SFML
- ✅ *Sistema de Audio* completo con música de fondo y efectos
- ✅ *Sistema de Puntuación* visual con números gráficos
- ✅ *Múltiples Pantallas* (inicio, juego, game over)
- ✅ *Controles Configurables* (WASD + Flechas)
- ✅ *Compilación con MinGW* en Windows y Linux
- ✅ *Sistema de Build* con Makefile
- ✅ *Migración completa a SFML* desde SDL2

## 🏗️ Arquitectura del Proyecto

### Clases Implementadas

1. *Game* - Controlador principal del juego
2. *Snake* - Lógica de la serpiente y movimiento
3. *Food* - Generación y manejo de comida
4. *GameRenderer* - Sistema de renderizado y gráficos
5. *AudioManager* - Gestión de música y efectos de sonido
6. *InputHandler* - Procesamiento de entrada del usuario

### Relaciones Implementadas

- *🔗 Composición (1..1)*: Game posee completamente todos los componentes
- *📦 Agregación (1..)**: Snake contiene múltiples segmentos Position
- *🤝 Asociación (0..1)*: InputHandler se comunica con Game

## 🗂️ Estructura del Proyecto


snake_game/
├── 📁 bin/                    # Ejecutables compilados
├── 📁 obj/                    # Archivos objeto (.o)
├── 📁 data/                   # Assets del juego
│   ├── 🖼️ images/            # Sprites y texturas
│   └── 🔊 music/             # Archivos de audio
├── 📁 docs/                   # Documentación
│   ├── 📊 DIAGRAMA_CLASES.md  # Diagrama de clases UML
│   ├── 📸 screenshots/        # Capturas de pantalla
│   └── 📖 BUILD_WINDOWS.md    # Guía de compilación
├── 📁 include/                # Archivos header (.hpp)
│   ├── 🎮 Game.hpp
│   ├── 🐍 Snake.hpp
│   ├── 🍎 Food.hpp
│   ├── 🎨 GameRenderer.hpp
│   ├── 🔊 AudioManager.hpp
│   └── ⌨️ InputHandler.hpp
├── 📁 src/                    # Código fuente (.cpp)
│   ├── main.cpp
│   ├── Game.cpp
│   ├── Snake.cpp
│   ├── Food.cpp
│   ├── GameRenderer.cpp
│   ├── AudioManager.cpp
│   └── InputHandler.cpp
├── 🔧 Makefile               # Sistema de build principal
├── 🔧 Makefile.windows       # Build específico para Windows
└── 📋 README.md              # Este archivo


## 🛠️ Instalación y Compilación

### Requisitos del Sistema

- *C++ 17* o superior
- *MinGW-w64* o Visual Studio con herramientas C++
- *SFML* Development Libraries (Graphics, Audio, System, Window)
- *Make* o *mingw32-make*

### 🪟 Windows (MinGW)

1. *Instalar MinGW-w64:*
   powershell
   # Usando Chocolatey
   choco install mingw
   
   # O descargar desde: https://www.mingw-w64.org/
   

2. *Instalar SFML (Opción A - vcpkg):*
   powershell
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   .\bootstrap-vcpkg.bat
   .\vcpkg install sfml
   

3. *Instalar SFML (Opción B - Manual):*
   - Descargar SFML Development Libraries desde [sfml-dev.org](https://www.sfml-dev.org/)
   - Extraer en C:\SFML\
   - Ajustar rutas en Makefile.windows

4. *Compilar el proyecto:*
   powershell
   # Clonar el repositorio
   git clone [URL_DEL_REPOSITORIO]
   cd snake_game
   
   # Compilar con assets
   make -f Makefile.windows build-all
   
   # Ejecutar
   make -f Makefile.windows run
   

### 🐧 Linux (Ubuntu/Debian)

1. *Instalar dependencias:*
   bash
   sudo apt-get update
   sudo apt-get install build-essential libsfml-dev
   

2. *Compilar y ejecutar:*
   bash
   # Clonar repositorio
   git clone [URL_DEL_REPOSITORIO]
   cd snake_game
   
   # Compilar con assets
   make build-all
   
   # Ejecutar
   make run
   

### 🍎 macOS

1. *Instalar dependencias:*
   bash
   # Usando Homebrew
   brew install sfml
   

2. *Compilar y ejecutar:*
   bash
   make build-all
   make run
   

## 🎮 Comandos de Make Disponibles

| Comando | Descripción |
|---------|-------------|
| make o make all | Compilar el proyecto |
| make debug | Compilar en modo debug |
| make clean | Limpiar archivos generados |
| make copy-assets | Copiar assets al directorio build |
| make build-all | Build completo con assets |
| make run | Ejecutar el juego |
| make check-deps | Verificar dependencias |
| make rebuild | Limpiar y recompilar todo |

## 🎯 Cómo Jugar

### Controles

| Tecla | Acción |
|-------|--------|
| *W* / *↑* | Mover arriba |
| *S* / *↓* | Mover abajo |
| *A* / *←* | Mover izquierda |
| *D* / *→* | Mover derecha |
| *ESPACIO* / *ENTER* | Iniciar juego / Reiniciar |
| *P* | Pausar juego |
| *ESC* | Salir del juego |

### Objetivo
1. 🎯 *Controla la serpiente* para comer la comida roja
2. 📈 *Crece* cada vez que comes y gana puntos
3. ⚠️ *Evita* chocar con las paredes o contigo mismo
4. 🏆 *Alcanza* la puntuación más alta posible

## 📊 Assets del Juego

### 🖼️ Imágenes (data/images/)
- fondo.jpg - Fondo del juego
- pantalla de inicio.jpg - Pantalla de inicio  
- pantalla final.jpg - Pantalla de game over
- cabeza.png - Cabeza de la serpiente
- frontal.png, trasera.png, izquierda.png, derecha.png - Cabezas direccionales
- cuerpo.png - Segmento del cuerpo
- segmento.png - Segmento de la cola
- comida.png - Comida
- cero.png a nueve.png - Números para el marcador

### 🔊 Audio (data/music/)
- musica_fondo.wav - Música de fondo del juego
- inicio.wav - Sonido de inicio
- comer.wav - Sonido al comer comida
- choque.wav - Sonido de colisión
- gameover.wav - Sonido de game over

## Desarrollo

### Nomenclatura Utilizada
- *PascalCase*: Clases, structs, enums (Game, Snake, Food, Direction)
- *camelCase*: Variables, funciones, métodos (currentDirection, hasGrown, GetHead())
- *UPPER_CASE*: Constantes (WINDOW_WIDTH, GRID_SIZE)

### Principios de Diseño
- *Encapsulamiento*: Miembros privados con getters/setters apropiados
- *Composición*: Game contiene y controla todos los componentes
- *Responsabilidad Única*: Cada clase tiene una función específica
- *Modularidad*: Separación clara entre lógica, renderizado y audio

### Patrones Implementados
- *Component Pattern*: Separación de responsabilidades en componentes
- *Observer Pattern*: Sistema de eventos para input
- *Strategy Pattern*: Diferentes estrategias de renderizado
- *RAII*: Gestión automática de recursos con smart pointers

## 📸 Capturas de Pantalla

### Pantalla de Inicio
![Pantalla de Inicio](docs/screenshots/start_screen.png)

### Jugando
![Gameplay](docs/screenshots/gameplay.png)

### Game Over
![Game Over](docs/screenshots/game_over.png)

## 📋 Funcionalidades Implementadas

- ✅ *Movimiento fluido* de la serpiente con validación de direcciones
- ✅ *Sistema de colisiones* (paredes y auto-colisión)
- ✅ *Generación aleatoria* de comida evitando la serpiente
- ✅ *Crecimiento dinámico* de la serpiente al comer
- ✅ *Sistema de puntuación* visual con sprites numéricos
- ✅ *Múltiples estados* del juego (inicio, jugando, game over, pausa)
- ✅ *Audio integrado* con música de fondo y efectos
- ✅ *Renderizado optimizado* con texturas y sprites
- ✅ *Controles responsivos* con mapeo configurable
- ✅ *Gestión de memoria* segura con smart pointers

## 🚀 Funcionalidades Avanzadas Futuras

- 🔄 *Sistema de niveles* con velocidad incremental
- 🏆 *Tabla de puntuaciones* persistente
- 🎨 *Temas visuales* intercambiables
- 🎵 *Múltiples pistas* de música
- 🔧 *Menú de configuración* para audio y controles
- 🕹️ *Soporte para joystick/gamepad*
- 📱 *Versión móvil* con controles táctiles

## 🧪 Testing y Validación

El proyecto ha sido probado en:
- ✅ *Windows 10/11* con MinGW-w64
- ✅ *Ubuntu 20.04+* con GCC
- ✅ *Diferentes resoluciones* de pantalla
- ✅ *Múltiples configuraciones* de SFML

## 🤝 Contribución

Este proyecto fue desarrollado como parte de un curso de *Programación Orientada a Objetos* implementando:

- *6 clases principales* con responsabilidades específicas
- *3 tipos de relaciones* (Composición, Agregación, Asociación)
- *Multiplicidad claramente definida* en las relaciones
- *Nomenclatura consistente* (PascalCase para clases, camelCase para métodos)
- *Código correctamente indentado* y documentado
- *Estructura de archivos organizada* (/bin, /docs, /data, /include, /src)
- *Makefile funcional* para compilación
- *Funcionalidad completa* del juego Snake

## 📄 Licencia

Este proyecto está desarrollado con fines educativos como parte de un curso de programación en C++.

---

*Desarrollado por:*  
*Curso:* 
*Fecha:* 
*Tecnologías:* C++17, SFML, MinGW