using namespace std;

#include "h_files/Sound.h"

Sound::Sound(GameObject& associated)
    : Component(associated), chunk(nullptr), channel(-1) { }

Sound::Sound(GameObject& associated, const string& file)
    : Component(associated), chunk(nullptr), channel(-1) {
    Open(file);
}

Sound::~Sound() {
    Stop();
    if (chunk) {
        Mix_FreeChunk(chunk);
    }
}

void Sound::Play(int times) {
    if (chunk) {
        channel = Mix_PlayChannel(-1, chunk, times - 1);
        if (channel == -1) {
            cerr << "Failed to allocate channel!\nError: " << Mix_GetError() << endl;
        }
    }
}

void Sound::Stop() {
    if (chunk && channel != -1) {
        Mix_HaltChannel(channel);
    }
}

void Sound::Open(const string& file) {
    Stop();
    if (chunk) {
        Mix_FreeChunk(chunk);
    }

    chunk = Mix_LoadWAV(file.c_str());

    if (!chunk) {
        cerr << "Sound: Failed to load WAV!\nError: " << Mix_GetError() << endl;
    }
}

bool Sound::IsOpen() const {
    return chunk != nullptr;
}
bool Sound::IsPlaying() const {
    return channel != -1 && Mix_Playing(channel);
}

void Sound::Update(float _) { }

void Sound::Render() { }

bool Sound::Is(const string& type) const {
    return type == "Sound";
}
