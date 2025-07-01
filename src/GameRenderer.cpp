#include "GameRenderer.hpp"
#include "Snake.hpp"
#include "Food.hpp"
#include <iostream>

GameRenderer::GameRenderer() : window(nullptr), gridSize(20) {  // Aumentado de 15 a 20 píxeles
}

GameRenderer::~GameRenderer() {
    Cleanup();
}

bool GameRenderer::Initialize(sf::RenderWindow* renderWindow) {
    if (!renderWindow) {
        std::cerr << "Window is null!" << std::endl;
        return false;
    }
    
    window = renderWindow;
    
    // Cargar fuente por defecto
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Could not load font, using default font" << std::endl;
        // SFML cargará la fuente por defecto automáticamente
        // Por ahora continuamos sin fuente personalizada
    }
    
    return true;
}

bool GameRenderer::LoadAssets() {
    // Cargar texturas de la serpiente
    if (!LoadSnakeTextures()) {
        std::cerr << "Failed to load snake textures!" << std::endl;
        return false;
    }
    
    // Cargar texturas de UI
    if (!LoadUITextures()) {
        std::cerr << "Failed to load UI textures!" << std::endl;
        return false;
    }
    
    // Cargar texturas de números
    if (!LoadNumberTextures()) {
        std::cerr << "Failed to load number textures!" << std::endl;
        return false;
    }
    
    return true;
}

void GameRenderer::Cleanup() {
    textures.clear();
    sprites.clear();
}

void GameRenderer::Clear() {
    window->clear(sf::Color::Black);
}

void GameRenderer::Present() {
    window->display();
}

void GameRenderer::RenderBackground() {
    sf::Sprite* bgSprite = GetSprite("background");
    if (bgSprite) {
        // Escalar el fondo para que cubra toda la ventana
        float scaleX = 1200.0f / bgSprite->getTexture()->getSize().x;
        float scaleY = 900.0f / bgSprite->getTexture()->getSize().y;
        bgSprite->setScale(scaleX, scaleY);
        window->draw(*bgSprite);
    } else {
        // Fondo por defecto
        window->clear(sf::Color(50, 50, 50));
    }
}

void GameRenderer::RenderSnake(const Snake& snake) {
    const auto& segments = snake.GetSegments();
    
    for (size_t i = 0; i < segments.size(); i++) {
        sf::Vector2f position = CalculateGridPosition(segments[i].x, segments[i].y);
        
        if (i == 0) {
            // Cabeza - elegir sprite según dirección
            std::string headSpriteName = "snake_head";
            switch (snake.GetCurrentDirection()) {
                case Direction::UP:
                    headSpriteName = "snake_head";      // cabeza.png (frontal)
                    break;
                case Direction::DOWN:
                    headSpriteName = "snake_head_back"; // trasera.png
                    break;
                case Direction::LEFT:
                    headSpriteName = "snake_head_left"; // izquierda.png
                    break;
                case Direction::RIGHT:
                    headSpriteName = "snake_head_right"; // derecha.png
                    break;
            }
            
            RenderSpriteAt(headSpriteName, position);
        } else if (i == segments.size() - 1 && snake.GetGrowthFrames() > 0) {
            // Cola recién crecida - usar segmento.png para simular crecimiento
            RenderSpriteAt("snake_segment", position);
        } else {
            // Cuerpo - determinar orientación según segmentos adyacentes
            std::string bodySprite = "snake_body"; // Por defecto (horizontal)
            
            if (i > 0 && i < segments.size() - 1) {
                // Segmento del medio - comparar con segmentos anterior y siguiente
                const auto& prev = segments[i - 1];
                const auto& next = segments[i + 1];
                
                // Si el movimiento es vertical (mismo X, diferente Y)
                if ((prev.x == segments[i].x && next.x == segments[i].x) ||
                    (prev.x == segments[i].x && prev.y != segments[i].y) ||
                    (next.x == segments[i].x && next.y != segments[i].y)) {
                    bodySprite = "snake_body_vertical";
                }
            } else if (i > 0) {
                // Último segmento - comparar solo con el anterior
                const auto& prev = segments[i - 1];
                if (prev.x == segments[i].x && prev.y != segments[i].y) {
                    bodySprite = "snake_body_vertical";
                }
            }
            
            RenderSpriteAt(bodySprite, position);
        }
    }
}

void GameRenderer::RenderFood(const Food& food) {
    if (!food.IsActive()) return;
    
    sf::Vector2f position = CalculateGridPosition(food.GetPosition().x, food.GetPosition().y);
    RenderSpriteAt("food", position);
}

void GameRenderer::RenderScore(int score) {
    std::string scoreStr = std::to_string(score);
    float x = 20.0f;  // Margen desde el borde izquierdo
    float y = 20.0f;  // Margen desde el borde superior
    
    for (char digit : scoreStr) {
        RenderDigit(digit - '0', x, y);
        x += 50.0f;  // Espaciado entre dígitos ajustado para mejor visualización
    }
}

