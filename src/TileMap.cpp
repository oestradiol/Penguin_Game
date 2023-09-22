#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

#include "h_files/TileMap.h"

TileMap::TileMap(GameObject& associated, const string& file, TileSet* tileSet)
    : Component(associated), tileSet(tileSet), mapWidth(0), mapHeight(0), mapDepth(0) {
    Load(file);
}

void TileMap::Load(const string& file) {
 
    ifstream mapFile(file);
    if (!mapFile.is_open()) {
        cerr << "TileMap: Could not open tile map file: " << file << "\n";
        exit(1);
    }

	string line, index;
    
    getline(mapFile, line);
    stringstream str(line);
    tileMatrix.resize(3);
    for (int i = 0; i < 3; i++) {
        getline(str, index, ',');
        tileMatrix[i] = stoi(index);
    }
    mapWidth = tileMatrix[0];
    mapHeight = tileMatrix[1];
    mapDepth = tileMatrix[2];

    int i = 0;
    tileMatrix.resize(mapWidth * mapHeight * mapDepth);
    while (getline(mapFile, line))
    {
        stringstream str(line);
        while (getline(str, index, ',')) {
            try {
                tileMatrix[i] = stoi(index) - 1;
            } catch (...) {
                continue;
            }
            i++;
        }
    }

    mapFile.close();
}

void TileMap::SetTileSet(TileSet* set) {
    tileSet = set;
}

int& TileMap::At(int x, int y, int z) {
    return tileMatrix[x + y * mapWidth + z * mapWidth * mapHeight];
}

void TileMap::Render() {
    int x = associated.box.x;
    int y = associated.box.y;
    for (int i = 0; i < mapDepth; ++i) {
        RenderLayer(i, x, y);
    }
}

void TileMap::Update(float dt) { }

bool TileMap::Is(const std::string &type) const
{
    return type == "TileMap";
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    if (tileSet == nullptr) {
        cerr << "TileMap: TileSet not defined.\n";
        return;
    }

    int tileWidth = tileSet->GetTileWidth();
    int tileHeight = tileSet->GetTileHeight();

    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            int index = At(x, y, layer);
            if (index >= 0) {
                int renderX = x * tileWidth - cameraX;
                int renderY = y * tileHeight - cameraY;
                tileSet->RenderTile(index, renderX, renderY);
            }
        }
    }
}

int TileMap::GetWidth() const {
    return mapWidth;
}

int TileMap::GetHeight() const {
    return mapHeight;
}

int TileMap::GetDepth() const {
    return mapDepth;
}
