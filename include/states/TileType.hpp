#pragma once

#include <string>

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
        "Tiles/changer_tile",
        "Tiles/doubler_tile"
};

inline std::string tileTypeToString(TileType type) {
    return tileTypeTextures[type];
}
