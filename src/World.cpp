#include "World.h"
#include <iostream>
#include "SDL.h"

World::World(int grid_width, int grid_height)
: grid_width(grid_width), 
  grid_height(grid_height),
  _snake(grid_width, grid_height),
  _engine(_dev()),
  _random_w(0, 9),
  _random_h(0, static_cast<int>(grid_height - 1)) {}

void World::HandleInput(Controller const &controller, bool &running) {
    controller.HandleInput(_snake, running);
}

void World::Update() {
    SpawnRow();
    for (ObstacleRow &row: _obstacleRows) {
        row.Update();
    }

    UpdateSnake();
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

void World::UpdateSnake() {
    if (!_snake.alive) return;

    // Check if there's food over here
    for (ObstacleRow &row: _obstacleRows) {
        vector<Food>::iterator eatenFoodIter = row.GetFoods().end();

        for (Food &food: row.GetFoods()) {
            //score++;
            // Grow snake and increase speed.
            if (IsCollidedWithFood(food)) {
                food.eaten = true;
                _snake.GrowBody();
            }
        }

        for (Obstacle &obstacle: row.GetObstacles()) {
            // Grow snake and increase speed.
            if (IsCollidedWithFood(obstacle)) {
                obstacle.eaten = true;
                _snake.ShrinkBody();
            }
        }
    }

    _snake.Update();
}

vector<ObstacleRow> World::GetObstacleRows() const {
    return _obstacleRows;
}

Snake World::GetSnake() const {
    return _snake;
}

bool World::IsCollidedWithFood(GameObject const &object) {
    return (_snake.head_x >= object.GetX() && _snake.head_x <= object.GetX() + object.GetWidth()) 
        && (_snake.head_y >= object.GetY() && _snake.head_y <= object.GetY() + object.GetHeight());
}