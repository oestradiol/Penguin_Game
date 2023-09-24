#define INCLUDE_SDL
#include "../SDL_include.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
using namespace std;

#include "../components/headers/PostDeletionAction.h"
#include "../components/headers/CameraFollower.h"
#include "../components/headers/TileMap.h"
#include "../components/headers/Sound.h"
#include "../components/headers/Face.h"
#include "headers/InputManager.h"
#include "headers/Camera.h"
#include "headers/State.h"

State::State()
    : music("assets/audio/stageState.ogg"), quitRequested(false) {
    music.Play();

    LoadAssets();
}
State::~State() {
    objectArray.clear();
    delete tileSet;
}

void State::LoadAssets() {
    // Initialize map
    GameObject* go = new GameObject();
    new Sprite(*go, "assets/img/ocean.jpg");
    new CameraFollower(*go);
    objectArray.emplace_back(go);

    go = new GameObject();
    tileSet = new TileSet(64, 64, "assets/img/tileset.png");
    new TileMap(*go, "assets/map/tileMap.txt", tileSet);
    objectArray.emplace_back(go);
}

void State::Update(float dt) {
    InputManager& inputManager = InputManager::GetInstance();

    if (inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested()) {
        quitRequested = true;
    }

    if (inputManager.KeyPress(SPACE_KEY)) {
        pair<int, int> mousePos = Camera::GetMousePos();
        Vec2 objPos = Vec2(200, 0).Rotated(-M_PI + M_PI * (rand() % 1001) / 500.0) + Vec2(mousePos.first, mousePos.second);
        AddObject((int)objPos.x, (int)objPos.y);
    }
    
    size_t len = objectArray.size() - 1;
    for (size_t i = 0; i <= len; i++) {
        size_t pos = len - i;
        if (!objectArray[pos]->IsDestroyed()) {
            objectArray[pos]->Update(dt);
        } else {
            objectArray.erase(objectArray.begin() + pos);
        }
    }

    Camera::Update(dt);
}

void State::Render() {
    for (const auto& object : objectArray) {
        object->Render();
    }
}

void State::AddObject(int mouseX, int mouseY) {
    GameObject* go = new GameObject();

    Sprite* sprite = new Sprite(*go, "assets/img/penguinface.png");
    go->box.x = mouseX - go->box.w / 2;
    go->box.y = mouseY - go->box.h / 2;

    Face* face = new Face(*go);
    Sound* sound = new Sound(*go, "assets/audio/boom.wav");

    *new PostDeletionAction(*go) += make_pair(
        new Action([go, sprite, face, sound]() {
            sprite->Destroy();
            face->Destroy();
            sound->Play();
        }),
        new CanDeleteAction(bind(&Sound::IsPlaying, sound))
    );

    objectArray.emplace_back(go);
}