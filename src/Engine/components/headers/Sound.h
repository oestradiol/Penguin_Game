#pragma once

#define INCLUDE_SDL_MIXER
#include "../../SDL_include.h"

#include <string>

#include "Component.h"

class Sound : public Component {
public:
    Sound(GameObject& associated);
    Sound(GameObject& associated, const std::string& file);
    ~Sound();

    void Play(int times = 1);
    void Stop();
    void Open(const std::string& file);
    bool IsOpen() const;
    bool IsPlaying() const;

    bool Is(const std::string& type) const override;

private:
    std::shared_ptr<Mix_Chunk> chunk;
    int channel;
};

inline bool Sound::IsOpen() const {
    return chunk != nullptr;
}

inline bool Sound::Is(const std::string& type) const {
    return type == "Sound";
}