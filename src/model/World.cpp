#include "World.h"
#include <iostream>
#include "SDL.h"

World::World(int grid_width, int grid_height): grid_width(grid_width), grid_height(grid_height) {}

void World::Update() {
    SpawnRow();
    for (ObstacleRow &row: obstacleRows) {
        row.Update();
    }
}

void World::SpawnRow() {
    if (obstacleRows.empty()) {
        ObstacleRow row{grid_width, 3};
        obstacleRows.emplace_back(row);
    } else {
        // Add a new row when the lastest first row passes a portion of the screen
        ObstacleRow firstRow = obstacleRows.front();
        if (firstRow.y > (grid_height / 3)) {
            ObstacleRow row{grid_width, 3};
            obstacleRows.emplace(obstacleRows.begin(), row);
        }

        // Remove the last row when it goes out of screen
        ObstacleRow lastRow = obstacleRows.back();
        if (lastRow.y > grid_height) {
            obstacleRows.pop_back();
        }
    }
}