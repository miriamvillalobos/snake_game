#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <functional>
#include "Snake.hpp"

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