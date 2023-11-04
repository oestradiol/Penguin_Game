using namespace std;

#include "../core/headers/Game.h"
#include "../core/headers/Resources.h"
#include "../core/headers/Camera.h"
#include "headers/Text.h"

Text::Text(GameObject& associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color)
    : Component(associated), font(nullptr), texture(nullptr), text(text), style(style), fontFile(fontFile), fontSize(fontSize), color(color) {
    RemakeTexture();
}

Text::~Text() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Text::Update(float dt) { }

void Text::Render() {
    if (texture) {
        Vec2& cameraPos = Camera::pos;
        Rect& objectBox = associated.box;
        int x = objectBox.x - cameraPos.x;
        int y = objectBox.y - cameraPos.y;

        SDL_Rect clipRect = { 0, 0, int(objectBox.w), int(objectBox.h) };
        SDL_Rect dstRect = { x, y, clipRect.w, clipRect.h };

        SDL_RendererFlip flipType = SDL_FLIP_NONE;
        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, 0, nullptr, flipType);
    }
}

void Text::SetText(const string& text) {
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
    this->style = style;
    RemakeTexture();
}

void Text::SetFontFile(const string& fontFile) {
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    font = Resources::GetFont(fontFile, fontSize);  
    if (!font) return;

    SDL_Surface* surface;
    switch (style) {
        case SOLID:
            surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
            break;

        case SHADED: {
            SDL_Color bgColor = {0, 0, 0, 255};
            surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, bgColor);
            break;
        }

        case BLENDED:
            surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
            break;
    }

    if (surface) {
        texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);

        if (texture) {
            associated.box.w = surface->w;
            associated.box.h = surface->h;
        }

        SDL_FreeSurface(surface);
    }
}
