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

    // SpawnFoods();
    // for (Food &food: _foods) {
    //     food.y += 0.1f;
    // }
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

void World::SpawnFoods() {
    _foods.erase(
        remove_if(_foods.begin(), _foods.end(), [this](const Food &food) {  return food.GetY() > grid_height;  }),
        _foods.end()
    );

    if (_foods.size() < 10) {
        Food newFood{_random_w(_engine), _random_h(_engine)};
        
        // Check that the location is not occupied by a snake item before placing
        // food.
        bool canBeSpawned = true;
        for (ObstacleRow const &row: _obstacleRows) {
            cout << "====================================================" << endl;
            cout << "CanBeSpawned " << canBeSpawned << endl;
            cout << "IsCollided " << IsCollidedY(newFood, row) << endl;
            canBeSpawned = canBeSpawned && !IsCollidedY(newFood, row);
            cout << "CanBeSpawned " << canBeSpawned << endl;
            cout << "====================================================" << endl;
        }

        for (Food const &food: _foods) {
            canBeSpawned = canBeSpawned && !IsCollided(newFood, food);
        }

        if (canBeSpawned) {
            _foods.emplace_back(newFood);
        }

        return;
    }
}

vector<ObstacleRow> World::GetObstacleRows() const {
    return _obstacleRows;
}

vector<Food> World::GetFoods() const {
    return _foods;
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