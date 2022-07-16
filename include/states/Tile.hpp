#pragma once
#include <memory>
#include "TileType.hpp"
#include "TileDirection.hpp"
#include "engine/drawables/Sprite.hpp"
#include "engine/Assets.hpp"

using namespace engine;

class TileManager;

class Tile : private Sprite {
public:
    Tile(TileType type) {
        this->type = type;
        Sprite::setTexture(&Assets::getTexture(tileTypeToString(type)));
    }

    Tile* prevTile() {
        return prev;
    }

    std::unique_ptr<Tile>& nextTile() {
        return next;
    }

    TileType getType() {
        return type;
    }

    TileDirection getDirFromPrev() {
        return dirFromPrev;
    }

    TileDirection getDirToNext() {
        return dirToNext;
    }
private:
    friend TileManager;

    TileType type;
    TileDirection dirFromPrev = NONE, dirToNext = NONE;
    std::unique_ptr<Tile> next = nullptr;
    Tile* prev = nullptr;
};