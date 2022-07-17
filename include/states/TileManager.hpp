#pragma once

#include <memory>
#include "engine/drawables/Sprite.hpp"
#include "TileType.hpp"
#include "TileDirection.hpp"
#include "Tile.hpp"

using namespace engine;

class TileManager : public Sprite {
public:
    TileManager();

    void addTile(TileType type, TileDirection dir);

    Tile* getFirstTile();

    Tile* getLastTile();

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::unique_ptr<Tile> _firstTile = std::make_unique<Tile>(START);
    Tile* _lastTile = nullptr;
};