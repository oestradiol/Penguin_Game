#define INCLUDE_SDL
#include "../SDL_include.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
using namespace std;

#include "../components/headers/CameraFollower.h"
#include "../components/headers/PenguinBody.h"
#include "../components/headers/TileMap.h"
#include "../components/headers/Alien.h"
#include "../utils/headers/Collision.h"
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

    go = new GameObject();
    new PenguinBody(*go);
    go->box.SetCenter(Vec2(704, 640));
    Camera::Follow(go);
    AddObject(go);

    size_t len = objectArray.size();
    for (size_t i = 0; i < len; i++)
        objectArray[i]->Start();

    started = true;
}

void State::LoadAssets() {
    music = new Music("assets/audio/stageState.ogg");
    tileSet = new TileSet(64, 64, "assets/img/tileset.png");
}

void State::Update(float dt) {
    InputManager& inputManager = InputManager::GetInstance();

    if (inputManager.WasKeyPressed(ESCAPE_KEY) || inputManager.QuitRequested()) {
        quitRequested = true;
    }
    
    size_t initialLen = objectArray.size();
    size_t currLen = initialLen;
    for (size_t i = 0; i < initialLen; i++) {
        // Iterates reversed
        size_t idxi = initialLen - i - 1;
        auto currObjPtr = objectArray[idxi];

        // Call update if not deleted
        if (!currObjPtr->IsDestroyed()) {
            currObjPtr->Update(dt);
        }
        
        // Erases if deleted
        else {
            objectArray.erase(objectArray.begin() + idxi);
            currLen--;
        }

        // Calculates collision of current object with the ones already checked
        for (size_t j = 1; j < currLen - idxi; j++) {
            size_t idxj = idxi + j;
            auto otherObjPtr = objectArray[idxj];
            
            Sprite* currObjSpritePtr = static_cast<Sprite*>(currObjPtr->GetComponent("Sprite"));
            Sprite* otherObjSpritePtr = static_cast<Sprite*>(otherObjPtr->GetComponent("Sprite"));
            float angleCurrObj = currObjSpritePtr ? currObjSpritePtr->GetRotation() * M_PI / 180 : 0;
            float angleOtherObj = otherObjSpritePtr ? otherObjSpritePtr->GetRotation() * M_PI / 180 : 0;
            if (!Collision::IsColliding(
                    currObjPtr->box,
                    otherObjPtr->box,
                    angleCurrObj,
                    angleOtherObj
                )) continue;
            
            currObjPtr->NotifyCollision(*otherObjPtr);
            otherObjPtr->NotifyCollision(*currObjPtr);
        }
    }

    Camera::Update(dt);
}

void State::Render() {
    size_t len = objectArray.size();
    for (size_t i = 0; i < len; i++) {
        objectArray[i]->Render();
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
    size_t len = objectArray.size();
    for (size_t i = 0; i < len; i++) {
        shared_ptr<GameObject> obj = objectArray[i];
        if (obj.get() == go) {
            return obj;
        }
    }
    
    return shared_ptr<GameObject>(nullptr);
}