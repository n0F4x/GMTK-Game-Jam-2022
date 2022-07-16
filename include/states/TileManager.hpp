#pragma once

#include <memory>
#include "engine/drawables/Sprite.hpp"
#include "states/TileType.hpp"

using namespace engine;

class TileManager : public Sprite {
public:
    TileManager() {
        attach_child(_firstTile.get());
        _firstTile->setPosition(getPosition());
        _lastTile = _firstTile.get();
    }

    void addTile(TileType type, TileDirection dir) {
        _lastTile->_next = std::make_unique<Tile>(type);
        _lastTile->_dirToNext = dir;
        _lastTile->_next->_dirFromPrev = dir;
        _lastTile->_next->_tileIndex = _lastTile->_tileIndex + 1;

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

    Tile* getFirstTile() {
        return _firstTile.get();
    }

    Tile* getLastTile() {
        return _lastTile;
    }

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        Sprite::draw(target, states);
        for (size_t i = 0; i < getChildrenCount(); ++i) {
            target.draw(*dynamic_cast<Sprite*>(getChild(i)), states);
        }
    }

private:
    std::unique_ptr<Tile> _firstTile = std::make_unique<Tile>(START);
    Tile* _lastTile = nullptr;
};