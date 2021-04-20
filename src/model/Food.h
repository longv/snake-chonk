#ifndef FOOD_H
#define FOOD_H

#include "GameObject.h"

class Food: public GameObject {
    public:
        Food(float x, float y): GameObject{x, y, 1, 1} {}
        bool eaten{false};
};

#endif