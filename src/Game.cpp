#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "h_files/SDL_include.h"

#include <iostream>
#include <stdexcept>
#include <sstream>
using namespace std;

#include "h_files/Game.h"

Game::Game(const string& title, int width, int height) {
    if (instance != nullptr) {
        throw new runtime_error("A game instance already exists!");
    } else {
        instance = this;
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        cerr << "Failed to initialize SDL: " << SDL_GetError() << endl;
        exit(1);
    }

    // Initialize IMG
    int flags = IMG_INIT_JPG; // | IMG_INIT_PNG | IMG_INIT_TIF;
    int result = IMG_Init(flags);
    if (result ^ flags) {
        stringstream err;
        err << "Warning - failed to load image loader(s):";
        if (!(result & IMG_INIT_JPG)) err << " JPG";
        err << ".\nError: " << IMG_GetError() << endl;
        cerr << err.str();
    }

    // Initialize Mixer
    flags = MIX_INIT_OGG; // | MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_FLUIDSYNTH | MIX_INIT_MODPLUG;
    result = Mix_Init(flags);
    if (result ^ flags) {
        stringstream err;
        err << "Warning - failed to load Mixer loader(s):";
        if (!(result & MIX_INIT_OGG)) err << " OGG";
        err << ".\nError: " << Mix_GetError() << endl;
        cerr << err.str();
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {
        cerr << "Failed to open audio device.\nError " << Mix_GetError() << endl;
    }

    Mix_AllocateChannels(32);

    // Create Window
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!window) {
        cerr << "Failed to create window.\nError: " << SDL_GetError() << endl;
        exit(1);
    }

    // Create Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Failed to create renderer. Error: " << SDL_GetError() << std::endl;
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
    // const int frameRate = 30;
    // const float frameTime = 1000.0f / frameRate;

    float dt = 0.0f;
    // Uint32 lastFrameTime = SDL_GetTicks();

    while (!state->QuitRequested()) {
        // Uint32 startTime = SDL_GetTicks();
        // Uint32 frameTimeElapsed = startTime - lastFrameTime;
        // dt = static_cast<float>(frameTimeElapsed);
        // if (dt > frameTime) {
        //     dt = frameTime;
        // }

        // 1. Verificar, controlar e carregar as telas de jogo
        // 2. Receber e processar dados de entrada
        state->Update(dt); // 3.
        state->Render(); // 4.

        SDL_RenderPresent(renderer);
        SDL_Delay(33);

        dt += 33;
        // Uint32 endTime = SDL_GetTicks();
        // Uint32 frameTimeElapsedTotal = endTime - startTime;
        // if (frameTimeElapsedTotal < frameTime) {
        //     SDL_Delay(static_cast<Uint32>(frameTime - frameTimeElapsedTotal));
        // }

        // lastFrameTime = startTime;
    }
}

int main (int argc, char** argv) {
    Game& game = Game::GetInstance();

    game.Run();

    delete &game;

    return 0;
}