#pragma once

#include <vector>
#include <memory>

#include "../../utils/headers/TileSet.h"
#include "GameObject.h"
#include "Music.h"

class State {
public:
    State();
    ~State();

    void Start();

    void LoadAssets();
    void Update(float dt);
    void Render();

    std::weak_ptr<GameObject> AddObject(GameObject* go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go) const;

    bool QuitRequested() const;

private:
    bool quitRequested;
    bool started;

    std::vector<std::shared_ptr<GameObject>> objectArray;

    Music* music;
    TileSet* tileSet;
};

inline bool State::QuitRequested() const {
    return quitRequested;
}