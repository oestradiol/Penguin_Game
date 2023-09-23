#pragma once

#include <vector>
#include <memory>

#include "../../components/headers/Music.h"
#include "GameObject.h"

class State {
public:
    State();
    ~State();

    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();

    void AddObject(int mouseX, int mouseY);

private:
    Music music;
    bool quitRequested;

    std::vector<std::unique_ptr<GameObject>> objectArray;
};

inline bool State::QuitRequested() {
    return quitRequested;
}