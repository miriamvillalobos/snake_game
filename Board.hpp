
#pragma once
#include "Snake.hpp"
#include "Food.hpp"

class Board {
public:
    void draw(const Snake& snake, const Food& food) const;
};
