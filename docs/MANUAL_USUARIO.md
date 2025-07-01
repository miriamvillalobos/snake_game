# Manual de Usuario - Snake Game

## 📋 Tabla de Contenidos
1. [Introducción](#introducción)
2. [Requisitos del Sistema](#requisitos-del-sistema)
3. [Instalación](#instalación)
4. [Cómo Jugar](#cómo-jugar)
5. [Controles](#controles)
6. [Elementos del Juego](#elementos-del-juego)
7. [Sistema de Puntuación](#sistema-de-puntuación)
8. [Pantallas del Juego](#pantallas-del-juego)
9. [Configuración de Audio](#configuración-de-audio)
10. [Solución de Problemas](#solución-de-problemas)
11. [Créditos](#créditos)

## 🐍 Introducción

*Snake Game* es una versión moderna del clásico juego de la serpiente. Controla una serpiente que debe comer comida para crecer, evitando chocar consigo misma o con los bordes del área de juego.

### Características principales:
- 🎮 Gráficos mejorados con sprites personalizados
- 🎵 Efectos de sonido y música de fondo
- 🏆 Sistema de puntuación
- 📱 Interfaz intuitiva
- 🎨 Animaciones fluidas

## 💻 Requisitos del Sistema

### Mínimos:
- *Sistema Operativo*: Linux (Ubuntu 18.04+, Fedora 30+, Arch Linux)
- *Procesador*: Intel/AMD 1.5 GHz o superior
- *Memoria RAM*: 512 MB
- *Gráficos*: Soporte OpenGL 2.1
- *Almacenamiento*: 50 MB de espacio libre
- *Audio*: Tarjeta de sonido compatible

### Recomendados:
- *Procesador*: Intel/AMD 2.0 GHz o superior
- *Memoria RAM*: 1 GB
- *Gráficos*: Tarjeta gráfica dedicada
- *Audio*: Sistema de audio estéreo

## 🔧 Instalación

### Opción 1: Ejecutar directamente
bash
# Navegar a la carpeta del juego
cd snake_game-main

# Ejecutar el juego
./bin/SnakeGame


### Opción 2: Compilar desde código fuente
bash
# Instalar dependencias (Ubuntu/Debian)
sudo apt update
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev build-essential

# Compilar el juego
make clean
make

# Ejecutar
make run


### Verificar instalación:
Si el juego se ejecuta correctamente, verás la pantalla de inicio con música de fondo.

## 🎮 Cómo Jugar

### Objetivo:
Controla la serpiente para comer la mayor cantidad de comida posible sin chocar con:
- Los bordes del área de juego
- Tu propio cuerpo

### Mecánicas básicas:
1. *Movimiento*: La serpiente se mueve constantemente en la dirección actual
2. *Crecimiento*: Al comer comida, la serpiente crece un segmento
3. *Velocidad*: La serpiente mantiene velocidad constante
4. *Colisiones*: El juego termina si la serpiente choca

### Flujo del juego:
1. Presiona cualquier tecla en el menú principal
2. Usa las flechas para mover la serpiente
3. Come la comida roja que aparece aleatoriamente
4. Evita chocar con los bordes o contigo mismo
5. Acumula la mayor puntuación posible

## ⌨️ Controles

### Movimiento:
| Tecla | Acción |
|-------|--------|
| ↑ o W | Mover hacia arriba |
| ↓ o S | Mover hacia abajo |
| ← o A | Mover hacia la izquierda |
| → o D | Mover hacia la derecha |

### Controles de juego:
| Tecla | Acción |
|-------|--------|
| SPACE | Pausar/Reanudar juego |
| R | Reiniciar partida (en Game Over) |
| ESC | Salir del juego |
| M | Activar/Desactivar música |

### Notas importantes:
- ⚠️ *No puedes moverte en dirección opuesta inmediatamente* (ej: de arriba a abajo directamente)
- ⚠️ *Los movimientos se registran instantáneamente*, evita presionar teclas muy rápido
- ✅ *Puedes cambiar de dirección mientras la serpiente se mueve*

## 🎯 Elementos del Juego

### La Serpiente:
- *Cabeza*: Sprite distintivo que indica la dirección
- *Cuerpo*: Segmentos que siguen a la cabeza
- *Cola*: Último segmento de la serpiente

### Tipos de segmentos:
- 🐍 *Cabeza direccional*: Cambia según la dirección (arriba, abajo, izquierda, derecha)
- 🟢 *Cuerpo vertical*: Para movimientos verticales
- 🟢 *Cuerpo horizontal*: Para movimientos horizontales
- 🔸 *Segmentos nuevos*: Aparecen al crecer

### La Comida:
- 🍎 *Comida normal*: Aparece aleatoriamente en el tablero
- ✨ *Efecto visual*: Animación al ser consumida
- 🔄 *Respawn*: Nueva comida aparece inmediatamente después de comer

### Área de Juego:
- 📐 *Dimensiones*: 1200x900 píxeles
- 🔲 *Grilla*: 20x20 píxeles por celda
- 🚧 *Límites invisibles*: Margen configurable alrededor del área
- 🎨 *Fondo*: Imagen de fondo personalizada

## 🏆 Sistema de Puntuación

### Puntuación básica:
- *Por cada comida*: +10 puntos
- *Visualización*: Esquina superior izquierda
- *Formato*: Dígitos individuales con sprites

### Cálculo de puntuación:

Puntuación = Número de comidas × 10 puntos


### Ejemplos:
- 1 comida = 10 puntos
- 5 comidas = 50 puntos
- 20 comidas = 200 puntos

### Récord personal:
- El juego guarda automáticamente tu mejor puntuación
- Se muestra en la pantalla de Game Over
- Persiste entre sesiones de juego

## 📺 Pantallas del Juego

### 1. Pantalla de Inicio:
- *Fondo*: Imagen de bienvenida
- *Música*: Tema de inicio
- *Acción*: Presiona cualquier tecla para comenzar

### 2. Pantalla de Juego:
- *Elementos visibles*:
  - Serpiente con sprites direccionales
  - Comida
  - Puntuación actual
  - Área de juego delimitada
- *Música*: Tema de fondo durante el juego

### 3. Pantalla de Game Over:
- *Información mostrada*:
  - "Game Over"
  - Puntuación final
  - Mejor puntuación
- *Opciones*:
  - R: Reiniciar partida
  - ESC: Salir del juego
- *Sonido*: Efecto de Game Over

## 🔊 Configuración de Audio

### Efectos de sonido:
- 🎵 *Música de inicio*: Al abrir el juego
- 🎶 *Música de fondo*: Durante la partida
- 🍎 *Efecto de comer*: Al consumir comida
- 💥 *Efecto de choque*: Al colisionar
- 🎺 *Sonido de Game Over*: Al terminar la partida

### Controles de audio:
- *Activar/Desactivar música*: Tecla M
- *Volumen*: Configurado automáticamente
- *Formato soportado*: OGG para efectos y música

### Archivos de audio incluidos:

assets/music/
├── inicio.ogg          # Música de bienvenida
├── musica_fondo.ogg    # Música durante el juego
├── comer.ogg           # Efecto al comer
├── choque.ogg          # Efecto de colisión
└── gameover.ogg        # Sonido de Game Over


## 🛠️ Solución de Problemas

### Problemas comunes:

#### El juego no inicia:
bash
# Verificar dependencias
ldd bin/SnakeGame

# Instalar librerías faltantes (Ubuntu)
sudo apt install libsdl2-2.0-0 libsdl2-image-2.0-0 libsdl2-mixer-2.0-0


#### No hay sonido:
- Verificar que el sistema de audio esté funcionando
- Comprobar que los archivos de audio existen en assets/music/
- Probar con auriculares/altavoces externos

#### Rendimiento lento:
- Cerrar otros programas que consuman recursos
- Verificar que el sistema cumple los requisitos mínimos
- Actualizar drivers de gráficos

#### Controles no responden:
- Verificar que la ventana del juego esté en foco
- Probar con diferentes teclas (flechas vs WASD)
- Reiniciar el juego

### Archivos importantes:

snake_game/
├── bin/SnakeGame           # Ejecutable principal
├── assets/                 # Recursos del juego
│   ├── images/            # Sprites y gráficos
│   └── music/             # Audio y efectos
└── docs/                  # Documentación


### Reportar problemas:
Si encuentras errores no documentados:
1. Anota la versión del sistema operativo
2. Describe los pasos para reproducir el problema
3. Incluye cualquier mensaje de error
4. Verifica que tengas las dependencias instaladas

## 🎖️ Créditos

### Desarrollo:
- *Programación*: Desarrollo en C++ con SDL2
- *Gráficos*: Sprites personalizados
- *Audio*: Efectos y música originales
- *Documentación*: Manual completo de usuario

### Tecnologías utilizadas:
- *Lenguaje*: C++17
- *Gráficos*: SDL2, SDL2_image
- *Audio*: SDL2_mixer
- *Build*: GNU Make
- *Plataforma*: Linux

### Licencias:
- Código fuente: Proyecto educativo
- Assets gráficos: Creación propia
- Audio: Recursos libres de derechos

---

## 📞 Contacto y Soporte

Para soporte técnico o sugerencias:
- Consulta la documentación en la carpeta docs/
- Revisa el código fuente para entender el funcionamiento
- Verifica los requisitos del sistema antes de reportar problemas

*¡Disfruta jugando Snake Game!* 🐍🎮

---

Manual de Usuario v1.0