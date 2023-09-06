#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>

#include "State.h"

State::State() : bg("img/ocean.jpg"), music("audio/stageState.ogg"), quitRequested(false) {
    music.Play();
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::LoadAssets() {
    // Pré carregar os assets do jogo, como imagens, fontes e músicas
}

void State::Update(float dt) {
    // Atualizar o estado das entidades, teste de colisões, etc.

    if (SDL_QuitRequested()) {
        quitRequested = true;
    }
}

void State::Render() {
    bg.Render(0, 0);
}
