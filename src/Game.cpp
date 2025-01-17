#include "Game.h"
#include <iostream>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : _world(grid_width, grid_height)
{
}

void Game::Run(Controller const& controller, Renderer& renderer,
               std::size_t target_frame_duration)
{
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;

    while (running)
    {
        frame_start = SDL_GetTicks();

        // Handle input and update logic
        _world.HandleInput(controller, running);
        _world.Update(_score);

        // Render the world
        renderer.Render(_world);

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render
        // cycle takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000)
        {
            renderer.UpdateWindowTitle(_score, frame_count,
                                       !_world.GetSnake().alive);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration)
        {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }
}

int Game::GetScore() const { return _score; }
