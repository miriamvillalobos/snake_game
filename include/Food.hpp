#ifndef FOOD_HPP
#define FOOD_HPP

#include "Snake.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

// Forward declarations
class Game;
class GameRenderer; FOOD_HPP
#define FOOD_HPP

#include "Snake.hpp"

// Forward declaration
class GameRenderer;

/**
 * @brief Clase que representa la comida en el juego
 * 
 * Maneja la generación de posiciones aleatorias para la comida
 * y la detección de cuando es consumida por la serpiente.
 */
class Food {
private:
    Position position;
    bool isActive;
    int nutritionalValue;
    
public:
    Food();
    ~Food();
    
    // Métodos de generación (verbos)
    void GenerateNewPosition(int gridWidth, int gridHeight, const Snake& snake);
    void Respawn(int gridWidth, int gridHeight, const Snake& snake);
    void Consume();
    
    // Métodos de renderizado
    void Render(GameRenderer* renderer);
    void Update();
    
    // Métodos de validación
    bool IsEatenBy(const Snake& snake) const;
    bool IsValidPosition(const Position& pos, const Snake& snake) const;
    
    // Getters
    const Position& GetPosition() const { return position; }
    bool IsActive() const { return isActive; }
    int GetNutritionalValue() const { return nutritionalValue; }
    
    // Setters
    void SetPosition(const Position& newPosition) { position = newPosition; }
    void SetActive(bool value) { isActive = value; }
    void SetNutritionalValue(int value) { nutritionalValue = value; }
    
private:
    // Métodos privados auxiliares
    Position GenerateRandomPosition(int gridWidth, int gridHeight) const;
    bool IsPositionOccupied(const Position& pos, const Snake& snake) const;
};

#endif // FOOD_HPP