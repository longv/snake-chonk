#include "World.h"
#include <iostream>
#include "SDL.h"

World::World(int grid_width, int grid_height)
: grid_width(grid_width), 
  grid_height(grid_height),
  _engine(_dev()),
  _random_w(0, 9),
  _random_h(0, static_cast<int>(grid_height - 1)) {}

void World::Update() {
    SpawnRow();
    for (ObstacleRow &row: _obstacleRows) {
        row.Update();
    }
}

void World::SpawnRow() {
    if (_obstacleRows.empty()) {
        ObstacleRow row{0, 0, grid_width, 3, 5, GenerateRowType()};
        _obstacleRows.emplace_back(row);
    } 

    ObstacleRow firstRow = _obstacleRows.front();
    if (firstRow.GetY() >= 0) {
        ObstacleRow row{0, -3, grid_width, 3, 5, GenerateRowType()};
        _obstacleRows.emplace(_obstacleRows.begin(), row);
    }

    // Remove the last row when it goes out of screen
    ObstacleRow lastRow = _obstacleRows.back();
    if (lastRow.GetY() > grid_height) {
        _obstacleRows.pop_back();
    }
}

RowType World::GenerateRowType() {
    int rand = _random_w(_engine);
    if (rand <= 1) {
        return RowType::FULL_OBSTACLES;
    } else if (rand <= 4) {
        return RowType::FOOD_ONLY;
    } else {
        return RowType::EMPTY;
    }
}

vector<ObstacleRow> World::GetObstacleRows() const {
    return _obstacleRows;
}

bool World::IsCollided(GameObject obj1, GameObject obj2) {
    return IsCollidedX(obj1, obj2) || IsCollidedY(obj1, obj2);
}

bool World::IsCollidedX(GameObject obj1, GameObject obj2) {
    return (obj1.GetX() <= obj2.GetX() + obj2.GetWidth()) && (obj1.GetX() + obj1.GetWidth() >= obj2.GetX());
}

bool World::IsCollidedY(GameObject obj1, GameObject obj2) {
    return (obj1.GetY() <= obj2.GetY() + obj2.GetHeight()) && (obj1.GetY() + obj1.GetHeight() >= obj2.GetY());
}