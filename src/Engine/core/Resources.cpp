#include <iostream>
using namespace std;

#include "headers/Resources.h"
#include "headers/Game.h"

unordered_map<string, shared_ptr<SDL_Texture>> Resources::imageTable;
unordered_map<string, shared_ptr<Mix_Music>> Resources::musicTable;
unordered_map<string, shared_ptr<Mix_Chunk>> Resources::soundTable;
unordered_map<string, shared_ptr<TTF_Font>> Resources::fontTable;

shared_ptr<SDL_Texture> Resources::GetImage(const string& file) {
    auto it = imageTable.find(file);
    if (it != imageTable.end()) {
        return it->second;
    }

    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (!texture) {
        cerr << "Resources: Failed to load texture!\nError: " << SDL_GetError() << endl;
        return nullptr;
    }

    shared_ptr<SDL_Texture> ptr(texture, [] (SDL_Texture* ptr) { SDL_DestroyTexture(ptr); });
    imageTable[file] = ptr;
    return ptr;
}

void Resources::ClearImages() {
    for (auto i = imageTable.begin(); i != imageTable.end();) {
        if (i->second.unique()) {
            imageTable.erase(i++);
        } else {
            i++;
        }
    }
    imageTable.clear();
}

shared_ptr<Mix_Music> Resources::GetMusic(const string& file) {
    auto it = musicTable.find(file);
    if (it != musicTable.end()) {
        return it->second;
    }

    Mix_Music* music = Mix_LoadMUS(file.c_str());
    if (!music) {
        cerr << "Resources: Failed to load music!\nError: " << Mix_GetError() << endl;
        return nullptr;
    }

    shared_ptr<Mix_Music> ptr(music, [] (Mix_Music* ptr) { Mix_FreeMusic(ptr); });
    musicTable[file] = ptr;
    return ptr;
}

void Resources::ClearMusics() {
    for (auto i = musicTable.begin(); i != musicTable.end();) {
        if (i->second.unique()) {
            musicTable.erase(i++);
        } else {
            i++;
        }
    }
    musicTable.clear();
}

shared_ptr<Mix_Chunk> Resources::GetSound(const string& file) {
    auto it = soundTable.find(file);
    if (it != soundTable.end()) {
        return it->second;
    }

    Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
    if (!chunk) {
        cerr << "Resources: Failed to load WAV!\nError: " << Mix_GetError() << endl;
        return nullptr;
    }

    shared_ptr<Mix_Chunk> ptr(chunk, [] (Mix_Chunk* ptr) { Mix_FreeChunk(ptr); });
    soundTable[file] = ptr;
    return ptr;
}

void Resources::ClearSounds() {
    for (auto i = soundTable.begin(); i != soundTable.end();) {
        if (i->second.unique()) {
            soundTable.erase(i++);
        } else {
            i++;
        }
    }
    soundTable.clear();
}


shared_ptr<TTF_Font> Resources::GetFont(const string& file, int size) {
    auto it = fontTable.find(file + ":" + to_string(size));
    if (it != fontTable.end()) {
        return it->second;
    }

    TTF_Font* font = TTF_OpenFont(file.c_str(), size);
    if (!font) {
        cerr << "Resources: Failed to load font!\nError: " << Mix_GetError() << endl;
        return nullptr;
    }

    shared_ptr<TTF_Font> ptr(font, [] (TTF_Font* ptr) { TTF_CloseFont(ptr); });
    fontTable[file] = ptr;
    return ptr;
}

void Resources::ClearFonts() {
    for (auto i = fontTable.begin(); i != fontTable.end();) {
        if (i->second.unique()) {
            fontTable.erase(i++);
        } else {
            i++;
        }
    }
    fontTable.clear();
}
