#pragma once

#include <memory>
#include "engine/drawables/Sprite.hpp"
#include "states/TileType.hpp"

using namespace engine;

class TileManager : Sprite {
public:
    TileManager() {
        attach_child(firstTile.get());
        firstTile->setPosition(getPosition());
    }

    void addTile(TileType type, TileDirection dir) {
        lastTile->next = std::make_unique<Tile>(type);
        lastTile->dirToNext = dir;
        lastTile->next->dirFromPrev = dir;

        switch (dir) {
            case LEFT:
                lastTile->next->setPosition({lastTile->getPosition().x - lastTile->getSize().x, lastTile->getPosition().y});
                break;
            case RIGHT:
                lastTile->next->setPosition({lastTile->getPosition().x + lastTile->getSize().x, lastTile->getPosition().y});
                break;
            case UP:
                lastTile->next->setPosition({lastTile->getPosition().x, lastTile->getPosition().y - lastTile->getSize().y});
                break;
            case DOWN:
                lastTile->next->setPosition({lastTile->getPosition().x, lastTile->getPosition().y + lastTile->getSize().y});
                break;
            case NONE:
                break;
        }

        lastTile = lastTile->next.get();
        attach_child(lastTile);
    }
private:
    std::unique_ptr<Tile> firstTile = std::make_unique<Tile>(START);
    Tile* lastTile = firstTile.get();
};