//
// Created by garrido-lestachebeli on 4/8/2026.
//

#include "GridObject.h"

GridObject::GridObject() : x(0), y(0) {}

GridObject::GridObject(int x, int y) : x(x), y(y) {}

int GridObject::getX() const {
    return x;
}

int GridObject::getY() const {
    return y;
}

void GridObject::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}