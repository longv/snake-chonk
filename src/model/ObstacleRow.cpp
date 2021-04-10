#include "ObstacleRow.h"
#include <iostream>

ObstacleRow::ObstacleRow(int grid_width): grid_width(grid_width) {
    x = 0;
    y = 0;
    Obstacle obstacle;
    obstacle.x = x;
    obstacle.y = y;
    obstacles.emplace_back(obstacle);
}

void ObstacleRow::Update() {
    y += speed;
    for (Obstacle &obstacle: obstacles) {
        obstacle.y = y;
    }
}