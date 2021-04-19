#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <random>
#include <algorithm>
#include "ObstacleRow.h"
#include "Food.h"

using namespace std;

class World {
    public:
        World(int grid_width, int grid_height);
        void Update();
        vector<ObstacleRow> GetObstacleRows() const;
        vector<Food> GetFoods() const;

    private:
        int grid_width, grid_height;
        random_device _dev;
        mt19937 _engine;
        uniform_int_distribution<int> _random_w;
        uniform_int_distribution<int> _random_h;

        vector<ObstacleRow> _obstacleRows;
        vector<Food> _foods;
        void SpawnRow();
        RowType GenerateRowType();
        void SpawnFoods();
        bool IsCollided(GameObject obj1, GameObject obj2);
        bool IsCollidedX(GameObject obj1, GameObject obj2);
        bool IsCollidedY(GameObject obj1, GameObject obj2);
};

#endif