#include <iostream>
#include <stdexcept>
using namespace std;

#include "headers/Camera.h"
#include "headers/InputManager.h"
#include "headers/Game.h"

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos;
Vec2 Camera::speed;

#define baseSpeed 500
void Camera::Update(float dt) {
    if (focus != nullptr) {
        int w, h;

        pos = Vec2(0,0);
        int result = SDL_GetRendererOutputSize(Game::GetInstance().GetRenderer(), &w, &h);
        if (result) {
            cerr << "Game: Failed to get Renderer Output Size.\nError: " << SDL_GetError() << endl;
        } else if (w && h) {
            pos -= Vec2(w / 2, h / 2);
        } else { // Em último caso, tentamos ao menos usar o valor inicial do tamanho...
            pos -= Vec2(Game::WIN_WIDTH / 2, Game::WIN_HEIGHT / 2);
        }
        pos += focus->box.Center();
    } else {
        speed = { 0, 0 };

        InputManager& inputManager = InputManager::GetInstance();
        speed.x = baseSpeed * (
            (inputManager.IsKeyPressed(RIGHT_ARROW_KEY) || inputManager.IsKeyPressed(D_KEY)) -
            (inputManager.IsKeyPressed(LEFT_ARROW_KEY) || inputManager.IsKeyPressed(A_KEY))
        );
        speed.y = baseSpeed * (
            (inputManager.IsKeyPressed(DOWN_ARROW_KEY) || inputManager.IsKeyPressed(S_KEY)) -
            (inputManager.IsKeyPressed(UP_ARROW_KEY) || inputManager.IsKeyPressed(W_KEY))
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