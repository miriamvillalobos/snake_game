# Snake Game Makefile

# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Directorios
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

# Archivos fuente y objeto
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/SnakeGame

# Librerías SFML
SFML_LIBS = -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-window
SFML_CFLAGS =

# Para Windows (si aplica)
ifeq ($(OS),Windows_NT)
    TARGET := $(TARGET).exe
    SFML_CFLAGS = -IC:/vcpkg/installed/x64-windows/include
    SFML_LIBS = -LC:/vcpkg/installed/x64-windows/lib -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-window
endif

# Agregar SFML a los flags
CXXFLAGS += $(SFML_CFLAGS) -I$(INCDIR)

# Regla principal
all: $(TARGET)

# Crear directorios si no existen
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Crear ejecutable
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $(OBJECTS) -o $@ $(SFML_LIBS)
	@echo "✅ Build complete: $(TARGET)"

# Compilar objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Debug
debug: CXXFLAGS = -std=c++17 -Wall -Wextra -g -DDEBUG $(SFML_CFLAGS) -I$(INCDIR)
debug: $(TARGET)

# Limpiar
clean:
	rm -rf $(OBJDIR) $(BINDIR)
	@echo "🧹 Clean complete"

# Ejecutar
run: $(TARGET)
	./$(TARGET)

# Instalar dependencias (Linux/macOS)
install-deps:
	@echo "📦 Installing SFML dependencies..."
	@if command -v apt-get >/dev/null 2>&1; then \
		sudo apt-get update && sudo apt-get install -y libsfml-dev; \
	elif command -v yum >/dev/null 2>&1; then \
		sudo yum install -y SFML-devel; \
	elif command -v pacman >/dev/null 2>&1; then \
		sudo pacman -S sfml; \
	elif command -v brew >/dev/null 2>&1; then \
		brew install sfml; \
	else \
		echo "⚠️ Package manager not recognized. Please install SFML manually."; \
	fi

.PHONY: all clean run install-deps debug
.PRECIOUS: $(OBJDIR)/%.o
