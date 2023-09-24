#pragma once

#include "../../core/headers/GameObject.h"
#include "../../components/headers/Sprite.h"

class TileSet {
public:
    TileSet(int tileWidth, int tileHeight, const std::string& file);
    void RenderTile(unsigned index, float x, float y);
    int GetTileWidth() const;
    int GetTileHeight() const;

private:
    GameObject tileSetGO;
    Sprite* tileSet;
    int rows;
    int columns;
    int tileWidth;
    int tileHeight;
};

inline int TileSet::GetTileWidth() const {
    return tileWidth;
}

inline int TileSet::GetTileHeight() const {
    return tileHeight;
}