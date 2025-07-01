# Snake Game Makef# Bibliotecas SFML
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
DEBUGFLAGS += $(SFML_CFLAGS) -I$(INCDIR)or y flags
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

# Bibliotecas SDL2
SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LIBS = $(shell sdl2-config --libs) -lSDL2_image -lSDL2_mixer

# Para Windows, ajustar si es necesario
ifeq ($(OS),Windows_NT)
    TARGET := $(TARGET).exe
    # Rutas típicas para Windows con vcpkg o instalación manual
    SDL_CFLAGS = -IC:/vcpkg/installed/x64-windows/include/SDL2
    SDL_LIBS = -LC:/vcpkg/installed/x64-windows/lib -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2main
endif

# Agregar flags de SDL2 a CXXFLAGS
CXXFLAGS += $(SDL_CFLAGS) -I$(INCDIR)
DEBUGFLAGS += $(SDL_CFLAGS) -I$(INCDIR)

# Regla principal
all: $(TARGET)

# Crear directorio de objetos si no existe
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Crear directorio de binarios si no existe
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
	@echo "Clean complete"

# Limpiar solo objetos
clean-obj:
	rm -rf $(OBJDIR)
	@echo "Object files cleaned"

# Ejecutar el juego
run: $(TARGET)
	cd "c:\Users\Inei\Desktop\snake_game-main (1)\snake_game-main" && $(BINDIR)/$(notdir $(TARGET))

# Instalar dependencias (para sistemas Unix-like)
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

# Copiar assets al directorio de build (ELIMINADO - assets deben estar en raíz)
# copy-assets: | $(BINDIR)
#	cp -r $(DATADIR)/images $(BINDIR)/
#	cp -r $(DATADIR)/music $(BINDIR)/
#	@echo "Assets copied to $(BINDIR)"

# Build completo (SIN copiar assets)
build-all: $(TARGET)

# Información del sistema
info:
	@echo "Compiler: $(CXX)"
	@echo "Source files: $(SOURCES)"
	@echo "Object files: $(OBJECTS)"
	@echo "Target: $(TARGET)"
	@echo "SFML CFLAGS: $(SFML_CFLAGS)"
	@echo "SFML LIBS: $(SFML_LIBS)"

# Verificar dependencias
check-deps:
	@echo "Checking SFML dependencies..."
	@pkg-config --exists sfml-graphics && echo "✓ SFML Graphics found" || echo "✗ SFML Graphics not found"
	@pkg-config --exists sfml-audio && echo "✓ SFML Audio found" || echo "✗ SFML Audio not found"
	@pkg-config --exists sfml-system && echo "✓ SFML System found" || echo "✗ SFML System not found"

# Rebuild completo
rebuild: clean $(TARGET)

# Reglas que no crean archivos
.PHONY: all clean clean-obj run install-deps build-all info check-deps debug rebuild

# Prevenir borrado de archivos intermedios
.PRECIOUS: $(OBJDIR)/%.o