#pragma once

#include <functional>
#include "states/Character.hpp"
#include "states/BoardGameManager.hpp"
#include "states/Tile.hpp"

extern const std::function<int(Character& character, BoardGameManager& boardGameMgr, int oldPositions[], int newPositions[])> boyCallback;
extern const std::function<int(Character& character, BoardGameManager& boardGameMgr, int oldPositions[], int newPositions[])> girlCallback;
extern const std::function<int(Character& character, BoardGameManager& boardGameMgr, int oldPositions[], int newPositions[])> grandpaCallback;
extern const std::function<int(Character& character, BoardGameManager& boardGameMgr, int oldPositions[], int newPositions[])> dogeCallback;