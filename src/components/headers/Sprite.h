#pragma once

#define INCLUDE_SDL
#include "../../SDL_include.h"

#include <string>

#include "Component.h"

class Sprite : public Component {
public:
    Sprite(GameObject& associated);
    Sprite(GameObject& associated, const std::string& file);

    void Open(const std::string& file);
    void SetClip(int x, int y, int w, int h);
    
    void Render() override;
    void Render(int x, int y);
    
    void Update(float dt) override;
    bool Is(const std::string& type) const override;

    int GetWidth() const;
    int GetHeight() const;
    bool IsOpen() const;

private:
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;
};

inline bool Sprite::Is(const std::string& type) const {
    return type == "Sprite";
}

inline int Sprite::GetWidth() const {
    return width;
}

inline int Sprite::GetHeight() const {
    return height;
}

inline bool Sprite::IsOpen() const {
    return texture != nullptr;
}