void GameRenderer::RenderStartScreen() {
    sf::Sprite* startSprite = GetSprite("start_screen");
    if (startSprite) {
        // Escalar la imagen de inicio para que se ajuste a la nueva resolución
        float scaleX = 1200.0f / startSprite->getTexture()->getSize().x;
        float scaleY = 900.0f / startSprite->getTexture()->getSize().y;
        startSprite->setScale(scaleX, scaleY);
        window->draw(*startSprite);
    } else {
        window->clear(sf::Color(100, 100, 100));
        RenderText("PRESS ANY KEY TO START", 400.0f, 450.0f, sf::Color::White);
    }
}

void GameRenderer::RenderGameOverScreen() {
    sf::Sprite* gameOverSprite = GetSprite("game_over");
    if (gameOverSprite) {
        // Escalar la imagen de game over para que se ajuste a la nueva resolución
        float scaleX = 1200.0f / gameOverSprite->getTexture()->getSize().x;
        float scaleY = 900.0f / gameOverSprite->getTexture()->getSize().y;
        gameOverSprite->setScale(scaleX, scaleY);
        window->draw(*gameOverSprite);
    } else {
        window->clear(sf::Color(150, 50, 50));
        RenderText("GAME OVER", 500.0f, 400.0f, sf::Color::White);
        RenderText("PRESS ANY KEY TO RESTART", 380.0f, 500.0f, sf::Color::White);
    }
}

void GameRenderer::RenderPauseScreen() {
    sf::RectangleShape overlay(sf::Vector2f(1200, 900));  // Ajustado a la nueva resolución
    overlay.setFillColor(sf::Color(0, 0, 0, 128));
    window->draw(overlay);
    
    RenderText("PAUSED", 550.0f, 450.0f, sf::Color::White);  // Centrado en la nueva resolución
}

void GameRenderer::RenderGameBounds() {
    // Definir dimensiones del área de juego
    const float margin = 100.0f;  // Reducido de 200 a 100 píxeles
    const float gameAreaX = margin;
    const float gameAreaY = margin;
    const float gameAreaWidth = 1200.0f - (2 * margin);  // 1000 píxeles
    const float gameAreaHeight = 900.0f - (2 * margin);  // 700 píxeles
    
    // Color y grosor del borde
    const float borderThickness = 3.0f;
    const sf::Color borderColor(255, 255, 255, 0); // Blanco completamente transparente (invisible)
    
    // Renderizar los cuatro bordes del área de juego
    
    // Borde superior
    sf::RectangleShape topBorder(sf::Vector2f(gameAreaWidth + 2 * borderThickness, borderThickness));
    topBorder.setPosition(gameAreaX - borderThickness, gameAreaY - borderThickness);
    topBorder.setFillColor(borderColor);
    window->draw(topBorder);
    
    // Borde inferior
    sf::RectangleShape bottomBorder(sf::Vector2f(gameAreaWidth + 2 * borderThickness, borderThickness));
    bottomBorder.setPosition(gameAreaX - borderThickness, gameAreaY + gameAreaHeight);
    bottomBorder.setFillColor(borderColor);
    window->draw(bottomBorder);
    
    // Borde izquierdo
    sf::RectangleShape leftBorder(sf::Vector2f(borderThickness, gameAreaHeight));
    leftBorder.setPosition(gameAreaX - borderThickness, gameAreaY);
    leftBorder.setFillColor(borderColor);
    window->draw(leftBorder);
    
    // Borde derecho
    sf::RectangleShape rightBorder(sf::Vector2f(borderThickness, gameAreaHeight));
    rightBorder.setPosition(gameAreaX + gameAreaWidth, gameAreaY);
    rightBorder.setFillColor(borderColor);
    window->draw(rightBorder);
}

bool GameRenderer::LoadTexture(const std::string& name, const std::string& path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return false;
    }
    
    textures[name] = std::move(texture);
    return true;
}

sf::Texture* GameRenderer::GetTexture(const std::string& name) {
    auto it = textures.find(name);
    return (it != textures.end()) ? &it->second : nullptr;
}

sf::Sprite* GameRenderer::GetSprite(const std::string& name) {
    auto it = sprites.find(name);
    return (it != sprites.end()) ? &it->second : nullptr;
}

void GameRenderer::CreateSprite(const std::string& name, const std::string& textureName) {
    sf::Texture* texture = GetTexture(textureName);
    if (texture) {
        sprites[name] = sf::Sprite(*texture);
    }
}

void GameRenderer::RenderSprite(const std::string& spriteName, float x, float y) {
    sf::Sprite* sprite = GetSprite(spriteName);
    if (sprite) {
        sprite->setPosition(x, y);
        
        // Escalar sprites de la serpiente para que se ajusten al tamaño de grilla (15x15)
        if (spriteName.find("snake_") == 0) {
            float scaleX = static_cast<float>(gridSize) / sprite->getTexture()->getSize().x;
            float scaleY = static_cast<float>(gridSize) / sprite->getTexture()->getSize().y;
            sprite->setScale(scaleX, scaleY);
        }
        // Escalar sprites de comida también
        else if (spriteName == "food") {
            float scaleX = static_cast<float>(gridSize) / sprite->getTexture()->getSize().x;
            float scaleY = static_cast<float>(gridSize) / sprite->getTexture()->getSize().y;
            sprite->setScale(scaleX, scaleY);
        }
        // Mantener escala original para otros sprites (números, etc.)
        else {
            sprite->setScale(1.0f, 1.0f);
        }
        
        window->draw(*sprite);
    } else {
        // Fallback: renderizar rectángulo de color
        sf::RectangleShape rect(sf::Vector2f(gridSize, gridSize));
        rect.setPosition(x, y);
        rect.setFillColor(sf::Color::Green);
        window->draw(rect);
    }
}

