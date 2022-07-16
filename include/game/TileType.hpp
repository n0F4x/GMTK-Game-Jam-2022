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
        "start",
        "finish",
        "normal",
        "plus_3",
        "minus_5",
        "swap_places",
        "repeat_move"
};

inline std::string tileTypeToString(TileType type) {
    return tileTypeTextures[type];
}
