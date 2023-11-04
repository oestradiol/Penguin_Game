#define INCLUDE_SDL
#include "../../Engine/SDL_include.h"

#include <iostream>
using namespace std;

#include "../../Engine/components/headers/CameraFollower.h"
#include "../../Engine/components/headers/Text.h"
#include "../../Engine/core/headers/InputManager.h"
#include "../../Engine/core/headers/Camera.h"
#include "../../Engine/core/headers/Game.h"
#include "headers/TitleState.h"
#include "headers/StageState.h"

TitleState::TitleState() : renderHint(false) { }

TitleState::~TitleState() {
    delete hint;
}

void TitleState::Start() {
    LoadAssets();

    GameObject* go = new GameObject();
    new Sprite(*go, "assets/img/title.jpg");
    new CameraFollower(*go);
    AddObject(go);

    hint = new GameObject();
    SDL_Color color = {255, 0, 0, 255};
    new Text(*hint, "assets/font/Call me maybe.ttf", 48, Text::SOLID, "Press space to start!", color);
    Camera::Follow(hint);

    StartArray();

    started = true;
}

void TitleState::Update(float dt) {
    InputManager& inputManager = InputManager::GetInstance();
    if (inputManager.WasKeyPressed(SPACE_KEY)) {
        Game::GetInstance().Push((State*) new StageState());
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

void TitleState::Render() {
    RenderArray();
    if (renderHint) hint->Render();
}

void TitleState::Pause() {
    Camera::Unfollow(hint);
}

void TitleState::Resume() {
    Camera::Follow(hint);
}