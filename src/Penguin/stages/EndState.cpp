#define INCLUDE_SDL
#include "../../Engine/SDL_include.h"

#include <iostream>
using namespace std;

#include "../../Engine/components/headers/CameraFollower.h"
#include "../../Engine/components/headers/Text.h"
#include "../../Engine/utils/headers/GameData.h"
#include "../../Engine/core/headers/InputManager.h"
#include "../../Engine/core/headers/Camera.h"
#include "../../Engine/core/headers/Game.h"
#include "headers/EndState.h"
#include "headers/StageState.h"

EndState::EndState() : renderHint(false) { }

EndState::~EndState() { 
    delete hint;
    delete music;
}

void EndState::Start() {
    LoadAssets();
    music->Play();
    
    GameObject* go = new GameObject();
    new Sprite(*go, GameData::playerVictory.value() ? "assets/img/win.jpg" : "assets/img/lose.jpg");
    new CameraFollower(*go);
    AddObject(go);

    hint = new GameObject();
    SDL_Color color = {255, 0, 0, 255};
    new Text(*hint, "assets/font/Call me maybe.ttf", 48, Text::SOLID, "Press space to play again, or esc to quit.", color);
    Camera::Follow(hint);

    StartArray();

    started = true;
} 

void EndState::LoadAssets() {
    music = new Music(GameData::playerVictory.value() ? "assets/audio/endStateWin.ogg" : "assets/audio/endStateLose.ogg");
}


void EndState::Update(float dt) {
    InputManager& inputManager = InputManager::GetInstance();
    if (inputManager.WasKeyPressed(SPACE_KEY)) {
        Game::GetInstance().Push((State*) new StageState());
        GameData::playerVictory.reset();
        popRequested = true;
    }
    if (inputManager.WasKeyPressed(ESCAPE_KEY)) {
        quitRequested = true;
    }

    switch (int(timer.Get())) {
        case 0:
            renderHint = false;
            timer.Update(dt);
            break;
        case 1:
            hint->box.SetCenter(Vec2(512, 300));
            renderHint = true;
            timer.Update(dt);
            break;
        default:
            timer.Restart();
            break;
    }
    
    UpdateArray(dt);

    Camera::Update(dt);
}

void EndState::Render() {
    RenderArray();
    if (renderHint) hint->Render();
}

void EndState::Pause() { }
void EndState::Resume() { }