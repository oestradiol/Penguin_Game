#pragma once

#include "GameObject.h"
#include "../../utils/headers/Vec2.h"

class Camera {
public:
    static void Follow(GameObject* newFocus);
    static void Unfollow(GameObject* ifFocus = nullptr);
    static void Update(float dt);

    static Vec2 pos;
    static Vec2 speed;

    static std::pair<int, int> GetMousePos();

private:
    static GameObject* focus;
};

inline void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

inline void Camera::Unfollow(GameObject* ifFocus) {
    if (ifFocus == focus || ifFocus == nullptr)
        focus = nullptr;
}