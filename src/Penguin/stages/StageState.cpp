#define INCLUDE_SDL
#include "../../Engine/SDL_include.h"

#include <iostream>
using namespace std;

#include "../../Engine/components/headers/CameraFollower.h"
#include "../../Engine/components/headers/PenguinBody.h"
#include "../../Engine/components/headers/TileMap.h"
#include "../../Engine/components/headers/Alien.h"
#include "../../Engine/core/headers/InputManager.h"
#include "../../Engine/utils/headers/GameData.h"
#include "../../Engine/core/headers/Camera.h"
#include "../../Engine/core/headers/Game.h"
#include "headers/StageState.h"
#include "headers/EndState.h"

StageState::StageState() : music(nullptr), tileSet(nullptr) { }

StageState::~StageState() {
    delete tileSet;
    delete music;
}

void StageState::Start() {
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
    new Alien(*go, 3, -.5);
    go->box.SetCenter(Vec2(0, 0));
    AddObject(go);

    go = new GameObject();
    new Alien(*go, 3, -.25);
    go->box.SetCenter(Vec2(0, 1280));
    AddObject(go);

    go = new GameObject();
    new Alien(*go, 3);
    go->box.SetCenter(Vec2(1408, 1280));
    AddObject(go);

    go = new GameObject();
    new Alien(*go, 3, .25);
    go->box.SetCenter(Vec2(1408, 0));
    AddObject(go);

    go = new GameObject();
    new Alien(*go, 3, .5);
    go->box.SetCenter(Vec2(512, 300));
    AddObject(go);

    go = new GameObject();
    new PenguinBody(*go);
    go->box.SetCenter(Vec2(704, 640));
    Camera::Follow(go);
    AddObject(go);

    StartArray();

    started = true;
}

void StageState::LoadAssets() {
    music = new Music("assets/audio/stageState.ogg");
    tileSet = new TileSet(64, 64, "assets/img/tileset.png");
}

void StageState::Update(float dt) {
    InputManager& inputManager = InputManager::GetInstance();
    if (inputManager.WasKeyPressed(ESCAPE_KEY)) {
        popRequested = true;
    }
    if (GameData::playerVictory.has_value()) {
        Game::GetInstance().Push((State*) new EndState());
        popRequested = true;
    }
    
    UpdateArray(dt);

    Camera::Update(dt);
}

void StageState::Render() {
    RenderArray();
}

void StageState::Pause() { }
void StageState::Resume() { }