#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <random>
#include <algorithm>
#include "controller.h"
#include "model/ObstacleRow.h"
#include "model/Food.h"
#include "model/Snake.h"

using namespace std;

class World {
    public:
        World(int grid_width, int grid_height);
        void HandleInput(Controller const &controller, bool &running);
        void Update(int &score);
        Snake GetSnake() const;
        vector<ObstacleRow> GetObstacleRows() const;
        vector<Food> GetFoods() const;

    private:
        int _grid_width, _grid_height;

        random_device _dev;
        mt19937 _engine;
        uniform_int_distribution<int> _random_w;
        uniform_int_distribution<int> _random_h;

        Snake _snake;
        void UpdateSnake(int &score);

        vector<ObstacleRow> _obstacleRows;
        void SpawnRow();
        RowType GenerateRowType();

        bool IsCollidedWithFood(GameObject const &object);
};

#endif