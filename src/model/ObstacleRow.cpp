#include "ObstacleRow.h"
#include <iostream>

ObstacleRow::ObstacleRow(float x, float y, float width, float height, int obstaclesPerRow, RowType type): GameObject{x, y, width, height} {
    float obstacleWidth = width / obstaclesPerRow;
    for (int i = 0; i < obstaclesPerRow; i++) {
        switch (type)
        {
            case FULL_OBSTACLES:
                SetupObstacle(i, obstacleWidth, _height);
                break;
            case FOOD_ONLY:
                SetupFood(i, obstacleWidth, _height);
            default:
                break;
        }
    }
}

void ObstacleRow::SetupObstacle(int index, float width, float height) {
    Obstacle obstacle{index * width, _y, width, height};
    _obstacles.emplace_back(obstacle);
}

void ObstacleRow::SetupFood(int index, float width, float height) {
    Food food{_x, _y};
    food.SetX(index * width + (width / 2 - food.GetWidth() / 2));
    food.SetY(_y + (height / 2 - food.GetHeight() / 2));
    _foods.emplace_back(food);
}

void ObstacleRow::Update() {
    _y += _speed;
    for (Obstacle &obstacle: _obstacles) {
        obstacle.SetY(_y);
    }
    for (Food &food: _foods) {
        food.SetY(food.GetY() + _speed);
    }
}

vector<Obstacle> ObstacleRow::GetObstacles() const {
    return _obstacles;
}

vector<Food> ObstacleRow::GetFoods() const {
    return _foods;
}