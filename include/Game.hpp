#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <memory>

// Forward declarations
class Snake;
class Food;
class GameRenderer;
class AudioManager;
class InputHandler;

// Incluir Direction desde Snake.hpp
enum class Direction;

/**
 * @brief Clase principal del juego Snake
 * 
 * Maneja el loop principal del juego, coordina todos los componentes
 * y controla el estado general del juego.
 */
class Game {
private:
    static const int WINDOW_WIDTH = 1200;
    static const int WINDOW_HEIGHT = 900;
    static const int GRID_SIZE = 20;  // Aumentado de 15 a 20 píxeles para sprites más grandes
    static const int GAME_AREA_MARGIN = 100;  // Reducido de 200 a 100 píxeles
    static const int GAME_AREA_WIDTH = WINDOW_WIDTH - (2 * GAME_AREA_MARGIN);  // 1000 píxeles
    static const int GAME_AREA_HEIGHT = WINDOW_HEIGHT - (2 * GAME_AREA_MARGIN); // 700 píxeles
    static const int GRID_WIDTH = GAME_AREA_WIDTH / GRID_SIZE;   // 50 celdas
    static const int GRID_HEIGHT = GAME_AREA_HEIGHT / GRID_SIZE; // 35 celdas
    
    sf::RenderWindow window;
    sf::Clock gameClock;
    bool isRunning;
    bool gameOver;
    bool gameStarted;
    int score;
    
    // Componentes del juego (Composición)
    std::unique_ptr<Snake> snake;           // 1..1
    std::unique_ptr<Food> food;             // 1..1
    std::unique_ptr<GameRenderer> renderer; // 1..1
    std::unique_ptr<AudioManager> audioManager; // 1..1
    std::unique_ptr<InputHandler> inputHandler; // 1..1
    
public:
    Game();
    ~Game();
    
    // Métodos principales (verbos)
    bool Initialize();
    void Run();
    void Update();
    void HandleEvents();
    void Render();
    void Cleanup();
    
    // Métodos de control del juego
    void StartGame();
    void RestartGame();
    void EndGame();
    void PauseGame();
    void ResumeGame();
    
    // Métodos de puntuación
    void AddScore(int points);
    void ResetScore();
    
    // Getters
    bool IsRunning() const { return isRunning; }
    bool IsGameOver() const { return gameOver; }
    bool IsGameStarted() const { return gameStarted; }
    int GetScore() const { return score; }
    int GetGridSize() const { return GRID_SIZE; }
    int GetGridWidth() const { return GRID_WIDTH; }
    int GetGridHeight() const { return GRID_HEIGHT; }
    
    // Setters
    void SetGameOver(bool value) { gameOver = value; }
    void SetGameStarted(bool value) { gameStarted = value; }
    void SetRunning(bool value) { isRunning = value; }
    
    // Métodos de control de la serpiente
    void ChangeSnakeDirection(Direction direction);
    
    // Acceso a componentes
    GameRenderer* GetRenderer() const { return renderer.get(); }
    AudioManager* GetAudioManager() const { return audioManager.get(); }
    sf::RenderWindow& GetWindow() { return window; }
    const sf::RenderWindow& GetWindow() const { return window; }
    sf::RenderWindow* GetWindowPtr() { return &window; }
};

#endif // GAME_HPP