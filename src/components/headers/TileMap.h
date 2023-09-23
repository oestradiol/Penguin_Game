#pragma once

#include "../../utils/headers/TileSet.h"

class TileMap : public Component {
public:
    TileMap(GameObject& associated, const std::string& file, TileSet* tileSet);

    void Load(const std::string& file);
    void SetTileSet(TileSet* tileSet);

    int& At(int x, int y, int z = 0);
    
    void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

    int GetWidth() const;
    int GetHeight() const;
    int GetDepth() const;

    void Render() override;
    void Update(float dt) override;
    bool Is(const std::string& type) const override;

private:
    std::vector<int> tileMatrix;
    TileSet* tileSet;
    
    int mapWidth;
    int mapHeight;
    int mapDepth;
};

inline void TileMap::SetTileSet(TileSet* set) {
    tileSet = set;
}

inline bool TileMap::Is(const std::string &type) const {
    return type == "TileMap";
}