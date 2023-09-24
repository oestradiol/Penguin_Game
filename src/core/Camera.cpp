#include "headers/Camera.h"
#include "headers/InputManager.h"
#include "headers/Game.h"

using namespace std;

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos;
Vec2 Camera::speed;

#define baseSpeed 500
void Camera::Update(float dt) {
    if (focus != nullptr) {
        int *w = nullptr, *h = nullptr;
        SDL_GetRendererOutputSize(Game::GetInstance().GetRenderer(), w, h);
        pos = focus->box.Center() - Vec2(*w / 2, *h / 2);
    } else {
        speed = { 0, 0 };

        InputManager& inputManager = InputManager::GetInstance();
        speed.x = baseSpeed * (
            (inputManager.IsKeyDown(RIGHT_ARROW_KEY) || inputManager.IsKeyDown(D_KEY)) -
            (inputManager.IsKeyDown(LEFT_ARROW_KEY) || inputManager.IsKeyDown(A_KEY))
        );
        speed.y = baseSpeed * (
            (inputManager.IsKeyDown(DOWN_ARROW_KEY) || inputManager.IsKeyDown(S_KEY)) -
            (inputManager.IsKeyDown(UP_ARROW_KEY) || inputManager.IsKeyDown(W_KEY))
        );

        pos += speed * dt;
    }
}

pair<int, int> Camera::GetMousePos() {
    InputManager& inputManager = InputManager::GetInstance();
    return make_pair(
        inputManager.GetMouseX() + pos.x,
        inputManager.GetMouseY() + pos.y
    );
}