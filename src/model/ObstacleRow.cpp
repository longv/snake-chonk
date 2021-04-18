#include "ObstacleRow.h"
#include <iostream>

ObstacleRow::ObstacleRow(float width, int obstaclesPerRow) {
    x = 0;
    y = 0;
    float prevX = x;
    float spaceBetweenObstacles = 1;
    float obstacleWidth = (width - spaceBetweenObstacles * (obstaclesPerRow - 1)) / obstaclesPerRow;
    float obstacleHeight = 3;

    for (int i = 0; i < obstaclesPerRow; i++) {
        Obstacle obstacle{obstacleWidth, obstacleHeight};
        obstacle.x = prevX;
        obstacle.y = y;

        _obstacles.emplace_back(obstacle);

        prevX += obstacleWidth + spaceBetweenObstacles;
    }
}

void ObstacleRow::Update() {
    y += _speed;
    for (Obstacle &obstacle: _obstacles) {
        obstacle.y = y;
    }
}

vector<Obstacle> ObstacleRow::getObstacles() const {
    return _obstacles;
}