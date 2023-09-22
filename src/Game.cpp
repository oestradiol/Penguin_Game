#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "h_files/SDL_include.h"

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

#include "h_files/Game.h"
#include "h_files/Resources.h"

Game::Game(const string& title, int width, int height) {
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

    // Create State
    state = new State();
}

Game::~Game() {
    delete state;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
};

State& Game::GetState() {
    return *state;
};

Game* Game::instance = nullptr;
Game& Game::GetInstance() {
    if (instance != nullptr) {
        return *instance;
    }

    return *(new Game("Nome: Elaina Lynn A., Matrícula: 200016750", 1024, 600));
};

void Game::Run() {
    const int frameRate = 60;
    const float frameTime = 1000.0f / frameRate;

    float dt = 0.0f;
    Uint32 lastFrameTime = SDL_GetTicks();

    while (!state->QuitRequested()) {
        Uint32 startTime = SDL_GetTicks();
        Uint32 frameTimeElapsed = startTime - lastFrameTime;
        dt = static_cast<float>(frameTimeElapsed);
        if (dt > frameTime) {
            dt = frameTime;
        }

        // 1. Verificar, controlar e carregar as telas de jogo
        // 2. Receber e processar dados de entrada
        state->Update(dt); // 3.
        state->Render(); // 4.

        SDL_RenderPresent(renderer);

        Uint32 endTime = SDL_GetTicks();
        Uint32 frameTimeElapsedTotal = endTime - startTime;
        if (frameTimeElapsedTotal < frameTime) {
            SDL_Delay(static_cast<Uint32>(frameTime - frameTimeElapsedTotal));
        }

        lastFrameTime = startTime;
    }

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}