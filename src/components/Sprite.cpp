#define INCLUDE_SDL_IMAGE
#include "../SDL_include.h"

#include <iostream>
using namespace std;

#include "../core/headers/Resources.h"
#include "../core/headers/Camera.h"
#include "../core/headers/Game.h"
#include "headers/Sprite.h"

Sprite::Sprite(GameObject& associated)
    : Component(associated), texture(nullptr), width(0), height(0), scale(1, 1), angleDeg(0) { }

Sprite::Sprite(GameObject& associated, const string& file)
    : Component(associated), texture(nullptr), width(0), height(0), scale(1, 1), angleDeg(0) {
    Open(file);
}

void Sprite::Start() {
    started = true;
}

void Sprite::Open(const string& file) {
    texture = Resources::GetImage(file);

    if (texture) {
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
        SetClip(0, 0, width, height);
    }
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
    associated.box.w = width;
    associated.box.h = height;
}

void Sprite::Render() {
    Vec2& cameraPos = Camera::pos;
    Rect& objectBox = associated.box;
    int x = objectBox.x - cameraPos.x;
    int y = objectBox.y - cameraPos.y;
    Render(x, y, Vec2(objectBox.w, objectBox.h));
}

void Sprite::Render(int x, int y, Vec2 dimensions) {
    if (!texture) {
        return;
    }

    SDL_Rect dstRect = { x, y, int(dimensions.x), int(dimensions.y) };
    SDL_RendererFlip flipType = SDL_FLIP_NONE;
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, angleDeg, nullptr, flipType);
}

void Sprite::Update(float dt) { }

void Sprite::SetScale(float scaleX, float scaleY) {
    scale.x = scaleX != 0 ? scaleX : scale.x;
    scale.y = scaleY != 0 ? scaleY : scale.y;
    Vec2 boxCenter = associated.box.Center();
    associated.box.w = static_cast<int>(width * scale.x);
    associated.box.h = static_cast<int>(height * scale.y);
    associated.box.SetCenter(boxCenter);
}
