#include "InputHandler.hpp"
#include "Game.hpp"
#include <iostream>

InputHandler::InputHandler() : gameInstance(nullptr), isEnabled(true) {
}

InputHandler::~InputHandler() {
    Cleanup();
}

void InputHandler::Initialize(Game* game) {
    gameInstance = game;
    ConfigureDefaultKeys();
}

void InputHandler::ConfigureDefaultKeys() {
    // Configurar teclas de dirección
    MapKeyToDirection(sf::Keyboard::W, Direction::UP);
    MapKeyToDirection(sf::Keyboard::S, Direction::DOWN);
    MapKeyToDirection(sf::Keyboard::A, Direction::LEFT);
    MapKeyToDirection(sf::Keyboard::D, Direction::RIGHT);
    MapKeyToDirection(sf::Keyboard::Up, Direction::UP);
    MapKeyToDirection(sf::Keyboard::Down, Direction::DOWN);
    MapKeyToDirection(sf::Keyboard::Left, Direction::LEFT);
    MapKeyToDirection(sf::Keyboard::Right, Direction::RIGHT);
    
    // Configurar teclas de acción
    MapKeyToAction(sf::Keyboard::Space, [this]() {
        if (gameInstance) {
            if (!gameInstance->IsGameStarted()) {
                gameInstance->StartGame();
            } else if (gameInstance->IsGameOver()) {
                gameInstance->RestartGame();
            }
        }
    });
    
    MapKeyToAction(sf::Keyboard::Enter, [this]() {
        if (gameInstance) {
            if (!gameInstance->IsGameStarted()) {
                gameInstance->StartGame();
            } else if (gameInstance->IsGameOver()) {
                gameInstance->RestartGame();
            }
        }
    });
    
    MapKeyToAction(sf::Keyboard::P, [this]() {
        if (gameInstance && gameInstance->IsGameStarted() && !gameInstance->IsGameOver()) {
            // Implementar pausa
            gameInstance->PauseGame();
        }
    });
    
    MapKeyToAction(sf::Keyboard::Escape, [this]() {
        if (gameInstance) {
            gameInstance->SetRunning(false);
        }
    });
}

void InputHandler::Cleanup() {
    keyToDirectionMap.clear();
    keyActionMap.clear();
    keyState.clear();
    gameInstance = nullptr;
}

void InputHandler::HandleEvents(sf::RenderWindow& window) {
    if (!isEnabled) return;
    
    sf::Event event;
    while (window.pollEvent(event)) {
        ProcessEvent(event);
    }
}

void InputHandler::ProcessEvent(const sf::Event& event) {
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

void InputHandler::ProcessKeyPressed(sf::Keyboard::Key key) {
    UpdateKeyState(key, true);
    
    if (IsDirectionKey(key)) {
        HandleDirectionInput(key);
    } else if (IsActionKey(key)) {
        HandleActionInput(key);
    }
}

void InputHandler::ProcessKeyReleased(sf::Keyboard::Key key) {
    UpdateKeyState(key, false);
}

void InputHandler::ProcessWindowClosed() {
    if (gameInstance) {
        gameInstance->SetRunning(false);
    }
}

void InputHandler::MapKeyToDirection(sf::Keyboard::Key key, Direction direction) {
    keyToDirectionMap[key] = direction;
}

void InputHandler::MapKeyToAction(sf::Keyboard::Key key, std::function<void()> action) {
    keyActionMap[key] = action;
}

void InputHandler::RemoveKeyMapping(sf::Keyboard::Key key) {
    keyToDirectionMap.erase(key);
    keyActionMap.erase(key);
}

void InputHandler::ResetKeyMappings() {
    keyToDirectionMap.clear();
    keyActionMap.clear();
    ConfigureDefaultKeys();
}

void InputHandler::Enable() {
    isEnabled = true;
}

void InputHandler::Disable() {
    isEnabled = false;
}

void InputHandler::ToggleEnabled() {
    isEnabled = !isEnabled;
}

bool InputHandler::IsKeyPressed(sf::Keyboard::Key key) const {
    auto it = keyState.find(key);
    return (it != keyState.end()) ? it->second : false;
}

bool InputHandler::IsAnyKeyPressed() const {
    for (const auto& pair : keyState) {
        if (pair.second) {
            return true;
        }
    }
    return false;
}

bool InputHandler::IsValidDirectionKey(sf::Keyboard::Key key) const {
    return keyToDirectionMap.find(key) != keyToDirectionMap.end();
}

bool InputHandler::IsValidActionKey(sf::Keyboard::Key key) const {
    return keyActionMap.find(key) != keyActionMap.end();
}

bool InputHandler::CanChangeDirection(Direction newDirection, Direction currentDirection) const {
    switch (newDirection) {
        case Direction::UP:
            return currentDirection != Direction::DOWN;
        case Direction::DOWN:
            return currentDirection != Direction::UP;
        case Direction::LEFT:
            return currentDirection != Direction::RIGHT;
        case Direction::RIGHT:
            return currentDirection != Direction::LEFT;
    }
    return false;
}

Direction InputHandler::GetDirectionFromKey(sf::Keyboard::Key key) const {
    auto it = keyToDirectionMap.find(key);
    return (it != keyToDirectionMap.end()) ? it->second : Direction::UP;
}

// Métodos privados
void InputHandler::UpdateKeyState(sf::Keyboard::Key key, bool isPressed) {
    keyState[key] = isPressed;
}

void InputHandler::ExecuteKeyAction(sf::Keyboard::Key key) {
    auto it = keyActionMap.find(key);
    if (it != keyActionMap.end() && it->second) {
        it->second();
    }
}

bool InputHandler::IsDirectionKey(sf::Keyboard::Key key) const {
    return IsValidDirectionKey(key);
}

bool InputHandler::IsActionKey(sf::Keyboard::Key key) const {
    return IsValidActionKey(key);
}

void InputHandler::HandleDirectionInput(sf::Keyboard::Key key) {
    if (!gameInstance) return;
    
    // Solo procesar entrada de dirección si el juego está en marcha
    if (gameInstance->IsGameStarted() && !gameInstance->IsGameOver()) {
        Direction newDirection = GetDirectionFromKey(key);
        gameInstance->ChangeSnakeDirection(newDirection);
    }
}

void InputHandler::HandleActionInput(sf::Keyboard::Key key) {
    ExecuteKeyAction(key);
}