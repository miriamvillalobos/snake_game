#include "Game.hpp"
#include "Snake.hpp"
#include "Food.hpp"
#include "GameRenderer.hpp"
#include "AudioManager.hpp"
#include "InputHandler.hpp"
#include <iostream>

Game::Game() 
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game - C++ SFML Project"),
      isRunning(false), gameOver(false), gameStarted(false), score(0) {
    // Inicializar componentes usando smart pointers
    snake = std::make_unique<Snake>(GRID_WIDTH / 2, GRID_HEIGHT / 2);
    food = std::make_unique<Food>();
    renderer = std::make_unique<GameRenderer>();
    audioManager = std::make_unique<AudioManager>();
    inputHandler = std::make_unique<InputHandler>();
    
    // Configurar ventana
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
}

Game::~Game() {
    Cleanup();
}

bool Game::Initialize() {
    // Inicializar componentes
    if (!renderer->Initialize(&window)) {
        std::cerr << "Failed to initialize renderer!" << std::endl;
        return false;
    }
    
    if (!audioManager->Initialize()) {
        std::cerr << "Failed to initialize audio manager!" << std::endl;
        return false;
    }
    
    inputHandler->Initialize(this);
    
    // Cargar assets
    if (!renderer->LoadAssets()) {
        std::cerr << "Failed to load renderer assets!" << std::endl;
        return false;
    }
    
    if (!audioManager->LoadAudioAssets()) {
        std::cerr << "Failed to load audio assets!" << std::endl;
        return false;
    }
    
    // Generar posición inicial de la comida
    food->GenerateNewPosition(GRID_WIDTH, GRID_HEIGHT, *snake);
    
    isRunning = true;
    return true;
}

void Game::Run() {
    audioManager->PlayMusic("background");
    
    sf::Clock clock;
    const sf::Time timePerFrame = sf::seconds(1.0f / 10.0f); // 10 FPS para Snake
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    
    while (window.isOpen() && isRunning) {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        
        // Procesar eventos
        HandleEvents();
        
        // Actualizar juego a velocidad fija
        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            
            if (gameStarted && !gameOver) {
                Update();
            }
        }
        
        // Renderizar
        Render();
    }
}

void Game::HandleEvents() {
    inputHandler->HandleEvents(window);
}

void Game::Update() {
    if (gameOver) return;
    
    snake->Update();
    food->Update();
    
    // Verificar colisiones
    if (snake->CheckWallCollision(GRID_WIDTH, GRID_HEIGHT) || 
        snake->CheckSelfCollision()) {
        EndGame();
        return;
    }
    
    // Verificar si la serpiente comió la comida
    if (food->IsEatenBy(*snake)) {
        snake->Grow();
        AddScore(food->GetNutritionalValue());
        audioManager->PlaySoundEffect("eat");
        food->GenerateNewPosition(GRID_WIDTH, GRID_HEIGHT, *snake);
    }
}

void Game::Render() {
    renderer->Clear();
    
    if (!gameStarted) {
        renderer->RenderStartScreen();
    } else if (gameOver) {
        renderer->RenderGameOverScreen();
        renderer->RenderScore(score);
    } else {
        renderer->RenderBackground();
        renderer->RenderGameBounds();  // Renderizar límites del área de juego
        renderer->RenderFood(*food);
        renderer->RenderSnake(*snake);
        renderer->RenderScore(score);
    }
    
    renderer->Present();
}

void Game::StartGame() {
    if (!gameStarted) {
        gameStarted = true;
        audioManager->PlaySoundEffect("start");
        audioManager->PlayMusic("background");
    }
}

void Game::RestartGame() {
    gameOver = false;
    gameStarted = false;
    ResetScore();
    snake->Reset(GRID_WIDTH / 2, GRID_HEIGHT / 2);
    food->GenerateNewPosition(GRID_WIDTH, GRID_HEIGHT, *snake);
    audioManager->StopMusic();
}

void Game::EndGame() {
    gameOver = true;
    audioManager->StopMusic();
    audioManager->PlaySoundEffect("crash");
    audioManager->PlaySoundEffect("gameover");
}

void Game::PauseGame() {
    audioManager->PauseMusic();
}

void Game::ResumeGame() {
    audioManager->ResumeMusic();
}

void Game::AddScore(int points) {
    score += points;
}

void Game::ResetScore() {
    score = 0;
}

void Game::ChangeSnakeDirection(Direction direction) {
    if (snake && gameStarted && !gameOver) {
        snake->ChangeDirection(direction);
    }
}

void Game::Cleanup() {
    if (renderer) {
        renderer->Cleanup();
    }
    
    if (audioManager) {
        audioManager->Cleanup();
    }
    
    if (inputHandler) {
        inputHandler->Cleanup();
    }
    
    if (window.isOpen()) {
        window.close();
    }
}