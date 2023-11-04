#pragma once

#define INCLUDE_SDL
#include "../../SDL_include.h"

#include <string>
#include <stack>

#include "State.h"

class Game {
public:
    static constexpr int WIN_WIDTH = 1024;
    static constexpr int WIN_HEIGHT = 600;

    static Game& GetInstance();

    ~Game();

    SDL_Renderer* GetRenderer() const;
    State& GetCurrentState() const;

    void Push(State* state);
    void Run();
    
    float GetDeltaTime() const;

private:
    Game(const std::string& title, int width, int height);
    void CalculateDeltaTime();

    static Game* instance;

    Uint32 frameStart;
    float dt;

    SDL_Window* window;
    SDL_Renderer* renderer;
    State* storedState;

    std::stack<std::unique_ptr<State>> stateStack;
};

inline SDL_Renderer* Game::GetRenderer() const {
    return renderer;
}

inline State& Game::GetCurrentState() const {
    return *stateStack.top();
}

inline float Game::GetDeltaTime() const {
    return dt;
}