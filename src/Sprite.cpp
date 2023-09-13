#define INCLUDE_SDL_IMAGE
#include "h_files/SDL_include.h"

#include <iostream>
using namespace std;

#include "h_files/Sprite.h"
#include "h_files/Game.h"
#include "h_files/GameObject.h"

Sprite::Sprite(GameObject& associated)
    : Component(associated), texture(nullptr), width(0), height(0) { }

Sprite::Sprite(GameObject& associated, const string& file)
    : Component(associated), texture(nullptr), width(0), height(0) {
    Open(file);
}

Sprite::~Sprite() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(const string& file) {
    if (texture) {
        SDL_DestroyTexture(texture);
    }

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

    if (!texture) {
        cerr << "Failed to load texture: " << SDL_GetError() << endl;
    } else {
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
        SetClip(0, 0, width, height);
    }
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render() {
    if (!texture) {
        return;
    }
    SDL_Rect dstRect = {
        static_cast<int>(associated.box.x),
        static_cast<int>(associated.box.y),
        clipRect.w,
        clipRect.h
    }
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
}

void Sprite::Update(float dt) {}

bool Sprite::Is(const std::string& type) const {
    return type == "Sprite";
}

int Sprite::GetWidth() const {
    return width;
}

int Sprite::GetHeight() const {
    return height;
}

bool Sprite::IsOpen() const {
    return texture != nullptr;
}
