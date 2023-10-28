#include <iostream>
using namespace std;

#include "headers/Resources.h"
#include "headers/Game.h"

unordered_map<string, SDL_Texture*> Resources::imageTable;
unordered_map<string, Mix_Music*> Resources::musicTable;
unordered_map<string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(const string& file) {
    auto it = imageTable.find(file);
    if (it != imageTable.end()) {
        return it->second;
    }

    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (!texture) {
        cerr << "Resources: Failed to load texture!\nError: " << SDL_GetError() << endl;
        return nullptr;
    }

    imageTable[file] = texture;
    return texture;
}

void Resources::ClearImages() {
    for (auto i = imageTable.begin(); i != imageTable.end(); i++) {
        SDL_DestroyTexture(i->second);
    }
    imageTable.clear();
}

Mix_Music* Resources::GetMusic(const string& file) {
    auto it = musicTable.find(file);
    if (it != musicTable.end()) {
        return it->second;
    }

    Mix_Music* music = Mix_LoadMUS(file.c_str());
    if (!music) {
        cerr << "Resources: Failed to load music!\nError: " << Mix_GetError() << endl;
        return nullptr;
    }

    musicTable[file] = music;
    return music;
}

void Resources::ClearMusics() {
    for (auto i = musicTable.begin(); i != musicTable.end(); i++) {
        Mix_FreeMusic(i->second);
    }
    musicTable.clear();
}

Mix_Chunk* Resources::GetSound(const string& file) {
    auto it = soundTable.find(file);
    if (it != soundTable.end()) {
        return it->second;
    }

    Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
    if (!chunk) {
        cerr << "Resources: Failed to load WAV!\nError: " << Mix_GetError() << endl;
        return nullptr;
    }

    soundTable[file] = chunk;
    return chunk;
}

void Resources::ClearSounds() {
    for (auto i = soundTable.begin(); i != soundTable.end(); i++) {
        Mix_FreeChunk(i->second);
    }
    soundTable.clear();
}
