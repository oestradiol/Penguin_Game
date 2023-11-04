#pragma once

#include "../../../Engine/utils/headers/Timer.h"
#include "../../../Engine/core/headers/GameObject.h"
#include "../../../Engine/core/headers/Music.h"
#include "../../../Engine/core/headers/State.h"

class TitleState : State {
public:
    TitleState();
    ~TitleState();

    void LoadAssets() override;
    void Update(float dt) override;
    void Render() override;

    void Start() override;
    void Pause() override;
    void Resume() override;

private:
    bool renderHint;
    GameObject* hint;
    Timer timer;
};

inline void TitleState::LoadAssets() { }