#pragma once

#define INCLUDE_SDL
#include "../../SDL_include.h"

#include <string>

#include "../../utils/headers/Timer.h"

#include "Component.h"

class Sprite : public Component {
public:
    Sprite(GameObject& associated);
    Sprite(GameObject& associated, const std::string& file, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);

    void Render() override;
    void Render(int x, int y, Vec2 dimensions) const;
    
    void Update(float dt) override;
    bool Is(const std::string& type) const override;

    bool IsOpen() const;

    void Open(const std::string& file);
    void SetClip(int x, int y, int w, int h);
    
    void SetRotation(double angleDeg);
    double GetRotation() const;

    void SetScale(float scaleX, float scaleY);
    Vec2 GetScale() const;

    int GetWidth() const;
    int GetHeight() const;

    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(float frameTime);

private:
    std::shared_ptr<SDL_Texture> texture;
    int width;
    int height;
    Vec2 scale;
    double angleDeg;
    SDL_Rect clipRect;
    int frameCount;
    int currentFrame;
    float timeElapsed;
    float frameTime;
    float secondsToSelfDestruct; 
    Timer selfDestructCount;
};

inline bool Sprite::Is(const std::string& type) const {
    return type == "Sprite";
}

inline int Sprite::GetWidth() const {
    return scale.x * width / frameCount;
}

inline int Sprite::GetHeight() const {
    return scale.y * height;
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

inline void Sprite::SetFrame(int frame) {
    currentFrame = frame % frameCount;
    SetClip(currentFrame * clipRect.w, clipRect.y, clipRect.w, clipRect.h);
}

inline void Sprite::SetFrameTime(float frameTime) {
    this->frameTime = frameTime;
}