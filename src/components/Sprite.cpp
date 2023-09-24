#define INCLUDE_SDL_IMAGE
#include "../SDL_include.h"

#include <iostream>
using namespace std;

#include "../core/headers/Resources.h"
#include "../core/headers/Camera.h"
#include "../core/headers/Game.h"
#include "headers/Sprite.h"

Sprite::Sprite(GameObject& associated)
    : Component(associated), texture(nullptr), width(0), height(0) { }

Sprite::Sprite(GameObject& associated, const string& file)
    : Component(associated), texture(nullptr), width(0), height(0) {
    Open(file);
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
    Render(x, y);
}

void Sprite::Render(int x, int y) {
    if (!texture) {
        return;
    }
    SDL_Rect dstRect = { x, y, clipRect.w, clipRect.h };
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
}

void Sprite::Update(float dt) { }