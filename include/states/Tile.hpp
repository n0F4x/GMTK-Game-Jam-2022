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
    Tile(TileType type) {
        this->_type = type;
        Sprite::setTexture(&Assets::getTexture(tileTypeToString(type)));
    }

    std::unique_ptr<Tile>& nextTile() {
        return _next;
    }

    Tile* prevTile() {
        return _prev;
    }

    TileType getType() {
        return _type;
    }

    TileDirection getDirFromPrev() {
        return _dirFromPrev;
    }

    TileDirection getDirToNext() {
        return _dirToNext;
    }
private:
    friend TileManager;

    TileType _type;
    TileDirection _dirFromPrev = NONE, _dirToNext = NONE;
    std::unique_ptr<Tile> _next = nullptr;
    Tile* _prev = nullptr;
};