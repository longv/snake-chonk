#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GameObject.h"

class Obstacle: public GameObject {
    public:
        Obstacle(float x, float y, float width, float height): GameObject{x, y, width, height} {}
};

#endif