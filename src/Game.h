#ifndef GAME_H
#define GAME_H

#include "Controller.h"
#include "Renderer.h"
#include "SDL.h"
#include "World.h"
#include <random>

class Game
{
public:
    Game(std::size_t grid_width, std::size_t grid_height);
    void Run(Controller const& controller, Renderer& renderer,
             std::size_t target_frame_duration);
    int GetScore() const;

private:
    World _world;
    int _score{0};
};

#endif