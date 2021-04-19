#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::HandleInput(bool &running, Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
         case SDLK_LEFT:
          snake.direction = Snake::Direction::kLeft;
          break;

        case SDLK_RIGHT:
          snake.direction = Snake::Direction::kRight;
          break;

        default:
          break;
      }
    } else if (e.type == SDL_KEYUP) {
      snake.direction = Snake::Direction::kNone;
    }
  }
}