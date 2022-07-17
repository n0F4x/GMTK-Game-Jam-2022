#pragma once
#include <memory>
#include "TileType.hpp"
#include "TileDirection.hpp"
#include "engine/drawables/Sprite.hpp"
#include "engine/Assets.hpp"

using namespace engine;

class TileManager;

class Tile : public Sprite {
public:
    Tile(TileType type);

    Tile* getRelativeTile(int offset = 1);

    TileType getType();

    TileDirection getDirFromPrev();

    TileDirection getDirToNext();

    int getTileIndex() const;
private:
    friend TileManager;

    TileType _type;
    TileDirection _dirFromPrev = NONE, _dirToNext = NONE;
    std::unique_ptr<Tile> _next = nullptr;
    Tile* _prev = nullptr;
    int _tileIndex = 0;
};