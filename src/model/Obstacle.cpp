#include "Obstacle.h"

Obstacle::Obstacle(float width, float height): _width(width), _height(height) {}

float Obstacle::getWidth() const {
    return _width;
}

float Obstacle::getHeight() const {
    return _height;
}