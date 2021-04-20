#ifndef OBSTACLE_ROW_H
#define OBSTACLE_ROW_H

#include <vector>
#include "GameObject.h"
#include "Obstacle.h"
#include "Food.h"

using namespace std;

enum RowType { FULL_OBSTACLES, FOOD_ONLY, EMPTY };

class ObstacleRow: public GameObject {
    public:
        ObstacleRow(float x, float y, float width, float height, int obstaclesPerRow, RowType type);
        void Update();
        vector<Obstacle> &GetObstacles();
        vector<Food> &GetFoods();
    
    private:
        vector<Obstacle> _obstacles;
        vector<Food> _foods;
        float _speed{0.1f};
        void SetupObstacle(int index, float width, float height);
        void SetupFood(int index, float width, float height);
};

#endif