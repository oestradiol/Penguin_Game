#pragma once

#define INCLUDE_SDL
#include "../../SDL_include.h"

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN

#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT

#define ESCAPE_KEY SDLK_ESCAPE
#define SPACE_KEY SDLK_SPACE
#define W_KEY SDLK_w
#define A_KEY SDLK_a
#define S_KEY SDLK_s
#define D_KEY SDLK_d

#include <unordered_map>

class InputManager {
public:
    static InputManager& GetInstance();

    void Update();

    bool WasKeyPressed(int key);
    bool WasKeyReleased(int key);
    bool IsKeyPressed(int key);

    bool WasMousePressed(int button) const;
    bool WasMouseReleased(int button) const;
    bool IsMousePressed(int button) const;

    int GetMouseX() const;
    int GetMouseY() const;

    bool QuitRequested() const;

private:
    InputManager();

    bool mouseState[6];
    int mouseUpdate[6];

    std::unordered_map<int, bool> keyState;
    std::unordered_map<int, int> keyUpdate;

    bool quitRequested;

    int updateCounter;

    int mouseX;
    int mouseY;
};

inline bool InputManager::IsKeyPressed(int key) {
    return keyState[key];
}

inline bool InputManager::IsMousePressed(int button) const {
    return mouseState[button];
}

inline int InputManager::GetMouseX() const {
    return mouseX;
}

inline int InputManager::GetMouseY() const {
    return mouseY;
}

inline bool InputManager::QuitRequested() const {
    return quitRequested;
}