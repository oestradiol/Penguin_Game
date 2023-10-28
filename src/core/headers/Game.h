#pragma once

#define INCLUDE_SDL
#include "../../SDL_include.h"

#include <string>

#include "State.h"

class Game {
public:
    static constexpr int WIN_WIDTH = 1024;
    static constexpr int WIN_HEIGHT = 600;

    ~Game();

    void Run();

    SDL_Renderer* GetRenderer() const;
    State& GetState() const;
    float GetDeltaTime() const;

    static Game& GetInstance();

private:
    Game(const std::string& title, int width, int height);
    void CalculateDeltaTime();

    static Game* instance;

    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;
    Uint32 frameStart;
    float dt;
};

inline SDL_Renderer* Game::GetRenderer() const {
    return renderer;
}

inline State& Game::GetState() const {
    return *state;
}

inline float Game::GetDeltaTime() const {
    return dt;
}
