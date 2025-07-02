#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <functional>
#include "Snake.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Snake.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

// Forward declaration
class Game;

/**
 * @brief Enumeración para los tipos de entrada del usuario
 */
enum class InputType {
    KEY_PRESS,
    KEY_RELEASE,
    QUIT_EVENT
};

/**
 * @brief Estructura para representar una entrada del usuario
 */
struct InputEvent {
    InputType type;
    sf::Keyboard::Key key;
    bool isPressed;
    
    InputEvent(InputType t = InputType::KEY_PRESS, sf::Keyboard::Key k = sf::Keyboard::Unknown, bool pressed = false)
        : type(t), key(k), isPressed(pressed) {}
};

/**
 * @brief Clase encargada del manejo de entrada del usuario
 * 
 * Procesa eventos del teclado y los traduce a acciones del juego.
 * Maneja configuraciones de teclas y estado de entrada.
 */
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
    
private:
    // Métodos privados auxiliares
    void UpdateKeyState(sf::Keyboard::Key key, bool isPressed);
    void ExecuteKeyAction(sf::Keyboard::Key key);
    bool IsDirectionKey(sf::Keyboard::Key key) const;
    bool IsActionKey(sf::Keyboard::Key key) const;
    void HandleDirectionInput(sf::Keyboard::Key key);
    void HandleActionInput(sf::Keyboard::Key key);
};

#endif // INPUT_HANDLER_HPP
#include "Snake.hpp"
#include "GameRenderer.hpp"
#include <algorithm>

Snake::Snake(int startX, int startY) 
    : currentDirection(Direction::RIGHT), nextDirection(Direction::RIGHT), 
      hasGrown(false), length(3), growthFrames(0) {
    segments.clear();
    segments.push_back(Position(startX, startY));
    segments.push_back(Position(startX - 1, startY));
    segments.push_back(Position(startX - 2, startY));
}

Snake::~Snake() {
    segments.clear();
}

void Snake::Move() {
    // Calcular nueva posición de la cabeza
    Position newHead = CalculateNextHeadPosition();
    
    // Agregar nueva cabeza
    AddSegment(newHead);
    
    // Remover cola si no ha crecido
    if (!hasGrown) {
        RemoveTail();
    } else {
        // La serpiente ha crecido, mantener todos los segmentos
        // El flag se mantendrá activo por un frame para mostrar el segmento de crecimiento
        hasGrown = false;
        length++;
    }
}

void Snake::ChangeDirection(Direction newDirection) {
    if (IsValidDirection(newDirection)) {
        nextDirection = newDirection;
    }
}

void Snake::Grow() {
    hasGrown = true;
    growthFrames = 3;  // Mostrar el efecto de crecimiento por 3 frames
}

void Snake::Reset(int startX, int startY) {
    segments.clear();
    segments.push_back(Position(startX, startY));
    segments.push_back(Position(startX - 1, startY));
    segments.push_back(Position(startX - 2, startY));
    
    currentDirection = Direction::RIGHT;
    nextDirection = Direction::RIGHT;
    hasGrown = false;
    length = 3;
    growthFrames = 0;
}

void Snake::Update() {
    // Actualizar dirección
    currentDirection = nextDirection;
    
    // Decrementar contador de frames de crecimiento
    if (growthFrames > 0) {
        growthFrames--;
    }
    
    // Mover serpiente
    Move();
}

void Snake::Render(GameRenderer* renderer) {
    if (!renderer) return;
    
    for (size_t i = 0; i < segments.size(); i++) {
        float x = segments[i].x * renderer->GetGridSize();
        float y = segments[i].y * renderer->GetGridSize();
        
        if (i == 0) {
            // Renderizar cabeza con dirección
            std::string headSprite = GetHeadSpriteForDirection();
            renderer->RenderSprite(headSprite, x, y);
        } else {
            // Renderizar cuerpo
            renderer->RenderSprite("snake_body", x, y);
        }
    }
}

bool Snake::IsValidDirection(Direction direction) const {
    return CanChangeDirection(direction, currentDirection);
}

bool Snake::CheckSelfCollision() const {
    const Position& head = segments[0];
    
    // Verificar colisión con el cuerpo (empezar desde el índice 1)
    for (size_t i = 1; i < segments.size(); i++) {
        if (head == segments[i]) {
            return true;
        }
    }
    
    return false;
}

bool Snake::CheckWallCollision(int gridWidth, int gridHeight) const {
    const Position& head = segments[0];
    
    return (head.x < 0 || head.x >= gridWidth || 
            head.y < 0 || head.y >= gridHeight);
}

bool Snake::CheckCollisionAt(const Position& position) const {
    for (const auto& segment : segments) {
        if (segment == position) {
            return true;
        }
    }
    return false;
}

// Métodos privados
void Snake::AddSegment(const Position& position) {
    segments.insert(segments.begin(), position);
}

void Snake::RemoveTail() {
    if (!segments.empty()) {
        segments.pop_back();
    }
}

Position Snake::CalculateNextHeadPosition() const {
    Position currentHead = segments[0];
    Position newHead = currentHead;
    
    switch (currentDirection) {
        case Direction::UP:
            newHead.y--;
            break;
        case Direction::DOWN:
            newHead.y++;
            break;
        case Direction::LEFT:
            newHead.x--;
            break;
        case Direction::RIGHT:
            newHead.x++;
            break;
    }
    
    return newHead;
}

bool Snake::CanChangeDirection(Direction newDirection, Direction currentDir) const {
    switch (newDirection) {
        case Direction::UP:
            return currentDir != Direction::DOWN;
        case Direction::DOWN:
            return currentDir != Direction::UP;
        case Direction::LEFT:
            return currentDir != Direction::RIGHT;
        case Direction::RIGHT:
            return currentDir != Direction::LEFT;
    }
    return false;
}

std::string Snake::GetHeadSpriteForDirection() const {
    switch (currentDirection) {
        case Direction::UP:
            return "snake_head";        // cabeza.png (sprite base)
        case Direction::DOWN:
            return "snake_head_back";   // trasera.png
        case Direction::LEFT:
            return "snake_head_left";   // izquierda.png
        case Direction::RIGHT:
            return "snake_head_right";  // derecha.png
        default:
            return "snake_head";        // cabeza.png como default
    }
}