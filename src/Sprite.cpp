#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include <iostream>

#include "Sprite.h"
#include "Game.h"

Sprite::Sprite() : texture(nullptr), width(0), height(0) { }

Sprite::Sprite(const std::string& file) : texture(nullptr), width(0), height(0) {
    Open(file);
}

Sprite::~Sprite() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(const std::string& file) {
    if (texture) {
        SDL_DestroyTexture(texture);
    }

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

    if (!texture) {
        std::cerr << "Failed to load texture: " << SDL_GetError() << std::endl;
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

void Sprite::Render(int x, int y) {
    SDL_Rect dstRect = {x, y, clipRect.w, clipRect.h};
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
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
