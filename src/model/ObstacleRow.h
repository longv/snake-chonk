#ifndef OBSTACLE_ROW_H
#define OBSTACLE_ROW_H

#include <vector>
#include "GameObject.h"
#include "Obstacle.h"

using namespace std;

class ObstacleRow: public GameObject {
    public:
        ObstacleRow(int grid_width);
        vector<Obstacle> obstacles;
        void Update();
    
    private:
        int grid_width;
        float speed{0.1f};
};

#endif