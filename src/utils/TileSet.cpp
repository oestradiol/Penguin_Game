#include <iostream>
#include <stdexcept>
using namespace std;

#include "headers/TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, const string& file)
    : tileSetGO(), tileSet(new Sprite(tileSetGO, file)), tileWidth(tileWidth), tileHeight(tileHeight) {
    if (!tileSet->IsOpen()) {
        cerr << "TileSet: Failed to open Sprite." << endl;
        return;
    }
    
    columns = tileSet->GetWidth() / tileWidth;
    rows = tileSet->GetHeight() / tileHeight;
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    if (index >= static_cast<unsigned>(columns * rows)) {
        if (index != (unsigned) -1) {
             cerr << "TileSet: Warning: Invalid tile index." << endl;
        }
        return;
    }

    int clipX = (index % columns) * tileWidth;
    int clipY = (index / columns) * tileHeight;

    tileSet->SetClip(clipX, clipY, tileWidth, tileHeight);
    tileSet->Render(x, y, Vec2(tileWidth, tileHeight));
}