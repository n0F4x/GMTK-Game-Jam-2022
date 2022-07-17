#include "states/TileManager.hpp"

TileManager::TileManager() {
    attach_child(_firstTile.get());
    _firstTile->setPosition(getPosition());
    _lastTile = _firstTile.get();
}

void TileManager::addTile(TileType type, TileDirection dir) {
    _lastTile->_next = std::make_unique<Tile>(type);
    _lastTile->_dirToNext = dir;
    _lastTile->_next->_dirFromPrev = dir;
    _lastTile->_next->_tileIndex = _lastTile->_tileIndex + 1;
    _lastTile->_next->_prev = _lastTile;

    switch (dir) {
        case LEFT:
            _lastTile->_next->setPosition({_lastTile->getPosition().x - _lastTile->getSize().x + 1, _lastTile->getPosition().y});
            break;
        case RIGHT:
            _lastTile->_next->setPosition({_lastTile->getPosition().x + _lastTile->getSize().x - 1, _lastTile->getPosition().y});
            break;
        case UP:
            _lastTile->_next->setPosition({_lastTile->getPosition().x, _lastTile->getPosition().y - _lastTile->getSize().y + 1});
            break;
        case DOWN:
            _lastTile->_next->setPosition({_lastTile->getPosition().x, _lastTile->getPosition().y + _lastTile->getSize().y - 1});
            break;
        case NONE:
            break;
    }

    _lastTile = _lastTile->_next.get();
    attach_child(_lastTile);
}

Tile *TileManager::getFirstTile() {
    return _firstTile.get();
}

Tile *TileManager::getLastTile() {
    return _lastTile;
}

void TileManager::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    Sprite::draw(target, states);
    for (size_t i = 0; i < getChildrenCount(); ++i) {
        target.draw(*dynamic_cast<Sprite*>(getChild(i)), states);
    }
}
