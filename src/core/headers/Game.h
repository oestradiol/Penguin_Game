#pragma once

#define INCLUDE_SDL
#include "../../SDL_include.h"

#include <string>

#include "State.h"

class Game {
public:
    ~Game();

    void Run();

    SDL_Renderer* GetRenderer() const;
    State& GetState() const;
    static Game& GetInstance();

private:
    Game(const std::string& title, int width, int height);

    static Game* instance;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;
};

inline SDL_Renderer* Game::GetRenderer() const {
    return renderer;
};

inline State& Game::GetState() const {
    return *state;
};