#pragma once

#include <vector>
#include <memory>

#include "Sprite.h"
#include "Music.h"

class State {
public:
    State();
    ~State();

    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();

    void Input();
    void AddObject(int mouseX, int mouseY);

private:
    Music music;
    bool quitRequested;

    std::vector<std::unique_ptr<GameObject>> objectArray;
};