void GameRenderer::RenderSpriteAt(const std::string& spriteName, const sf::Vector2f& position) {
    RenderSprite(spriteName, position.x, position.y);
}

void GameRenderer::RenderRect(const sf::FloatRect& rect, const sf::Color& color) {
    sf::RectangleShape rectangle(sf::Vector2f(rect.width, rect.height));
    rectangle.setPosition(rect.left, rect.top);
    rectangle.setFillColor(color);
    window->draw(rectangle);
}

void GameRenderer::RenderText(const std::string& text, float x, float y, const sf::Color& color) {
    sf::Text sfText;
    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(32);  // Aumentado de 24 a 32 para mejor legibilidad
    sfText.setFillColor(color);
    sfText.setPosition(x, y);
    window->draw(sfText);
}

// Métodos privados
bool GameRenderer::LoadSnakeTextures() {
    LoadTexture("snake_head", "assets/images/cabeza.png");
    LoadTexture("snake_head_right", "assets/images/derecha.png");
    LoadTexture("snake_head_left", "assets/images/izquierda.png");
    LoadTexture("snake_head_back", "assets/images/trasera.png");
    LoadTexture("snake_body", "assets/images/cuerpo.png");
    LoadTexture("snake_body_vertical", "assets/images/cuerpovertical.png");  // Nueva textura para cuerpo vertical
    LoadTexture("snake_segment", "assets/images/segmento.png");
    
    // Crear sprites
    CreateSprite("snake_head", "snake_head");
    CreateSprite("snake_head_right", "snake_head_right");
    CreateSprite("snake_head_left", "snake_head_left");
    CreateSprite("snake_head_back", "snake_head_back");
    CreateSprite("snake_body", "snake_body");
    CreateSprite("snake_body_vertical", "snake_body_vertical");  // Sprite para cuerpo vertical
    CreateSprite("snake_segment", "snake_segment");
    
    return true;
}

bool GameRenderer::LoadUITextures() {
    LoadTexture("background", "assets/images/fondo.jpg");
    LoadTexture("food", "assets/images/comida.png");
    LoadTexture("start_screen", "assets/images/pantalla de inicio.jpg");
    LoadTexture("game_over", "assets/images/pantalla final.jpg");
    
    // Crear sprites
    CreateSprite("background", "background");
    CreateSprite("food", "food");
    CreateSprite("start_screen", "start_screen");
    CreateSprite("game_over", "game_over");
    
    return true;
}

bool GameRenderer::LoadNumberTextures() {
    LoadTexture("num_0", "assets/images/cero.png");
    LoadTexture("num_1", "assets/images/uno.png");
    LoadTexture("num_2", "assets/images/dos.png");
    LoadTexture("num_3", "assets/images/tres.png");
    LoadTexture("num_4", "assets/images/cuatro.png");
    LoadTexture("num_5", "assets/images/cinco.png");
    LoadTexture("num_6", "assets/images/seis.png");
    LoadTexture("num_7", "assets/images/siete.png");
    LoadTexture("num_8", "assets/images/ocho.png");
    LoadTexture("num_9", "assets/images/nueve.png");
    
    // Crear sprites para números
    for (int i = 0; i <= 9; i++) {
        CreateSprite("num_" + std::to_string(i), "num_" + std::to_string(i));
    }
    
    return true;
}

void GameRenderer::RenderDigit(int digit, float x, float y) {
    if (digit < 0 || digit > 9) return;
    
    std::string spriteName = "num_" + std::to_string(digit);
    sf::Sprite* sprite = GetSprite(spriteName);
    if (sprite) {
        sprite->setPosition(x, y);
        
        // Escalar los números del score para que tengan un tamaño apropiado
        // Hacer los números más pequeños pero legibles (aproximadamente 40x40 píxeles)
        float targetSize = 40.0f;
        float scaleX = targetSize / sprite->getTexture()->getSize().x;
        float scaleY = targetSize / sprite->getTexture()->getSize().y;
        sprite->setScale(scaleX, scaleY);
        
        window->draw(*sprite);
    } else {
        // Fallback: usar texto si no hay sprite disponible
        RenderText(std::to_string(digit), x, y, sf::Color::White);
    }
}

sf::Vector2f GameRenderer::CalculateGridPosition(int gridX, int gridY) const {
    const float margin = GetGameAreaMargin();
    return sf::Vector2f(margin + (gridX * gridSize), margin + (gridY * gridSize));
}