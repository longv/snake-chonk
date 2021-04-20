#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(World const &world) {
  int widthPerBlock = screen_width / grid_width;
  int heightPerBlock = screen_height / grid_height;
  
  SDL_Rect block;
  block.w = widthPerBlock;
  block.h = heightPerBlock;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render obstacles
  for (ObstacleRow &row: world.GetObstacleRows()) {
    int count = 0;
    for (Obstacle &obstacle: row.GetObstacles()) {
      block.w = obstacle.GetWidth() * widthPerBlock;
      block.h = obstacle.GetHeight() * heightPerBlock;
      block.x = obstacle.GetX() * widthPerBlock;
      block.y = obstacle.GetY() * heightPerBlock;
      
      Color color = _colors[count];
      SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, 255);
      count++;

      SDL_RenderFillRect(sdl_renderer, &block);
    }

    // Render food
    for (Food &food: row.GetFoods()) {
      block.w = food.GetWidth() * widthPerBlock;
      block.h = food.GetHeight() * heightPerBlock;
      block.x = food.GetX() * widthPerBlock;
      block.y = food.GetY() * heightPerBlock;

      Color color = _colors[5];
      SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, 255);

      SDL_RenderFillRect(sdl_renderer, &block);
    }
  }

  block.w = widthPerBlock;
  block.h = heightPerBlock;

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : world.GetSnake().body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(world.GetSnake().head_x) * block.w;
  block.y = static_cast<int>(world.GetSnake().head_y) * block.h;
  if (world.GetSnake().alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::RenderObstacles(Obstacle obstacle) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = 1 * block.w;
  block.y = 2 * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);
}

void Renderer::UpdateWindowTitle(int score, int fps, bool gameEnd) {
  if (gameEnd) {
    std::string title{"You died! Final Score: " + std::to_string(score)};
    SDL_SetWindowTitle(sdl_window, title.c_str());
  } else {
    std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(sdl_window, title.c_str());
  }
}
