#include "Snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  // We first capture the head's cell before updating.
  SDL_Point prev_cell{static_cast<int>(head_x), static_cast<int>(head_y)};  

  UpdateHead();

  // Capture the head's cell after updating.
  SDL_Point current_cell{static_cast<int>(head_x), static_cast<int>(head_y)};  

  UpdateBody(current_cell, prev_cell);
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kLeft:
      if (head_x > speed) {
        head_x -= speed;
      } else {
        head_x = 0;
      }
      break;

    case Direction::kRight:
      if (head_x + speed < grid_width) {
        head_x += speed;
      } else {
        head_x = grid_width - 1;
      }
      break;
    
    default:
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  if (growing) {
    float newCellX = head_x;
    float newCellY = head_y + 1;
    if (!body.empty()) {
      SDL_Point lastCell = body.back();
      newCellX = lastCell.x;
      newCellY = lastCell.y + 1;
    }
    SDL_Point newCell{static_cast<int>(newCellX), static_cast<int>(newCellY)};  
    body.emplace_back(newCell);
    growing = false;
    size++;
  }

  if (shrinking) {
    if (body.size() < 1) {
      alive = false;
    } else {
      body.pop_back();
      shrinking = false;
      size--;
    }
  }

  for (SDL_Point &point: body) {
    point.x = head_x;
  }
}

void Snake::GrowBody() { growing = true; }

void Snake::ShrinkBody() { shrinking = true; }