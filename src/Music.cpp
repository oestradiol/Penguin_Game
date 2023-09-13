#include <iostream>
using namespace std;

#include "h_files/Music.h"

Music::Music() : music(nullptr) {}

Music::Music(const string& file) : music(nullptr) {
    Open(file);
}

Music::~Music() {
    Stop();
    if (music) {
        Mix_FreeMusic(music);
    }
}

void Music::Play(int times) {
    if (music) {
        Mix_PlayMusic(music, times);
    }
}

void Music::Stop(int msToStop) {
    if (music && Mix_PlayingMusic()) {
        Mix_FadeOutMusic(msToStop);
    }
}

void Music::Open(const string& file) {
    if (music) {
        Mix_FreeMusic(music);
    }

    music = Mix_LoadMUS(file.c_str());

    if (!music) {
        cerr << "Failed to load music: " << Mix_GetError() << endl;
    }
}

bool Music::IsOpen() const {
    return music != nullptr;
}
