#pragma once

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <string>
#include <iostream>

#include "Component.h"
#include "GameObject.h"

class Sound : public Component {
public:
    Sound(GameObject& associated);
    Sound(GameObject& associated, const std::string& file);
    ~Sound();

    void Play(int times = 1);
    void Stop();
    void Open(const std::string& file);
    bool IsOpen() const;

    void Update(float dt) override;
    void Render() override;
    bool Is(const std::string& type) const override;

private:
    Mix_Chunk* chunk;
    int channel;
};