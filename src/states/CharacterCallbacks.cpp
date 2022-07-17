#include "states/CharacterCallbacks.hpp"

extern const std::function<int(Character& character, BoardGameManager& boardGameMgr, int oldPositions[], int newPositions[])> boyCallback = [](Character& character, BoardGameManager& boardGameMgr, int oldPositions[], int newPositions[]) -> int {
    int playersBehindBoyOldPos = 0, playersBehindBoyNewPos = 0;
    for (int i = 0; i < 4; ++i) {
        if (oldPositions[i] < character.getCurrentTile()->getTileIndex())
            playersBehindBoyOldPos++;
        if (newPositions[i] < character.getCurrentTile()->getTileIndex())
            playersBehindBoyNewPos++;
    }
    if (playersBehindBoyOldPos > playersBehindBoyNewPos)
        return 0;
    return playersBehindBoyNewPos - playersBehindBoyOldPos;
};

extern const std::function<int(Character& character, BoardGameManager& boardGameMgr, int oldPositions[], int newPositions[])> girlCallback = [](Character& character, BoardGameManager& boardGameMgr, int oldPositions[], int newPositions[]) -> int {
    std::pair<int, int> oldPair[4], newPair[4];
    for (int i = 0; i < 4; ++i) {
        oldPair[i].first = oldPositions[i];
        oldPair[i].second = i;
        newPair[i].first = newPositions[i];
        newPair[i].second = i;
    }
    std::sort(oldPair, oldPair + 4);
    std::sort(newPair, newPair + 4);
    for (int i = 0; i < 4; ++i)
        if (oldPair[i].second != newPair[i].second)
            return 0;
    return 1;
};

extern const std::function<int(Character& character, BoardGameManager& boardGameMgr, int oldPositions[], int newPositions[])> grandpaCallback = [](Character& character, BoardGameManager& boardGameMgr, int oldPositions[], int newPositions[]) -> int {
    if (character.getType() == boardGameMgr.getActiveCharacter().getType())
        if (character.getCurrentTile()->getDirFromPrev() == character.getCurrentTile()->getDirToNext())
            return 1;
    return 0;
};

extern const std::function<int(Character& character, BoardGameManager& boardGameMgr, int oldPositions[], int newPositions[])> dogeCallback = [](Character& character, BoardGameManager& boardGameMgr, int oldPositions[], int newPositions[]) -> int {
    int numberOfPlayersOnTileOfDoge = 0;
    for (int i = 0; i < 4; i++)
        if (character.getCurrentTile()->getTileIndex() == newPositions[i])
            numberOfPlayersOnTileOfDoge++;
    return numberOfPlayersOnTileOfDoge - 1;
};