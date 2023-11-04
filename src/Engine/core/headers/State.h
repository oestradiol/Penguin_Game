#pragma once

#include <vector>
#include <memory>

#include "../../utils/headers/TileSet.h"
#include "GameObject.h"
#include "Music.h"

class State {
public:
    State();
    virtual ~State();

    virtual void LoadAssets() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;

    virtual void Start() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;

    std::weak_ptr<GameObject> AddObject(GameObject* go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go) const;

    bool PopRequested() const;
    bool QuitRequested() const;

protected:
    virtual void StartArray();
    virtual void UpdateArray(float dt);
    virtual void RenderArray();

    bool popRequested;
    bool quitRequested;
    bool started;

    std::vector<std::shared_ptr<GameObject>> objectArray;
};

inline bool State::PopRequested() const {
    return popRequested;
}

inline bool State::QuitRequested() const {
    return quitRequested;
}