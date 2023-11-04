#pragma once

#define INCLUDE_SDL
#include "../../SDL_include.h"

#include "Component.h"
#include "Sprite.h"

class Collider : public Component {
public:
    Collider(GameObject& associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});
    
    void Render() override;
    void Update(float dt) override;
    bool Is(const std::string& type) const override;

    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);

    Rect box;

private:
    Vec2 scale;
    Vec2 offset;
};

inline bool Collider::Is(const std::string& type) const {
    return type == "Collider";
}

inline void Collider::SetScale(Vec2 scale) {
    this->scale = scale;
}

inline void Collider::SetOffset(Vec2 offset) {
    this->offset = offset;
}