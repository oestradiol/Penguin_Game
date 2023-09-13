#ifndef GAME_H_
#define GAME_H_

#define INCLUDE_SDL
#include "SDL_include.h"

#include <string>

#include "State.h"

class Game {
public:
    ~Game();

    void Run();

    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();

private:
    Game(const std::string& title, int width, int height);

    static Game* instance;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;
};

#endif