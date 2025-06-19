
#include "../include/Food.hpp"
#include <cstdlib>
#include <ctime>

Food::Food() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    respawn();
}

void Food::respawn() {
    position.x = std::rand() % 40;
    position.y = std::rand() % 20;
}

Point Food::getPosition() const {
    return position;
}
