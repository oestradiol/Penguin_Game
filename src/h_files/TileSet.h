#pragma once

#include "Sprite.h"
#include "GameObject.h"

class TileSet {
public:
    TileSet(int tileWidth, int tileHeight, const std::string& file);
    void RenderTile(unsigned index, float x, float y);
    int GetTileWidth() const;
    int GetTileHeight() const;

private:
    GameObject tileSetGO;
    Sprite tileSet;
    int rows;
    int columns;
    int tileWidth;
    int tileHeight;
};