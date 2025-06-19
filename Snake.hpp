
#pragma once
#include <deque>
#include "Point.hpp"

class Snake {
public:
    Snake();
    void move();
    void grow();
    bool checkCollision() const;
    void changeDirection(char dir);
    const std::deque<Point>& getBody() const;

private:
    std::deque<Point> body;
    char direction;
};
