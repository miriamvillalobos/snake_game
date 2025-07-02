#include "Food.hpp"
#include "GameRenderer.hpp"
#include <random>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

Food::Food() : position(0, 0), isActive(true), nutritionalValue(10) {
}

Food::~Food() {
    // Destructor vacío, SFML maneja automáticamente los recursos
}

void Food::GenerateNewPosition(int gridWidth, int gridHeight, const Snake& snake) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(0, gridWidth - 1);
    std::uniform_int_distribution<> distY(0, gridHeight - 1);
    
    Position newPos;
    bool validPosition = false;
    
    // Keep generating positions until we find one not occupied by the snake
    while (!validPosition) {
        newPos.x = distX(gen);
        newPos.y = distY(gen);
        
        validPosition = true;
        
        // Check if position conflicts with snake segments
        const auto& segments = snake.GetSegments();
        for (const auto& segment : segments) {
            if (newPos == segment) {
                validPosition = false;
                break;
            }
        }
    }
    
    position = newPos;
}

void Food::Render(GameRenderer* renderer) {
    renderer->RenderFood(*this);
}

void Food::Update() {
    // Por ahora, la comida no necesita actualización
    // Esto se puede expandir para comida especial, animaciones, etc.
}

bool Food::IsEatenBy(const Snake& snake) const {
    return position == snake.GetHead();
}