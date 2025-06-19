
#include "../include/Game.hpp"
#include <iostream>
#include <conio.h> // Para _kbhit() y _getch()
#include <windows.h>

void Game::run() {
    Snake snake;
    Food food;
    Board board;

    while (!snake.checkCollision()) {
        if (_kbhit()) {
            char input = _getch();
            snake.changeDirection(input);
        }
        snake.move();
        if (snake.getBody().front() == food.getPosition()) {
            snake.grow();
            food.respawn();
        }
        system("cls");
        board.draw(snake, food);
        Sleep(100);
    }

    std::cout << "Game Over!\n";
}
