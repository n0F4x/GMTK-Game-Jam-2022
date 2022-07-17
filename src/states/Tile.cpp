#include "states/Tile.hpp"

Tile::Tile(TileType type) {
    this->_type = type;
    Sprite::setTexture(&getTileTypeTexture(type));
}

Tile *Tile::getRelativeTile(int offset) {
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

TileType Tile::getType() {
    return _type;
}

TileDirection Tile::getDirFromPrev() {
    return _dirFromPrev;
}

TileDirection Tile::getDirToNext() {
    return _dirToNext;
}

int Tile::getTileIndex() const {
    return _tileIndex;
}
