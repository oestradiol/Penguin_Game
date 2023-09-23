#pragma once

#define INCLUDE_SDL
#include "../../SDL_include.h"

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN

#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT

#define ESCAPE_KEY SDLK_ESCAPE
#define SPACE_KEY SDLK_SPACE

#include <unordered_map>

class InputManager {
public:
    static InputManager& GetInstance();

    void Update();

    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);

    bool MousePress(int button) const;
    bool MouseRelease(int button) const;
    bool IsMouseDown(int button) const;

    int GetMouseX() const;
    int GetMouseY() const;

    bool QuitRequested() const;

private:
    InputManager();
    ~InputManager();

    bool mouseState[6];
    int mouseUpdate[6];

    std::unordered_map<int, bool> keyState;
    std::unordered_map<int, int> keyUpdate;

    bool quitRequested;

    int updateCounter;

    int mouseX;
    int mouseY;
};

inline bool InputManager::IsKeyDown(int key) {
    return keyState[key];
}

inline bool InputManager::IsMouseDown(int button) const {
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