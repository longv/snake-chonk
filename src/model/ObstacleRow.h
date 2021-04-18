#ifndef OBSTACLE_ROW_H
#define OBSTACLE_ROW_H

#include <vector>
#include "GameObject.h"
#include "Obstacle.h"

using namespace std;

class ObstacleRow: public GameObject {
    public:
        ObstacleRow(float width, int obstaclesPerRow);
        void Update();
        vector<Obstacle> getObstacles() const;
    
    private:
        vector<Obstacle> _obstacles;
        float _speed{0.1f};
};

#endif