#include <iostream>
using namespace std;

#include "h_files/Music.h"
#include "h_files/Resources.h"

Music::Music()
    : music(nullptr) { }

Music::Music(const string& file)
    : music(nullptr) {
    Open(file);
}

Music::~Music() {
    Stop();
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
    music = Resources::GetMusic(file);
}

bool Music::IsOpen() const {
    return music != nullptr;
}
