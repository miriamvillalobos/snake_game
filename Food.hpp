
#pragma once
#include "Point.hpp"

class Food {
public:
    Food();
    void respawn();
    Point getPosition() const;

private:
    Point position;
};
