# Manual del Programador - Snake Game

## 📋 Tabla de Contenidos
1. [Introducción](#introducción)
2. [Arquitectura del Sistema](#arquitectura-del-sistema)
3. [Estructura del Proyecto](#estructura-del-proyecto)
4. [Dependencias y Tecnologías](#dependencias-y-tecnologías)
5. [Configuración del Entorno](#configuración-del-entorno)
6. [Compilación y Build](#compilación-y-build)
7. [Clases Principales](#clases-principales)
8. [Flujo de Ejecución](#flujo-de-ejecución)
9. [Sistema de Renderizado](#sistema-de-renderizado)
10. [Gestión de Audio](#gestión-de-audio)
11. [Manejo de Entrada](#manejo-de-entrada)
12. [Gestión de Recursos](#gestión-de-recursos)
13. [Patterns y Principios](#patterns-y-principios)
14. [Testing y Debugging](#testing-y-debugging)
15. [Extensiones y Mejoras](#extensiones-y-mejoras)
16. [API Reference](#api-reference)
17. [Troubleshooting](#troubleshooting)

## 🚀 Introducción

Este manual está dirigido a desarrolladores que deseen:
- **Entender** la arquitectura del juego Snake
- **Modificar** o **extender** la funcionalidad existente
- **Contribuir** al desarrollo del proyecto
- **Aprender** patrones de diseño en C++ y SFML

### Objetivos del diseño:
- **Modularidad**: Componentes independientes y reutilizables
- **Escalabilidad**: Fácil agregar nuevas funcionalidades
- **Mantenibilidad**: Código limpio y bien documentado
- **Rendimiento**: Optimizado para 60 FPS constantes

## 🏗️ Arquitectura del Sistema

### Patrón Arquitectural: **Component-Based Architecture**

```
SnakeGame (Sistema Principal)
├── Agregación (o--) ─→ Componentes Principales
│   ├── Juego           # Lógica del juego
│   ├── Pantalla        # Sistema de renderizado
│   ├── Serpiente       # Entidad principal
│   ├── Comida          # Objetivos del juego
│   ├── Tablero         # Área de juego
│   ├── Controlador     # Input handling
│   ├── Sonido          # Audio management
│   └── Puntuacion      # Score system
└── Composición (*--) ─→ Elementos Internos
    ├── Segmentos       # Partes de la serpiente
    ├── Texturas        # Assets gráficos
    ├── Audio           # Assets de sonido
    └── Entradas        # Input events
```

### Principios Aplicados:
- **Single Responsibility**: Cada clase tiene una responsabilidad única
- **Dependency Inversion**: Uso de abstracciones sobre implementaciones
- **Composition over Inheritance**: Composición de componentes
- **Open/Closed**: Abierto para extensión, cerrado para modificación

## 📁 Estructura del Proyecto

```
snake_game/
├── 📂 src/                    # Código fuente
│   ├── 🎮 Game.cpp           # Clase principal del juego
│   ├── 🐍 Snake.cpp          # Lógica de la serpiente
│   ├── 🍎 Food.cpp           # Lógica de la comida
│   ├── 🖼️  GameRenderer.cpp   # Sistema de renderizado
│   ├── 🔊 AudioManager.cpp   # Gestión de audio
│   ├── ⌨️  InputHandler.cpp   # Manejo de entrada
│   └── � main.cpp           # Punto de entrada del programa
├── 📂 include/               # Headers
│   ├── 🎮 Game.hpp
│   ├── 🐍 Snake.hpp
│   ├── 🍎 Food.hpp
│   ├── 🖼️  GameRenderer.hpp
│   ├── 🔊 AudioManager.hpp
│   └── ⌨️  InputHandler.hpp
├── 📂 assets/                # Recursos del juego
│   ├── 📂 images/           # Sprites y texturas
│   │   ├── cabeza.png       # Sprite de cabeza de serpiente
│   │   ├── cuerpo.png       # Sprite de cuerpo de serpiente
│   │   ├── cuerpovertical.png # Sprite de segmento vertical
│   │   ├── segmento.png     # Sprite de segmento general
│   │   ├── frontal.png      # Cabeza mirando arriba
│   │   ├── trasera.png      # Cabeza mirando abajo
│   │   ├── izquierda.png    # Cabeza mirando izquierda
│   │   ├── derecha.png      # Cabeza mirando derecha
│   │   ├── comida.png       # Sprite de comida
│   │   ├── fondo.jpg        # Fondo del juego
│   │   ├── cero.png         # Dígito 0 para score
│   │   ├── uno.png          # Dígito 1 para score
│   │   ├── dos.png          # Dígito 2 para score
│   │   ├── tres.png         # Dígito 3 para score
│   │   ├── cuatro.png       # Dígito 4 para score
│   │   ├── cinco.png        # Dígito 5 para score
│   │   ├── seis.png         # Dígito 6 para score
│   │   ├── siete.png        # Dígito 7 para score
│   │   ├── ocho.png         # Dígito 8 para score
│   │   ├── nueve.png        # Dígito 9 para score
│   │   ├── pantalla de inicio.jpg # Pantalla de inicio
│   │   └── pantalla final.jpg     # Pantalla de game over
│   └── 📂 music/            # Audio
│       ├── inicio.ogg       # Música de inicio (convertido de .wav)
│       ├── musica_fondo.ogg # Música del juego (convertido de .wav)
│       ├── comer.ogg        # Efecto al comer (convertido de .wav)
│       ├── choque.ogg       # Efecto de colisión (convertido de .wav)
│       └── gameover.ogg     # Sonido de game over (convertido de .wav)
├── 📂 bin/                   # Ejecutables
│   └── 🎮 SnakeGame         # Ejecutable principal (generado)
├── 📂 obj/                   # Archivos objeto (generado)
├── 📂 docs/                  # Documentación
│   ├── 📖 MANUAL_USUARIO.md # Manual de usuario
│   ├── 👨‍💻 MANUAL_PROGRAMADOR.md # Este manual
│   ├── 📊 DIAGRAMA_CLASES.md # Diagrama UML textual
│   └── 🎨 SnakeGameClassDiagram.puml # Diagrama PlantUML
└── 🔧 Makefile              # Script de compilación
```

## 🛠️ Dependencias y Tecnologías

### Lenguaje y Estándar:
- **C++17**: Características modernas del lenguaje
- **STL**: Uso extensivo de contenedores y algoritmos

### Librerías Principales:
```cpp
// Graphics & Window Management
#include <SFML/Graphics.hpp>    // Core SFML graphics functionality
#include <SFML/Window.hpp>      // Window and event handling
#include <SFML/System.hpp>      // System utilities and timing

// Audio
#include <SFML/Audio.hpp>       // Audio playback (OGG, WAV, FLAC)

// Standard Library
#include <memory>               // Smart pointers
#include <vector>               // Dynamic arrays
#include <map>                  // Key-value containers
#include <string>               // String handling
#include <iostream>             // I/O operations
#include <random>               // Random number generation
#include <functional>           // Function objects
```

### Herramientas de Build:
- **GNU Make**: Sistema de compilación
- **GCC/G++**: Compilador principal
- **pkg-config**: Gestión de dependencias

## ⚙️ Configuración del Entorno

### Instalación de Dependencias:

#### Ubuntu/Debian:
```bash
# Actualizar repositorios
sudo apt update

# Instalar herramientas de desarrollo
sudo apt install build-essential git

# Instalar librerías SFML
sudo apt install libsfml-dev

# Verificar instalación
pkg-config --modversion sfml-all
```

#### Fedora/CentOS:
```bash
# Instalar herramientas de desarrollo
sudo dnf groupinstall "Development Tools"

# Instalar librerías SFML
sudo dnf install SFML-devel

# Verificar instalación
pkg-config --modversion sfml-all
```

#### Arch Linux:
```bash
# Instalar dependencias
sudo pacman -S base-devel sfml

# Verificar instalación
pkg-config --modversion sfml-all
```

### Configuración del IDE:

#### VS Code:
```json
// .vscode/c_cpp_properties.json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**",
                "/usr/include/SFML"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "c17",
            "cppStandard": "c++17"
        }
    ]
}
```

#### CLion:
```cmake
# CMakeLists.txt (alternativo)
cmake_minimum_required(VERSION 3.16)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML REQUIRED sfml-all)

include_directories(include/)
file(GLOB SOURCES "src/*.cpp")

add_executable(SnakeGame ${SOURCES})
target_link_libraries(SnakeGame ${SFML_LIBRARIES})
```

## 🔨 Compilación y Build

### Makefile Explicado:

```makefile
# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
DEBUGFLAGS = -std=c++17 -Wall -Wextra -g -DDEBUG

# Directorios
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin
DATADIR = assets

# Archivos fuente y objeto
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/SnakeGame

# Bibliotecas SFML
SFML_LIBS = -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-window

# Para Windows, ajustar si es necesario
ifeq ($(OS),Windows_NT)
    TARGET := $(TARGET).exe
    # Rutas típicas para Windows con vcpkg o instalación manual
    SFML_CFLAGS = -IC:/vcpkg/installed/x64-windows/include
    SFML_LIBS = -LC:/vcpkg/installed/x64-windows/lib -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-window
endif

# Agregar flags de SFML a CXXFLAGS
CXXFLAGS += $(SFML_CFLAGS) -I$(INCDIR)
DEBUGFLAGS += $(SFML_CFLAGS) -I$(INCDIR)

# Regla principal
all: $(TARGET)

# Crear directorios si no existen
$(OBJDIR):
    mkdir -p $(OBJDIR)

$(BINDIR):
    mkdir -p $(BINDIR)

# Regla para crear el ejecutable
$(TARGET): $(OBJECTS) | $(BINDIR)
    $(CXX) $(OBJECTS) -o $@ $(SFML_LIBS)
    @echo "Build complete: $(TARGET)"

# Regla para compilar archivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
    $(CXX) $(CXXFLAGS) -c $< -o $@

# Build de debug
debug: CXXFLAGS = $(DEBUGFLAGS)
debug: $(TARGET)

# Limpiar archivos generados
clean:
    rm -rf $(OBJDIR) $(BINDIR)

# Ejecutar el juego
run: $(TARGET)
    cd "." && $(BINDIR)/$(notdir $(TARGET))

# Instalar dependencias SFML
install-deps:
    @echo "Installing SFML dependencies..."
    @if command -v apt-get >/dev/null 2>&1; then \
        sudo apt-get update && sudo apt-get install -y libsfml-dev; \
    elif command -v yum >/dev/null 2>&1; then \
        sudo yum install -y SFML-devel; \
    elif command -v pacman >/dev/null 2>&1; then \
        sudo pacman -S sfml; \
    elif command -v brew >/dev/null 2>&1; then \
        brew install sfml; \
    else \
        echo "Package manager not recognized. Please install SFML manually."; \
    fi

# Verificar dependencias
check-deps:
    @echo "Checking SFML dependencies..."
    @pkg-config --exists sfml-graphics && echo "✓ SFML Graphics found" || echo "✗ SFML Graphics not found"
    @pkg-config --exists sfml-audio && echo "✓ SFML Audio found" || echo "✗ SFML Audio not found"
    @pkg-config --exists sfml-system && echo "✓ SFML System found" || echo "✗ SFML System not found"

# Reglas que no crean archivos
.PHONY: all clean run install-deps debug check-deps
```

### Comandos de Build:

```bash
# Compilación completa
make clean && make

# Compilación incremental
make

# Ejecutar después de compilar
make run

# Solo limpiar
make clean

# Compilación con debug
make CXXFLAGS="-std=c++17 -g -Wall -Wextra -Iinclude/"

# Compilación optimizada
make CXXFLAGS="-std=c++17 -O3 -Wall -Wextra -Iinclude/"
```

## 🎯 Clases Principales

### 1. **Game.hpp/cpp** - Controlador Principal

```cpp
class Game {
private:
    static const int WINDOW_WIDTH = 1200;
    static const int WINDOW_HEIGHT = 900;
    static const int GRID_SIZE = 20;  // Aumentado de 15 a 20 píxeles para sprites más grandes
    static const int GAME_AREA_MARGIN = 100;  // Reducido de 200 a 100 píxeles
    static const int GAME_AREA_WIDTH = WINDOW_WIDTH - (2 * GAME_AREA_MARGIN);  // 1000 píxeles
    static const int GAME_AREA_HEIGHT = WINDOW_HEIGHT - (2 * GAME_AREA_MARGIN); // 700 píxeles
    static const int GRID_WIDTH = GAME_AREA_WIDTH / GRID_SIZE;   // 50 celdas
    static const int GRID_HEIGHT = GAME_AREA_HEIGHT / GRID_SIZE; // 35 celdas
    
    sf::RenderWindow window;
    sf::Clock gameClock;
    bool isRunning;
    bool gameOver;
    bool gameStarted;
    int score;
    
    // Componentes del juego (Composición)
    std::unique_ptr<Snake> snake;           // 1..1
    std::unique_ptr<Food> food;             // 1..1
    std::unique_ptr<GameRenderer> renderer; // 1..1
    std::unique_ptr<AudioManager> audioManager; // 1..1
    std::unique_ptr<InputHandler> inputHandler; // 1..1

public:
    Game();
    ~Game();
    
    // Métodos principales (verbos)
    bool Initialize();
    void Run();
    void Update();
    void HandleEvents();
    void Render();
    void Cleanup();
    
    // Métodos de control del juego
    void StartGame();
    void RestartGame();
    void EndGame();
    void PauseGame();
    void ResumeGame();
    
    // Métodos de puntuación
    void AddScore(int points);
    void ResetScore();
    
    // Getters
    bool IsRunning() const { return isRunning; }
    bool IsGameOver() const { return gameOver; }
    bool IsGameStarted() const { return gameStarted; }
    int GetScore() const { return score; }
    int GetGridSize() const { return GRID_SIZE; }
    int GetGridWidth() const { return GRID_WIDTH; }
    int GetGridHeight() const { return GRID_HEIGHT; }
    
    // Métodos de control de la serpiente
    void ChangeSnakeDirection(Direction direction);
    
    // Acceso a componentes
    GameRenderer* GetRenderer() const { return renderer.get(); }
    AudioManager* GetAudioManager() const { return audioManager.get(); }
    sf::RenderWindow& GetWindow() { return window; }
};
```

**Responsabilidades:**
- Inicialización y cierre del sistema
- Coordinación entre componentes
- Loop principal del juego
- Gestión de estados (menú, jugando, game over)

### 2. **Snake.hpp/cpp** - Lógica de la Serpiente

```cpp
enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Position {
    int x, y;
    
    Position(int x = 0, int y = 0) : x(x), y(y) {}
    
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator!=(const Position& other) const {
        return !(*this == other);
    }
};

class Snake {
private:
    std::vector<Position> segments;     // 1..*  (múltiples segmentos)
    Direction currentDirection;
    Direction nextDirection;
    bool hasGrown;
    int length;
    int growthFrames;  // Contador para mostrar efectos de crecimiento

public:
    Snake(int startX, int startY);
    ~Snake();
    
    // Métodos de movimiento (verbos)
    void Move();
    void ChangeDirection(Direction newDirection);
    void Grow();
    void Reset(int startX, int startY);
    
    // Métodos de actualización
    void Update();
    void Render(GameRenderer* renderer);
    
    // Métodos de validación
    bool IsValidDirection(Direction direction) const;
    bool CheckSelfCollision() const;
    bool CheckWallCollision(int gridWidth, int gridHeight) const;
    bool CheckCollisionAt(const Position& position) const;
    
    // Getters
    const Position& GetHead() const { return segments[0]; }
    const std::vector<Position>& GetSegments() const { return segments; }
    Direction GetCurrentDirection() const { return currentDirection; }
    Direction GetNextDirection() const { return nextDirection; }
    int GetLength() const { return length; }
    bool HasGrown() const { return hasGrown; }
    int GetGrowthFrames() const { return growthFrames; }
};
```

**Algoritmos clave:**
- **Movimiento**: Agregar nueva cabeza, remover cola
- **Crecimiento**: No remover cola en el siguiente movimiento
- **Colisión**: Verificar intersección con segmentos propios

### 3. **GameRenderer.hpp/cpp** - Sistema de Renderizado

```cpp
class GameRenderer {
private:
    sf::RenderWindow* window;
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Sprite> sprites;
    sf::Font font;
    int gridSize;

public:
    GameRenderer();
    ~GameRenderer();
    
    // Métodos de inicialización (verbos)
    bool Initialize(sf::RenderWindow* renderWindow);
    bool LoadAssets();
    void Cleanup();
    
    // Métodos de renderizado
    void Clear();
    void Present();
    void RenderBackground();
    void RenderSnake(const Snake& snake);
    void RenderFood(const Food& food);
    void RenderScore(int score);
    void RenderStartScreen();
    void RenderGameOverScreen();
    void RenderPauseScreen();
    void RenderGameBounds();  // Renderizar límites del área de juego
    
    // Métodos de texturas y sprites
    bool LoadTexture(const std::string& name, const std::string& path);
    sf::Texture* GetTexture(const std::string& name);
    sf::Sprite* GetSprite(const std::string& name);
};
```

**Características:**
- **Gestión de texturas**: Carga y cache automático
- **Renderizado por capas**: Fondo → Entidades → UI
- **Sprites direccionales**: Cabeza según dirección de movimiento

### 4. **AudioManager.hpp/cpp** - Gestión de Audio

```cpp
class AudioManager {
private:
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, sf::Sound> sounds;
    std::map<std::string, sf::Music> musicTracks;
    sf::Music* currentMusic;
    bool isMusicEnabled;
    bool areSoundEffectsEnabled;
    float musicVolume;
    float soundVolume;

public:
    AudioManager();
    ~AudioManager();
    
    // Métodos de inicialización (verbos)
    bool Initialize();
    bool LoadAudioAssets();
    void Cleanup();
    
    // Métodos de música
    void PlayMusic(const std::string& musicName, bool loop = true);
    void StopMusic();
    void PauseMusic();
    void ResumeMusic();
    
    // Métodos de efectos de sonido
    void PlaySoundEffect(const std::string& soundName);
    void StopSoundEffect(const std::string& soundName);
    void StopAllSoundEffects();
    
    // Métodos de carga
    bool LoadSoundEffect(const std::string& name, const std::string& filename);
    bool LoadMusic(const std::string& name, const std::string& filename);
    
    // Control de volumen
    void SetMusicVolume(float volume);
    void SetSoundVolume(float volume);
    void ToggleMusic();
    void ToggleSoundEffects();
    
    // Getters
    bool IsMusicEnabled() const { return isMusicEnabled; }
    bool AreSoundEffectsEnabled() const { return areSoundEffectsEnabled; }
    float GetMusicVolume() const { return musicVolume; }
    float GetSoundVolume() const { return soundVolume; }
};
```

**Formatos soportados:**
- **OGG Vorbis**: Para música y efectos de sonido
- **WAV**: Para efectos de sonido de alta calidad
- **FLAC**: Para música sin pérdida
- **Gestión automática**: Carga lazy de assets
- **Control granular**: Volumen independiente por tipo

### 5. **InputHandler.hpp/cpp** - Manejo de Entrada

```cpp
enum class InputType {
    KEY_PRESS,
    KEY_RELEASE,
    QUIT_EVENT
};

struct InputEvent {
    InputType type;
    sf::Keyboard::Key key;
    bool isPressed;
    
    InputEvent(InputType t = InputType::KEY_PRESS, sf::Keyboard::Key k = sf::Keyboard::Unknown, bool pressed = false)
        : type(t), key(k), isPressed(pressed) {}
};

class InputHandler {
private:
    std::map<sf::Keyboard::Key, Direction> keyToDirectionMap;
    std::map<sf::Keyboard::Key, std::function<void()>> keyActionMap;
    std::map<sf::Keyboard::Key, bool> keyState;
    Game* gameInstance;
    bool isEnabled;

public:
    InputHandler();
    ~InputHandler();
    
    // Métodos de inicialización (verbos)
    void Initialize(Game* game);
    void ConfigureDefaultKeys();
    void Cleanup();
    
    // Métodos de procesamiento de eventos
    void HandleEvents(sf::RenderWindow& window);
    void ProcessEvent(const sf::Event& event);
    void ProcessKeyPressed(sf::Keyboard::Key key);
    void ProcessKeyReleased(sf::Keyboard::Key key);
    void ProcessWindowClosed();
    
    // Métodos de configuración de teclas
    void MapKeyToDirection(sf::Keyboard::Key key, Direction direction);
    void MapKeyToAction(sf::Keyboard::Key key, std::function<void()> action);
    void RemoveKeyMapping(sf::Keyboard::Key key);
    void ResetKeyMappings();
    
    // Métodos de estado
    void Enable();
    void Disable();
    void ToggleEnabled();
    bool IsKeyPressed(sf::Keyboard::Key key) const;
    bool IsAnyKeyPressed() const;
    
    // Métodos de validación
    bool IsValidDirectionKey(sf::Keyboard::Key key) const;
    bool IsValidActionKey(sf::Keyboard::Key key) const;
    bool CanChangeDirection(Direction newDirection, Direction currentDirection) const;
    
    // Getters
    bool IsEnabled() const { return isEnabled; }
    Direction GetDirectionFromKey(sf::Keyboard::Key key) const;
    const std::map<sf::Keyboard::Key, Direction>& GetKeyDirectionMap() const { return keyToDirectionMap; }
    
    // Setters
    void SetGameInstance(Game* game) { gameInstance = game; }
    void SetEnabled(bool enabled) { isEnabled = enabled; }
};
```

## 🔄 Flujo de Ejecución

### Game Loop Principal:

```cpp
void Game::Run() {
    sf::Clock clock;
    const sf::Time timeStep = sf::seconds(1.0f / 10.0f); // 10 FPS para la serpiente
    sf::Time accumulator = sf::Time::Zero;
    
    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        accumulator += elapsed;
        
        // 1. Procesar eventos de entrada
        HandleEvents();
        
        // 2. Actualizar lógica del juego con timestep fijo
        while (accumulator >= timeStep) {
            Update();
            accumulator -= timeStep;
        }
        
        // 3. Renderizar frame actual
        Render();
    }
}

void Game::HandleEvents() {
    inputHandler->HandleEvents(window);
}

void Game::Update() {
    if (!gameStarted || gameOver) {
        return;
    }
    
    // Actualizar serpiente
    snake->Update();
    
    // Verificar colisiones con paredes
    if (snake->CheckWallCollision(GRID_WIDTH, GRID_HEIGHT)) {
        EndGame();
        return;
    }
    
    // Verificar auto-colisión
    if (snake->CheckSelfCollision()) {
        EndGame();
        return;
    }
    
    // Verificar si comió la comida
    if (snake->CheckCollisionAt(food->GetPosition())) {
        snake->Grow();
        AddScore(10);
        food->Respawn(GRID_WIDTH, GRID_HEIGHT, *snake);
        audioManager->PlaySoundEffect("comer");
    }
}

void Game::Render() {
    renderer->Clear();
    
    if (!gameStarted) {
        renderer->RenderStartScreen();
    } else if (gameOver) {
        renderer->RenderGameOverScreen();
    } else {
        renderer->RenderBackground();
        renderer->RenderGameBounds();
        renderer->RenderFood(*food);
        renderer->RenderSnake(*snake);
        renderer->RenderScore(score);
    }
    
    renderer->Present();
}
```

## 🎨 Sistema de Renderizado

### Pipeline de Renderizado:

```cpp
void Game::Render() {
    // 1. Limpiar buffer
    renderer->Clear();
    
    // 2. Renderizar fondo
    renderer->RenderBackground();
    
    // 3. Renderizar límites del área de juego
    renderer->RenderGameBounds();
    
    // 4. Renderizar entidades del juego
    if (currentState == GameState::PLAYING || 
        currentState == GameState::PAUSED) {
        renderer->RenderFood(*food);
        renderer->RenderSnake(*snake);
    }
    
    // 5. Renderizar UI
    renderer->RenderScore(score);
    
    // 6. Renderizar overlays según estado
    switch (currentState) {
        case GameState::MENU:
            renderer->RenderMenuScreen();
            break;
        case GameState::PAUSED:
            renderer->RenderPauseOverlay();
            break;
        case GameState::GAME_OVER:
            renderer->RenderGameOverScreen(score, highScore);
            break;
    }
    
    // 7. Presentar frame
    renderer->Display();
}
```

### Gestión de Sprites:

```cpp
// Sprite direccional para cabeza de serpiente
void GameRenderer::RenderSnakeHead(const Position& pos, Direction dir) {
    std::string spriteName;
    switch (dir) {
        case Direction::UP:    spriteName = "frontal"; break;
        case Direction::DOWN:  spriteName = "trasera"; break;
        case Direction::LEFT:  spriteName = "izquierda"; break;
        case Direction::RIGHT: spriteName = "derecha"; break;
    }
    
    sf::Sprite& sprite = GetSprite(spriteName);
    sprite.setPosition(
        pos.x * gridSize + gameAreaMargin,
        pos.y * gridSize + gameAreaMargin
    );
    
    window->draw(sprite);
}
```

## 🔊 Gestión de Audio

### Arquitectura de Audio:

```cpp
class AudioManager {
private:
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, sf::Sound> sounds;
    std::map<std::string, sf::Music> musicTracks;
    sf::Music* currentMusic;
    bool isMusicEnabled;
    bool areSoundEffectsEnabled;
    float musicVolume;
    float soundVolume;

public:
    bool LoadAudioAssets() {
        // Cargar efectos de sonido
        if (!LoadSoundEffect("comer", "assets/music/comer.ogg")) return false;
        if (!LoadSoundEffect("choque", "assets/music/choque.ogg")) return false;
        if (!LoadSoundEffect("gameover", "assets/music/gameover.ogg")) return false;
        
        // Cargar música
        if (!LoadMusic("inicio", "assets/music/inicio.ogg")) return false;
        if (!LoadMusic("fondo", "assets/music/musica_fondo.ogg")) return false;
        
        return true;
    }
    
    bool LoadSoundEffect(const std::string& name, const std::string& filename) {
        if (!soundBuffers[name].loadFromFile(filename)) {
            return false;
        }
        sounds[name].setBuffer(soundBuffers[name]);
        return true;
    }
    
    bool LoadMusic(const std::string& name, const std::string& filename) {
        // Para música, SFML requiere cargar directamente desde archivo
        // cuando se vaya a reproducir
        return true; // Validación al reproducir
    }
    
    void PlaySoundEffect(const std::string& soundName) {
        if (areSoundEffectsEnabled && sounds.find(soundName) != sounds.end()) {
            sounds[soundName].setVolume(soundVolume);
            sounds[soundName].play();
        }
    }
    
    void PlayMusic(const std::string& musicName, bool loop = true) {
        if (!isMusicEnabled) return;
        
        std::string filename = "assets/music/" + musicName + ".ogg";
        if (currentMusic && currentMusic->openFromFile(filename)) {
            currentMusic->setLoop(loop);
            currentMusic->setVolume(musicVolume);
            currentMusic->play();
        }
    }
};
```

### Sistema de Audio Reactivo:

```cpp
// Reproducción contextual de audio
void Game::HandleGameEvent(GameEvent event) {
    switch (event) {
        case GameEvent::FOOD_EATEN:
            audioManager->PlaySoundEffect("comer");
            break;
            
        case GameEvent::COLLISION:
            audioManager->PlaySoundEffect("choque");
            audioManager->StopMusic();
            break;
            
        case GameEvent::GAME_START:
            audioManager->StopMusic();
            audioManager->PlayMusic("fondo");
            break;
            
        case GameEvent::GAME_OVER:
            audioManager->PlaySoundEffect("gameover");
            break;
    }
}
```

## ⌨️ Manejo de Entrada

### Sistema de Input Mapping:

```cpp
class InputHandler {
private:
    std::map<sf::Keyboard::Key, Direction> keyToDirectionMap;
    std::map<sf::Keyboard::Key, std::function<void()>> keyActionMap;
    std::map<sf::Keyboard::Key, bool> keyState;
    Game* gameInstance;
    bool isEnabled;

public:
    void Initialize(Game* game) {
        gameInstance = game;
        ConfigureDefaultKeys();
    }
    
    void ConfigureDefaultKeys() {
        // Mapear direcciones
        keyToDirectionMap[sf::Keyboard::Up] = Direction::UP;
        keyToDirectionMap[sf::Keyboard::W] = Direction::UP;
        keyToDirectionMap[sf::Keyboard::Down] = Direction::DOWN;
        keyToDirectionMap[sf::Keyboard::S] = Direction::DOWN;
        keyToDirectionMap[sf::Keyboard::Left] = Direction::LEFT;
        keyToDirectionMap[sf::Keyboard::A] = Direction::LEFT;
        keyToDirectionMap[sf::Keyboard::Right] = Direction::RIGHT;
        keyToDirectionMap[sf::Keyboard::D] = Direction::RIGHT;
        
        // Mapear acciones
        keyActionMap[sf::Keyboard::Space] = [this]() { /* Pausar/Reanudar */ };
        keyActionMap[sf::Keyboard::R] = [this]() { /* Reiniciar juego */ };
        keyActionMap[sf::Keyboard::Escape] = [this]() { /* Salir del juego */ };
        keyActionMap[sf::Keyboard::M] = [this]() { /* Toggle música */ };
    }
    
    void HandleEvents(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ProcessEvent(event);
        }
    }
    
    void ProcessEvent(const sf::Event& event) {
        switch (event.type) {
            case sf::Event::Closed:
                ProcessWindowClosed();
                break;
            case sf::Event::KeyPressed:
                ProcessKeyPressed(event.key.code);
                break;
            case sf::Event::KeyReleased:
                ProcessKeyReleased(event.key.code);
                break;
            default:
                break;
        }
    }
};
```

### Validación de Movimiento:

```cpp
bool Snake::IsValidDirectionChange(Direction newDirection) const {
    // No permitir movimiento en dirección opuesta
    switch (currentDirection) {
        case Direction::UP:
            return newDirection != Direction::DOWN;
        case Direction::DOWN:
            return newDirection != Direction::UP;
        case Direction::LEFT:
            return newDirection != Direction::RIGHT;
        case Direction::RIGHT:
            return newDirection != Direction::LEFT;
    }
    return true;
}
```

## 🗂️ Gestión de Recursos

### Resource Manager Pattern:

```cpp
template<typename T>
class ResourceManager {
private:
    std::map<std::string, std::unique_ptr<T>> resources;
    
public:
    template<typename... Args>
    T* Load(const std::string& name, Args&&... args) {
        auto it = resources.find(name);
        if (it != resources.end()) {
            return it->second.get();
        }
        
        auto resource = std::make_unique<T>(std::forward<Args>(args)...);
        T* ptr = resource.get();
        resources[name] = std::move(resource);
        return ptr;
    }
    
    T* Get(const std::string& name) {
        auto it = resources.find(name);
        return (it != resources.end()) ? it->second.get() : nullptr;
    }
    
    void Clear() {
        resources.clear();
    }
};

// Uso específico para texturas
using TextureManager = ResourceManager<sf::Texture>;
using AudioManager = ResourceManager<sf::SoundBuffer>;
```

### Asset Loading Strategy:

```cpp
class AssetLoader {
public:
    static bool LoadAllAssets(GameRenderer* renderer, AudioManager* audio) {
        // Cargar sprites de la serpiente
        const std::vector<std::string> snakeSprites = {
            "cabeza", "cuerpo", "segmento", "cuerpovertical",
            "frontal", "trasera", "izquierda", "derecha"
        };
        
        for (const auto& sprite : snakeSprites) {
            if (!renderer->LoadTexture("assets/images/" + sprite + ".png")) {
                std::cerr << "Failed to load sprite: " << sprite << std::endl;
                return false;
            }
        }
        
        // Cargar sprites de números para score
        for (int i = 0; i <= 9; ++i) {
            std::string filename = "assets/images/" + std::to_string(i) + ".png";
            if (!renderer->LoadTexture(filename)) {
                std::cerr << "Failed to load number sprite: " << i << std::endl;
                return false;
            }
        }
        
        // Cargar otros assets
        return LoadGameAssets(renderer) && LoadAudioAssets(audio);
    }
};
```

## 🎯 Patterns y Principios

### 1. **Component Pattern**:
```cpp
// En lugar de herencia, usamos composición
class GameObject {
private:
    std::unique_ptr<PositionComponent> position;
    std::unique_ptr<RenderComponent> render;
    std::unique_ptr<CollisionComponent> collision;
    
public:
    template<typename T>
    T* GetComponent() {
        // Template specialization para cada tipo
    }
    
    template<typename T, typename... Args>
    T* AddComponent(Args&&... args) {
        // Factory method para componentes
    }
};
```

### 2. **Observer Pattern** para eventos:
```cpp
class GameEventSystem {
private:
    std::map<GameEventType, std::vector<std::function<void(const GameEvent&)>>> listeners;
    
public:
    void Subscribe(GameEventType type, std::function<void(const GameEvent&)> listener) {
        listeners[type].push_back(listener);
    }
    
    void Publish(const GameEvent& event) {
        for (auto& listener : listeners[event.type]) {
            listener(event);
        }
    }
};
```

### 3. **State Pattern** para game states:
```cpp
class GameState {
public:
    virtual ~GameState() = default;
    virtual void Enter() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render(GameRenderer* renderer) = 0;
    virtual void Exit() = 0;
};

class PlayingState : public GameState {
    void Update(float deltaTime) override {
        // Lógica específica del estado "jugando"
    }
};
```

### 4. **RAII** para gestión de recursos:
```cpp
class SFMLResource {
private:
    sf::Texture texture;
    
public:
    SFMLResource(const std::string& path) {
        if (!texture.loadFromFile(path)) {
            throw std::runtime_error("Failed to load texture: " + path);
        }
    }
    
    // El destructor se maneja automáticamente por SFML
    
    // No copyable, solo movible
    SFMLResource(const SFMLResource&) = delete;
    SFMLResource& operator=(const SFMLResource&) = delete;
    
    SFMLResource(SFMLResource&& other) noexcept = default;
    SFMLResource& operator=(SFMLResource&& other) noexcept = default;
    
    const sf::Texture& getTexture() const { return texture; }
    }
};
```

## 🧪 Testing y Debugging

### Unit Testing Framework:

```cpp
// test/test_snake.cpp
#include "catch2/catch.hpp"
#include "Snake.hpp"

TEST_CASE("Snake Movement", "[snake]") {
    Snake snake;
    Position initialHead = snake.GetHead();
    
    SECTION("Move right") {
        snake.ChangeDirection(Direction::RIGHT);
        snake.Move();
        
        Position newHead = snake.GetHead();
        REQUIRE(newHead.x == initialHead.x + 1);
        REQUIRE(newHead.y == initialHead.y);
    }
    
    SECTION("Cannot move in opposite direction") {
        snake.ChangeDirection(Direction::RIGHT);
        snake.Move();
        
        // Intentar moverse a la izquierda debería ser ignorado
        snake.ChangeDirection(Direction::LEFT);
        snake.Move();
        
        Position head = snake.GetHead();
        REQUIRE(head.x > initialHead.x); // Siguió moviéndose a la derecha
    }
}

TEST_CASE("Collision Detection", "[snake]") {
    Snake snake;
    
    SECTION("Wall collision") {
        // Mover la serpiente fuera de los límites
        for (int i = 0; i < 100; ++i) {
            snake.Move();
        }
        
        REQUIRE(snake.CheckWallCollision(800, 600) == true);
    }
}
```

### Debugging Helpers:

```cpp
class DebugRenderer {
private:
    sf::RenderWindow* window;
    bool debugEnabled;
    sf::Font debugFont;
    
public:
    void RenderCollisionBoxes(const Snake& snake) {
        if (!debugEnabled) return;
        
        // Renderizar cajas de colisión
        sf::RectangleShape debugRect;
        debugRect.setFillColor(sf::Color::Transparent);
        debugRect.setOutlineColor(sf::Color::Red);
        debugRect.setOutlineThickness(1.0f);
        
        for (const auto& segment : snake.GetSegments()) {
            debugRect.setPosition(segment.x * 20.0f, segment.y * 20.0f);
            debugRect.setSize(sf::Vector2f(20.0f, 20.0f));
            window->draw(debugRect);
        }
    }
    
    void RenderFPS(int fps) {
        if (!debugEnabled) return;
        
        // Renderizar contador de FPS
        sf::Text fpsText;
        fpsText.setFont(debugFont);
        fpsText.setString("FPS: " + std::to_string(fps));
        fpsText.setCharacterSize(16);
        fpsText.setFillColor(sf::Color::White);
        fpsText.setPosition(10, 10);
        window->draw(fpsText);
    }
    
    void RenderGameInfo(const Game& game) {
        if (!debugEnabled) return;
        
        // Información del estado del juego
        sf::Text infoText;
        infoText.setFont(debugFont);
        std::string info = "Score: " + std::to_string(game.GetScore()) +
                          " | Length: " + std::to_string(game.GetSnake().GetLength());
        infoText.setString(info);
        infoText.setCharacterSize(16);
        infoText.setFillColor(sf::Color::White);
        infoText.setPosition(10, 30);
        window->draw(infoText);
    }
};
```

### Profiling y Optimización:

```cpp
class Profiler {
private:
    std::map<std::string, std::chrono::high_resolution_clock::time_point> timers;
    std::map<std::string, double> averages;
    
public:
    void StartTimer(const std::string& name) {
        timers[name] = std::chrono::high_resolution_clock::now();
    }
    
    void EndTimer(const std::string& name) {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double, std::milli>(end - timers[name]);
        
        // Calcular promedio móvil
        averages[name] = (averages[name] * 0.9) + (duration.count() * 0.1);
    }
    
    void PrintStats() {
        for (const auto& [name, time] : averages) {
            std::cout << name << ": " << time << "ms" << std::endl;
        }
    }
};

// Uso en el game loop
void Game::Update() {
    profiler.StartTimer("Snake Update");
    snake->Update();
    profiler.EndTimer("Snake Update");
    
    profiler.StartTimer("Collision Check");
    CheckCollisions();
    profiler.EndTimer("Collision Check");
}
```

## 🚀 Extensiones y Mejoras

### 1. **Sistema de Power-ups**:

```cpp
enum class PowerUpType {
    SPEED_BOOST,    // Aumenta velocidad temporalmente
    SLOW_TIME,      // Ralentiza el tiempo
    DOUBLE_SCORE,   // Duplica puntos por un tiempo
    EXTRA_LIFE,     // Vida extra (para modo con vidas)
    SHRINK          // Reduce tamaño de la serpiente
};

class PowerUp {
private:
    Position position;
    PowerUpType type;
    float duration;     // Duración del efecto
    bool isActive;
    
public:
    void Apply(Snake& snake, Game& game);
    void Update(float deltaTime);
    bool IsExpired() const;
};
```

### 2. **Múltiples niveles**:

```cpp
class Level {
private:
    int levelNumber;
    int targetScore;        // Score necesario para pasar
    float snakeSpeed;       // Velocidad de la serpiente
    std::vector<Position> obstacles; // Obstáculos en el nivel
    
public:
    bool IsCompleted(int currentScore) const;
    void LoadLevel(int number);
    void RenderObstacles(GameRenderer* renderer);
};

class LevelManager {
private:
    std::vector<std::unique_ptr<Level>> levels;
    int currentLevel;
    
public:
    void LoadNextLevel();
    Level* GetCurrentLevel();
    bool IsGameComplete() const;
};
```

### 3. **IA para serpiente automática**:

```cpp
class SnakeAI {
private:
    Snake* snake;
    Food* food;
    
    // Algoritmo A* para pathfinding
    std::vector<Position> FindPath(Position start, Position goal);
    bool IsPositionSafe(Position pos);
    
public:
    Direction GetNextMove();
    void SetDifficulty(AIDifficulty difficulty);
};

enum class AIDifficulty {
    EASY,       // A veces toma decisiones subóptimas
    MEDIUM,     // Juega bien pero no perfecto
    HARD,       // Juego casi perfecto
    PERFECT     // Nunca pierde (para demo)
};
```

### 4. **Sistema de configuración**:

```cpp
class GameConfig {
private:
    std::map<std::string, std::any> settings;
    std::string configFile;
    
public:
    template<typename T>
    T Get(const std::string& key, const T& defaultValue = T{}) {
        auto it = settings.find(key);
        if (it != settings.end()) {
            return std::any_cast<T>(it->second);
        }
        return defaultValue;
    }
    
    template<typename T>
    void Set(const std::string& key, const T& value) {
        settings[key] = value;
    }
    
    bool LoadFromFile(const std::string& filename);
    bool SaveToFile(const std::string& filename);
};

// Uso
GameConfig config;
config.LoadFromFile("settings.json");

int windowWidth = config.Get<int>("window_width", 1200);
bool fullscreen = config.Get<bool>("fullscreen", false);
float musicVolume = config.Get<float>("music_volume", 0.7f);
```

### 5. **Multiplayer local**:

```cpp
class MultiplayerGame {
private:
    std::vector<std::unique_ptr<Snake>> players;
    std::vector<std::unique_ptr<InputHandler>> playerInputs;
    
public:
    void AddPlayer(int playerNumber);
    void UpdateAllPlayers();
    void CheckPlayerCollisions();
    PlayerID GetWinner();
};

class PlayerInputHandler : public InputHandler {
private:
    int playerNumber;
    std::map<int, std::map<sf::Keyboard::Key, Direction>> playerControls;
    
public:
    PlayerInputHandler(int playerNum) : playerNumber(playerNum) {
        // Jugador 1: WASD
        // Jugador 2: Flechas
        // Jugador 3: IJKL
        // Jugador 4: Numpad
        SetupPlayerControls();
    }
};
```

## 📚 API Reference

### Game Class - Métodos Principales:

```cpp
class Game {
public:
    // Constructor/Destructor
    Game();
    ~Game();
    
    // Lifecycle
    bool Initialize();
    void Run();
    void Cleanup();
    
    // Game Control
    void StartGame();
    void RestartGame();
    void EndGame();
    void PauseGame();
    void ResumeGame();
    
    // State Queries
    bool IsRunning() const { return isRunning; }
    bool IsGameOver() const { return gameOver; }
    bool IsGameStarted() const { return gameStarted; }
    int GetScore() const { return score; }
    int GetGridSize() const { return GRID_SIZE; }
    int GetGridWidth() const { return GRID_WIDTH; }
    int GetGridHeight() const { return GRID_HEIGHT; }
    
    // Score Management
    void AddScore(int points);
    void ResetScore();
    
    // Component Access
    GameRenderer* GetRenderer() const { return renderer.get(); }
    AudioManager* GetAudioManager() const { return audioManager.get(); }
    sf::RenderWindow& GetWindow() { return window; }
    
    // Input Control
    void ChangeSnakeDirection(Direction direction);
};
```

### Snake Class - Métodos Principales:

```cpp
class Snake {
public:
    // Constructor
    Snake(int startX, int startY);
    ~Snake();
    
    // Movement
    void Move();
    void ChangeDirection(Direction newDirection);
    void Grow();
    void Reset(int startX, int startY);
    
    // Update
    void Update();
    void Render(GameRenderer* renderer);
    
    // Validation
    bool IsValidDirection(Direction direction) const;
    bool CheckSelfCollision() const;
    bool CheckWallCollision(int gridWidth, int gridHeight) const;
    bool CheckCollisionAt(const Position& position) const;
    
    // State Queries
    const Position& GetHead() const { return segments[0]; }
    const std::vector<Position>& GetSegments() const { return segments; }
    Direction GetCurrentDirection() const { return currentDirection; }
    Direction GetNextDirection() const { return nextDirection; }
    int GetLength() const { return length; }
    bool HasGrown() const { return hasGrown; }
    int GetGrowthFrames() const { return growthFrames; }
};
```

### GameRenderer Class - Métodos Principales:

```cpp
class GameRenderer {
public:
    // Constructor/Destructor
    GameRenderer();
    ~GameRenderer();
    
    // Initialization
    bool Initialize(sf::RenderWindow* renderWindow);
    bool LoadAssets();
    void Cleanup();
    
    // Rendering
    void Clear();
    void Present();
    void RenderBackground();
    void RenderSnake(const Snake& snake);
    void RenderFood(const Food& food);
    void RenderScore(int score);
    void RenderStartScreen();
    void RenderGameOverScreen();
    void RenderPauseScreen();
    void RenderGameBounds();
    
    // Asset Management
    bool LoadTexture(const std::string& name, const std::string& path);
    sf::Texture* GetTexture(const std::string& name);
    sf::Sprite* GetSprite(const std::string& name);
};
```

### AudioManager Class - Métodos Principales:

```cpp
class AudioManager {
public:
    // Constructor/Destructor
    AudioManager();
    ~AudioManager();
    
    // Initialization
    bool Initialize();
    bool LoadAudioAssets();
    void Cleanup();
    
    // Music Control
    void PlayMusic(const std::string& musicName, bool loop = true);
    void StopMusic();
    void PauseMusic();
    void ResumeMusic();
    
    // Sound Effects
    void PlaySoundEffect(const std::string& soundName);
    void StopSoundEffect(const std::string& soundName);
    void StopAllSoundEffects();
    
    // Asset Loading
    bool LoadSoundEffect(const std::string& name, const std::string& filename);
    bool LoadMusic(const std::string& name, const std::string& filename);
    
    // Volume Control
    void SetMusicVolume(float volume);
    void SetSoundVolume(float volume);
    void ToggleMusic();
    void ToggleSoundEffects();
    
    // State Queries
    bool IsMusicEnabled() const { return isMusicEnabled; }
    bool AreSoundEffectsEnabled() const { return areSoundEffectsEnabled; }
    float GetMusicVolume() const { return musicVolume; }
    float GetSoundVolume() const { return soundVolume; }
};
```

## 🛠️ Troubleshooting

### Problemas Comunes de Desarrollo:

#### 1. **Errores de Compilación**:

```bash
# Error: SFML headers not found
# Solución:
pkg-config --cflags sfml-all
export CXXFLAGS="$CXXFLAGS $(pkg-config --cflags sfml-all)"

# Error: undefined reference to SFML functions
# Solución:
pkg-config --libs sfml-all
export LDFLAGS="$LDFLAGS $(pkg-config --libs sfml-all)"
```

#### 2. **Problemas de Rendimiento**:

```cpp
// Profiling de rendimiento
void Game::DebugPerformance() {
    static int frameCount = 0;
    static auto lastTime = std::chrono::high_resolution_clock::now();
    
    frameCount++;
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration<double>(currentTime - lastTime);
    
    if (elapsed.count() >= 1.0) {
        double fps = frameCount / elapsed.count();
        std::cout << "FPS: " << fps << std::endl;
        
        frameCount = 0;
        lastTime = currentTime;
    }
}
```

#### 3. **Memory Leaks**:

```bash
# Usar Valgrind para detectar memory leaks
valgrind --leak-check=full --show-leak-kinds=all ./bin/SnakeGame

# Usar AddressSanitizer
g++ -fsanitize=address -g -o snake_debug src/*.cpp
./snake_debug
```

#### 4. **Debugging con GDB**:

```bash
# Compilar con símbolos de debug
make CXXFLAGS="-std=c++17 -g -Wall -Wextra -Iinclude/"

# Ejecutar con GDB
gdb ./bin/SnakeGame

# Comandos útiles en GDB
(gdb) break Game::Update
(gdb) run
(gdb) print snake->GetLength()
(gdb) watch score
```

### Tips de Desarrollo:

#### 1. **Organización del Código**:
- Un archivo `.cpp` y `.hpp` por cada clase principal
- Separar lógica de presentación
- Usar namespaces para evitar colisiones
- Documentar APIs públicas con Doxygen

#### 2. **Gestión de Recursos**:
- Siempre usar RAII para recursos SFML
- Implementar Resource Managers para assets grandes
- Precargar assets críticos al inicio
- Liberar recursos no utilizados

#### 3. **Optimización**:
- Evitar allocaciones en el game loop
- Usar object pooling para objetos frecuentes
- Implementar dirty flags para rendering
- Cachear cálculos costosos

#### 4. **Testing**:
- Testear cada clase de forma aislada
- Usar mocks para dependencias externas
- Implementar tests de integración
- Automatizar tests con CI/CD

---

## 📝 Conclusión

Este manual proporciona una base sólida para entender y extender el juego Snake. La arquitectura modular permite fácil mantenimiento y extensión, mientras que los patrones de diseño aplicados aseguran código limpio y escalable.

### Próximos pasos recomendados:
1. **Familiarizarse** con el código base actual
2. **Experimentar** con pequeñas modificaciones
3. **Implementar** una extensión simple (ej: power-ups)
4. **Contribuir** mejoras al proyecto principal

### Recursos adicionales:
- [SFML Documentation](https://www.sfml-dev.org/documentation/)
- [SFML Tutorials](https://www.sfml-dev.org/tutorials/)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)
- [Game Programming Patterns](https://gameprogrammingpatterns.com/)
- [PlantUML Documentation](https://plantuml.com/)

---

**¡Disfruten :D!** 🐍💻

---

*Manual del Programador v1.0*
