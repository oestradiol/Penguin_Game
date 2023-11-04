#pragma once

#include "../../../Engine/utils/headers/TileSet.h"
#include "../../../Engine/core/headers/Music.h"
#include "../../../Engine/core/headers/State.h"

class StageState : State {
public:
    StageState();
    ~StageState();

    void LoadAssets() override;
    void Update(float dt) override;
    void Render() override;

    void Start() override;
    void Pause() override;
    void Resume() override;

private:
    Music* music;
    TileSet* tileSet;
};