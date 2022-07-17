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
        Sprite::setTexture(&getTileTypeTexture(type));
    }

    Tile* getRelativeTile(int offset = 1) {
        Tile* t = this;
        if (offset >= 0) {
            for (int i = 0; i < offset; ++i) {
                t = t->_next.get();
            }
        } else {
            for (int i = 0; i < -offset; ++i) {
                t = t->_prev;
            }
        }
        return t;
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

    int getTileIndex() const {
        return _tileIndex;
    }
private:
    friend TileManager;

    TileType _type;
    TileDirection _dirFromPrev = NONE, _dirToNext = NONE;
    std::unique_ptr<Tile> _next = nullptr;
    Tile* _prev = nullptr;
    int _tileIndex = 0;
};