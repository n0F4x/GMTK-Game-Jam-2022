#pragma once

#include <functional>
#include "states/Character.hpp"
#include "states/BoardGameManager.hpp"
#include "states/Tile.hpp"

extern const std::function<int(Character&, BoardGameManager&, int[], int[])> boyCallback;
extern const std::function<int(Character&, BoardGameManager&, int[], int[])> girlCallback;
extern const std::function<int(Character&, BoardGameManager&, int[], int[])> grandpaCallback;
extern const std::function<int(Character&, BoardGameManager&, int[], int[])> dogeCallback;