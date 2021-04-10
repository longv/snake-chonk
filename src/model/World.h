#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "ObstacleRow.h"

using namespace std;

class World {
    public:
        World(int grid_width, int grid_height);
        vector<ObstacleRow> obstacleRows;

        void Update();

    private:
        int grid_width, grid_height;

        void SpawnRow();
};

#endif