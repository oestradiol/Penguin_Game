#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "../SDL_include.h"

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

#include "headers/Game.h"
#include "headers/Resources.h"
#include "headers/InputManager.h"

Game::Game(const string& title, int width, int height)
    : frameStart(0), dt(0), storedState(nullptr) {
    if (instance != nullptr) {
        throw new runtime_error("A game instance already exists!");
    } else {
        instance = this;
    }

    srand(time(NULL));

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        cerr << "Game: Failed to initialize SDL!\nError: " << SDL_GetError() << endl;
        exit(1);
    }

    // Initialize IMG
    int flags = IMG_INIT_JPG | IMG_INIT_PNG; // | IMG_INIT_TIF;
    int result = IMG_Init(flags);
    if (result ^ flags) {
        stringstream err;
        err << "Warning - failed to load image loader(s):";
        if (!(result & IMG_INIT_JPG)) err << " JPG";
        if (!(result & IMG_INIT_PNG)) err << " PNG";
        err << ".\nError: " << IMG_GetError() << endl;
        cerr << err.str() << endl;
    }

    // Initialize TTF
    result = TTF_Init();
    if (result) {
        stringstream err;
        err << "Warning - failed to load font loader.";
        err << ".\nError: " << IMG_GetError() << endl;
        cerr << err.str() << endl;
    }

    // Initialize Mixer
    flags = MIX_INIT_OGG; // | MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_FLUIDSYNTH | MIX_INIT_MODPLUG;
    result = Mix_Init(flags);
    if (result ^ flags) {
        stringstream err;
        err << "Game: Warning - failed to load Mixer loader(s):";
        if (!(result & MIX_INIT_OGG)) err << " OGG";
        err << ".\nError: " << Mix_GetError() << endl;
        cerr << err.str() << endl;
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {
        cerr << "Game: Failed to open audio device.\nError " << Mix_GetError() << endl;
    }

    Mix_AllocateChannels(32);

    // Create Window
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!window) {
        cerr << "Game: Failed to create window.\nError: " << SDL_GetError() << endl;
        exit(1);
    }

    // Create Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cerr << "Game: Failed to create renderer.\nError: " << SDL_GetError() << endl;
        exit(1);
    }
}

Game::~Game() {
    if (storedState) delete storedState;
    size_t len = stateStack.size();
    for (size_t i = 0; i < len; i++) stateStack.pop();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

Game* Game::instance = nullptr;
Game& Game::GetInstance() {
    if (instance != nullptr) {
        return *instance;
    }

    return *(new Game("Nome: Elaina Lynn A., Matrícula: 200016750", WIN_WIDTH, WIN_HEIGHT));
};

void Game::CalculateDeltaTime() {
    Uint32 currentFrameTime = SDL_GetTicks();
    dt = static_cast<float>(currentFrameTime - frameStart) / 1000.0f;
    frameStart = currentFrameTime;
}

void Game::Push(State* state) {
    storedState = state;
}

void Game::Run() {
    if (storedState == nullptr) {
        cerr << "Game: Failed to initialize. No initial state found." << endl;
        exit(1);
    }
    stateStack.emplace(storedState);
    storedState = nullptr;
    unique_ptr<State>* currState = &stateStack.top();
    (*currState)->Start();

    while (!stateStack.empty() && !(*currState)->QuitRequested()) {
        if ((*currState)->PopRequested()) {
            stateStack.pop();
            Resources::ClearImages();
            Resources::ClearMusics();
            Resources::ClearSounds();
            Resources::ClearFonts();
            currState = nullptr;

            if (storedState == nullptr) {
                if (!stateStack.empty()) {
                    currState = &stateStack.top();
                    (*currState)->Resume();
                } else {
                    break;
                }
            }
        }
        
        if (storedState != nullptr) {
            stateStack.emplace(storedState);
            storedState = nullptr;
            if (currState != nullptr) (*currState)->Pause();
            currState = &stateStack.top();
            (*currState)->Start();
        }

        CalculateDeltaTime();

        InputManager& inputManager = InputManager::GetInstance();
        inputManager.Update();
        (*currState)->Update(dt);
        (*currState)->Render();

        SDL_RenderPresent(renderer);
    }

    if (!stateStack.empty()) {
        size_t len = stateStack.size();
        for (size_t i = 0; i < len; i++)
            stateStack.pop();
    }
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
    Resources::ClearFonts();
}