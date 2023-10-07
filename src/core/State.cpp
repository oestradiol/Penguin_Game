#define INCLUDE_SDL
#include "../SDL_include.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
using namespace std;

#include "../components/headers/CameraFollower.h"
#include "../components/headers/TileMap.h"
#include "../components/headers/Alien.h"
#include "headers/InputManager.h"
#include "headers/Camera.h"
#include "headers/State.h"

State::State()
    : quitRequested(false), started(false) { }

State::~State() {
    objectArray.clear();
    delete tileSet;
    delete music;
}

void State::Start() {
    LoadAssets();
    music->Play();

    GameObject* go = new GameObject();
    new Sprite(*go, "assets/img/ocean.jpg");
    new CameraFollower(*go);
    AddObject(go);

    go = new GameObject();
    new TileMap(*go, "assets/map/tileMap.txt", tileSet);
    AddObject(go);

    go = new GameObject();
    new Alien(*go, 3);
    go->box.SetCenter(Vec2(512, 300));
    AddObject(go);

    for (const auto& object : objectArray)
        object->Start();

    started = true;
}

void State::LoadAssets() {
    music = new Music("assets/audio/stageState.ogg");
    tileSet = new TileSet(64, 64, "assets/img/tileset.png");
}

void State::Update(float dt) {
    InputManager& inputManager = InputManager::GetInstance();

    if (inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested()) {
        quitRequested = true;
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

weak_ptr<GameObject> State::AddObject(GameObject* go) {
    shared_ptr<GameObject> goPtr(go);
    objectArray.push_back(goPtr);

    if (started)
        goPtr->Start();

    return goPtr;
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) const {
    for (const auto& object : objectArray) {
        if (object.get() == go) {
            return object;
        }
    }
    
    return shared_ptr<GameObject>(nullptr);
}