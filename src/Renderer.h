#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "World.h"
#include "model/Color.h"
#include "model/Obstacle.h"
#include "model/Snake.h"
#include <vector>

using namespace std;

class Renderer
{
public:
    Renderer(const std::size_t screen_width, const std::size_t screen_height,
             const std::size_t grid_width, const std::size_t grid_height);
    ~Renderer();

    void Render(World const& world);
    void RenderObstacles(Obstacle obstacle);
    void UpdateWindowTitle(int score, int fps, bool gameEnd);

private:
    SDL_Window* sdl_window;
    SDL_Renderer* sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;

    const vector<Color> _colors{
        Color{255, 102, 102}, // red
        Color{255, 178, 102}, // orange
        Color{102, 255, 178}, // teal
        Color{102, 178, 255}, // blue
        Color{178, 102, 255}, // purple
        Color{255, 255, 102}  // yellow
    };
};

#endif