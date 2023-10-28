#define INCLUDE_SDL_IMAGE
#include "../SDL_include.h"

#include <iostream>
using namespace std;

#include "../core/headers/Resources.h"
#include "../core/headers/Camera.h"
#include "../core/headers/Game.h"
#include "headers/PostDeletionAction.h"
#include "headers/Sprite.h"

Sprite::Sprite(GameObject& associated)
    : Component(associated), texture(nullptr), width(0), height(0), scale(1, 1), angleDeg(0), frameCount(1), currentFrame(0), timeElapsed(0), frameTime(0) { }

Sprite::Sprite(GameObject& associated, const string& file, int frameCount, float frameTime, float secondsToSelfDestruct)
    : Component(associated), texture(nullptr), width(0), height(0), scale(1, 1), angleDeg(0), currentFrame(0), timeElapsed(0), secondsToSelfDestruct(secondsToSelfDestruct) {
    this->frameCount = frameCount;
    this->frameTime = frameTime;
    Open(file);
}

void Sprite::Open(const string& file) {
    texture = Resources::GetImage(file);

    if (texture) {
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
        SetClip(0, 0, width / frameCount, height);
        associated.box.w = clipRect.w;
        associated.box.h = clipRect.h;
    }
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render() {
    Vec2& cameraPos = Camera::pos;
    Rect& objectBox = associated.box;
    int x = objectBox.x - cameraPos.x;
    int y = objectBox.y - cameraPos.y;
    Render(x, y, Vec2(objectBox.w, objectBox.h));
}

void Sprite::Render(int x, int y, Vec2 dimensions) const {
    if (!texture) {
        return;
    }

    SDL_Rect dstRect = { x, y, int(dimensions.x), int(dimensions.y) };
    SDL_RendererFlip flipType = SDL_FLIP_NONE;
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, angleDeg, nullptr, flipType);
}

void Sprite::Update(float dt) {
    timeElapsed += dt;
    if (timeElapsed > frameTime) {
        timeElapsed = 0;
        currentFrame = (currentFrame + 1) % frameCount;
        SetClip(currentFrame * clipRect.w, clipRect.y, clipRect.w, clipRect.h);
    }

    if (secondsToSelfDestruct <= 0) return;

    selfDestructCount.Update(dt);
    if (selfDestructCount.Get() > secondsToSelfDestruct) {
        PostDeletionAction* postDeletionAction = (PostDeletionAction*) associated.GetComponent("PostDeletionAction");
        if (postDeletionAction) {
            (*postDeletionAction)();
        } else {
            associated.Destroy();
        }
    }
}

void Sprite::SetScale(float scaleX, float scaleY) {
    float prevScaleX = scale.x;
    float prevScaleY = scale.y;
    scale.x = scaleX != 0 ? scaleX : scale.x;
    scale.y = scaleY != 0 ? scaleY : scale.y;

    Vec2 boxCenter = associated.box.Center();
    associated.box.w = int(scale.x * associated.box.w / prevScaleX);
    associated.box.h = int(scale.y * associated.box.h / prevScaleY);
    associated.box.SetCenter(boxCenter);
}

void Sprite::SetFrameCount(int frameCount) {
    this->frameCount = frameCount;
    int newWidth = width / frameCount;
    SetClip(currentFrame * newWidth, clipRect.y, newWidth, clipRect.h);

    Vec2 boxCenter = associated.box.Center();
    associated.box.w = int(newWidth * scale.x);
    associated.box.SetCenter(boxCenter);
}