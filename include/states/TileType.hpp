#pragma once

#include <string>
#include "engine/Assets.hpp"

enum TileType {
    START,
    FINISH,
    NORMAL,
    PLUS_3,
    MINUS_5,
    SWAP_PLACES,
    REPEAT_MOVE
};

static const std::string tileTypeTextures[] = {
        "Tiles/basic_tile",
        "Tiles/end_tile",
        "Tiles/basic_tile",
        "Tiles/plus_tile",
        "Tiles/minus_tile",
        "Tiles/swap_tile",
        "Tiles/repeat_move_tile"
};

inline sf::Texture& getTileTypeTexture(TileType type) {
    return engine::Assets::getTexture(tileTypeTextures[type]);
}
