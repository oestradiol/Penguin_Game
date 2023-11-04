#pragma once

#include <vector>
#include <memory>

#include "../../../Engine/utils/headers/Timer.h"
#include "../../../Engine/core/headers/GameObject.h"
#include "../../../Engine/core/headers/Music.h"
#include "../../../Engine/core/headers/State.h"

class EndState : State {
public:
    EndState();
    ~EndState();

    void LoadAssets() override;
    void Update(float dt) override;
    void Render() override;

    void Start() override;
    void Pause() override;
    void Resume() override;

private:
    Music* music;
    GameObject* hint;
    bool renderHint;
    Timer timer;
};