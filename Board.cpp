
#include "../include/Board.hpp"
#include <iostream>
#include <vector>

void Board::draw(const Snake& snake, const Food& food) const {
    std::vector<std::vector<char>> grid(20, std::vector<char>(40, ' '));

    for (const auto& part : snake.getBody()) {
        grid[part.y][part.x] = 'O';
    }
    Point f = food.getPosition();
    grid[f.y][f.x] = '*';

    for (int y = 0; y < 20; ++y) {
        for (int x = 0; x < 40; ++x) {
            std::cout << grid[y][x];
        }
        std::cout << '\n';
    }
}
