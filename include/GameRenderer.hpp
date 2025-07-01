#ifndef GAME_RENDERER_HPP
#define GAME_RENDERER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

// Forward declarations
class Snake;
class Food;

/**
 * @brief Clase responsable de todo el renderizado del juego
 * 
 * Maneja la carga de texturas, renderizado de sprites,
 * y presentación visual del juego.
 */
class GameRenderer {
private:
    sf::RenderWindow* window;
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Sprite> sprites;
    sf::Font font;
    int gridSize;
    
public:
    GameRenderer();
    ~GameRenderer();
    
    // Métodos de inicialización (verbos)
    bool Initialize(sf::RenderWindow* renderWindow);
    bool LoadAssets();
    void Cleanup();
    
    // Métodos de renderizado
    void Clear();
    void Present();
    void RenderBackground();
    void RenderSnake(const Snake& snake);
    void RenderFood(const Food& food);
    void RenderScore(int score);
    void RenderStartScreen();
    void RenderGameOverScreen();
    void RenderPauseScreen();
    void RenderGameBounds();  // Renderizar límites del área de juego
    
    // Métodos de texturas y sprites
    bool LoadTexture(const std::string& name, const std::string& path);
    sf::Texture* GetTexture(const std::string& name);
    sf::Sprite* GetSprite(const std::string& name);
    void CreateSprite(const std::string& name, const std::string& textureName);
    
    // Métodos de utilidad
    void RenderSprite(const std::string& spriteName, float x, float y);
    void RenderSpriteAt(const std::string& spriteName, const sf::Vector2f& position);
    void RenderRect(const sf::FloatRect& rect, const sf::Color& color);
    void RenderText(const std::string& text, float x, float y, const sf::Color& color = sf::Color::White);
    
    // Getters
    sf::RenderWindow* GetWindow() const { return window; }
    int GetGridSize() const { return gridSize; }
    const sf::Font& GetFont() const { return font; }
    
    // Métodos para obtener dimensiones del área de juego
    float GetGameAreaMargin() const { return 100.0f; }  // Reducido de 200 a 100 píxeles
    float GetGameAreaWidth() const { return 1200.0f - (2 * GetGameAreaMargin()); }  // 1000 píxeles
    float GetGameAreaHeight() const { return 900.0f - (2 * GetGameAreaMargin()); }  // 700 píxeles
    int GetGameGridWidth() const { return static_cast<int>(GetGameAreaWidth() / gridSize); }
    int GetGameGridHeight() const { return static_cast<int>(GetGameAreaHeight() / gridSize); }
    
    // Setters
    void SetGridSize(int size) { gridSize = size; }
    
private:
    // Métodos privados auxiliares
    bool LoadSnakeTextures();
    bool LoadUITextures();
    bool LoadNumberTextures();
    void RenderDigit(int digit, float x, float y);
    sf::Vector2f CalculateGridPosition(int gridX, int gridY) const;
    sf::FloatRect CalculateGridRect(int gridX, int gridY) const;
};

#endif // GAME_RENDERER_HPP