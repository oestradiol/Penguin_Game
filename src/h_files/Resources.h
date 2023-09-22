#pragma once

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <unordered_map>
#include <string>

class Resources {
public:
    static SDL_Texture* GetImage(const std::string& file);
    static void ClearImages();

    static Mix_Music* GetMusic(const std::string& file);
    static void ClearMusics();

    static Mix_Chunk* GetSound(const std::string& file);
    static void ClearSounds();

private:
    static std::unordered_map<std::string, SDL_Texture*> imageTable;
    static std::unordered_map<std::string, Mix_Music*> musicTable;
    static std::unordered_map<std::string, Mix_Chunk*> soundTable;
};