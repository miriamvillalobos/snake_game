
#include "../include/Snake.hpp"

Snake::Snake() : direction('D') {
    body.push_front({10, 10});
}

void Snake::move() {
    Point head = body.front();
    switch (direction) {
        case 'W': head.y--; break;
        case 'S': head.y++; break;
        case 'A': head.x--; break;
        case 'D': head.x++; break;
    }
    body.push_front(head);
    body.pop_back();
}

void Snake::grow() {
    body.push_back(body.back());
}

bool Snake::checkCollision() const {
    Point head = body.front();
    if (head.x < 0 || head.x >= 40 || head.y < 0 || head.y >= 20)
        return true;
    for (size_t i = 1; i < body.size(); ++i) {
        if (body[i] == head) return true;
    }
    return false;
}

void Snake::changeDirection(char dir) {
    direction = dir;
}

const std::deque<Point>& Snake::getBody() const {
    return body;
}
