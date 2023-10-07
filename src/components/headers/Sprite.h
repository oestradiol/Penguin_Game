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

    void Start() override;
    void Render() override;
    void Render(int x, int y, Vec2 dimensions);
    
    void Update(float dt) override;
    bool Is(const std::string& type) const override;
    
    void SetRotation(double angleDeg);
    double GetRotation() const;

    void SetScale(float scaleX, float scaleY);
    Vec2 GetScale() const;

    int GetWidth() const;
    int GetHeight() const;
    bool IsOpen() const;

private:
    SDL_Texture* texture;
    int width;
    int height;
    Vec2 scale;
    double angleDeg;
    SDL_Rect clipRect;
};

inline bool Sprite::Is(const std::string& type) const {
    return type == "Sprite";
}

inline int Sprite::GetWidth() const {
    return width * scale.x;
}

inline int Sprite::GetHeight() const {
    return height * scale.y;
}

inline bool Sprite::IsOpen() const {
    return texture != nullptr;
}

inline void Sprite::SetRotation(double angleDeg) {
    this->angleDeg = angleDeg;
}

inline double Sprite::GetRotation() const {
    return angleDeg;
}

inline Vec2 Sprite::GetScale() const {
    return scale;
}