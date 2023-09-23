#include "headers/InputManager.h"

InputManager& InputManager::GetInstance() {
    static InputManager instance;
    return instance;
}

InputManager::InputManager()
    : quitRequested(false), updateCounter(-1), mouseX(0), mouseY(0) {
    for (int i = 0; i < 6; ++i) {
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }
}

InputManager::~InputManager() { }

void InputManager::Update() {
    SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;
    updateCounter++;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quitRequested = true;
                break;
            
            case SDL_MOUSEBUTTONDOWN:
                mouseState[event.button.button] = true;
                mouseUpdate[event.button.button] = updateCounter;
                break;
            
            case SDL_MOUSEBUTTONUP:
                mouseState[event.button.button] = false;
                mouseUpdate[event.button.button] = updateCounter;
                break;

            case SDL_KEYDOWN: {
                if (event.key.repeat != 0) break;
                SDL_Keycode eventCode = event.key.keysym.sym;
                keyState[eventCode] = true;
                keyUpdate[eventCode] = updateCounter;
                break;
            }
            case SDL_KEYUP: {
                if (event.key.repeat != 0) break;
                SDL_Keycode eventCode = event.key.keysym.sym;
                keyState[eventCode] = false;
                keyUpdate[eventCode] = updateCounter;
                break;
            }
            default:
                break;
        }
    }
}

bool InputManager::KeyPress(int key) {
    return (IsKeyDown(key) && (keyUpdate[key] == updateCounter));
}

bool InputManager::KeyRelease(int key) {
    return (!IsKeyDown(key) && (keyUpdate[key] == updateCounter));
}

bool InputManager::MousePress(int button) const {
    return (IsMouseDown(button) && (mouseUpdate[button] == updateCounter));
}

bool InputManager::MouseRelease(int button) const {
    return (!IsMouseDown(button) && (mouseUpdate[button] == updateCounter));
}
