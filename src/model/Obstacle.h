#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GameObject.h"

class Obstacle: public GameObject {
    public:
        Obstacle(float width, float height);
        float getWidth() const;
        float getHeight() const;

    private:
        float _width, _height;
};

#endif