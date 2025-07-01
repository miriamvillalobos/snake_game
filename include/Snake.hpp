#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include <string>

// Forward declaration
class GameRenderer;

/**
 * @brief Enumeración para las direcciones de movimiento
 */
enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

/**
 * @brief Estructura para representar una posición en la grilla
 */
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

/**
 * @brief Clase que representa la serpiente del juego
 * 
 * Maneja el movimiento, crecimiento y detección de colisiones
 * de la serpiente.
 */
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
    
    // Setters
    void SetHasGrown(bool value) { hasGrown = value; }
    
private:
    // Métodos privados auxiliares
    void AddSegment(const Position& position);
    void RemoveTail();
    Position CalculateNextHeadPosition() const;
    bool CanChangeDirection(Direction newDirection, Direction currentDir) const;
    std::string GetHeadSpriteForDirection() const;
};

#endif // SNAKE_HPP