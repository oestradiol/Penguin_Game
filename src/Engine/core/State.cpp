using namespace std;

#include "headers/State.h"
#include "../utils/headers/Collision.h"
#include "../core/headers/InputManager.h"

State::State()
    : popRequested(false), quitRequested(false), started(false) { }

State::~State() {
    objectArray.clear();
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

void State::StartArray() {
    size_t len = objectArray.size();
    for (size_t i = 0; i < len; i++)
        objectArray[i]->Start();
}

void State::UpdateArray(float dt) {
    InputManager& inputManager = InputManager::GetInstance();
    if (inputManager.QuitRequested()) {
        quitRequested = true;
    }

    size_t initialLen = objectArray.size();
    size_t currLen = initialLen;
    for (size_t i = 0; i < initialLen; i++) {
        // Iterates reversed
        size_t idxi = initialLen - i - 1;
        auto currObjPtr = objectArray[idxi];

        // Call update if not destroyed
        if (!currObjPtr->IsDestroyed()) {
            currObjPtr->Update(dt);
        }
        
        // Erases if destroyed
        else {
            objectArray.erase(objectArray.begin() + idxi);
            currLen--;
        }

        // Calculates collision of current object with the ones already checked
        for (size_t j = 1; j < currLen - idxi; j++) {
            size_t idxj = idxi + j;
            auto otherObjPtr = objectArray[idxj];
            
            Sprite* currObjSpritePtr = (Sprite*) currObjPtr->GetComponent("Sprite");
            Sprite* otherObjSpritePtr = (Sprite*) otherObjPtr->GetComponent("Sprite");
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
}

void State::RenderArray() {
    size_t len = objectArray.size();
    for (size_t i = 0; i < len; i++)
        objectArray[i]->Render();
}