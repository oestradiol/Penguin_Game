#include <iostream>
using namespace std;

#include "../core/headers/Resources.h"
#include "headers/Music.h"

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
        Mix_PlayMusic(music.get(), times);
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