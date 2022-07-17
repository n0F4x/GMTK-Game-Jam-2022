#pragma once

#include <functional>
#include <utility>
#include "engine/drawables/Sprite.hpp"
#include "states/TileType.hpp"
#include "Tile.hpp"
#include "CharacterType.hpp"

class BoardGameManager;

class Character : public engine::Sprite {
public:
    static const int MAX_HAPPINESS;

    Character(CharacterType type, int happinessLoss,
              const int favoriteNumber, int favoriteNumberHappinessChange,
              int hatedNumber, int hatedNumberHappinessChange,
              TileType favoriteTile, int favoriteTileHappinessChange,
              TileType hatedTile, int hatedTileHappinessChange,
              std::string specialDescription,
              std::function<int(Character& character, BoardGameManager& boardGameMgr, int oldPositions[], int newPositions[])> specialCallback =
                      std::function<int(Character& character, BoardGameManager& boardGameMgr, int oldPositions[], int newPositions[])>(),
              std::function<void(Character&)> loseCallback = std::function<void(Character&)>());

    CharacterType getType() {
        return _type;
    }

    /**
     * @brief set happiness of character between 0 and MAX_HAPPINESS
     */
    void setHappiness(const int amount);

    /**
     * @brief Add to the happiness of the character between 0 and MAX_HAPPINESS
     */
    void addHappiness(const int amount);

    /**
     * @brief get happiness of character between 0 and MAX_HAPPINESS
     */
    int getHappiness() const;

    /**
     * @brief get happiness of character between 0.f and 1.f
     */
    float getHappinessNormed() const;

    /**
     * @brief calculate happiness after turn
     */
    void calculateHappinessAfterTurn(int diceNumber, TileType tile, CharacterType activeCharacter,
                                     BoardGameManager &boardGameMgr, int oldPositions[], int newPositions[]);

    void setCurrentTile(Tile* tile);

    Tile* getCurrentTile();

    void move(int offset);

    void setSpecialCallback(std::function<int(Character& character, BoardGameManager& boardGameMgr, int oldPositions[], int newPositions[])> callback);
    void setLoseCallback(std::function<void(Character& character)> callback);

    std::string getSpecialDescription();

private:
    CharacterType _type;

    int _happiness = MAX_HAPPINESS;
    int _happinessLoss;

    int _favoriteNumber;
    int _favoriteNumberHappinessChange;

    int _hatedNumber;
    int _hatedNumberHappinessChange;

    TileType _favoriteTile;
    int _favoriteTileHappinessChange;

    TileType _hatedTile;
    int _hatedTileHappinessChange;

    std::string _specialDescription;

    std::function<int(Character& character, BoardGameManager& boardGameMgr, int oldPositions[], int newPositions[])> _specialCallback;
    std::function<void(Character&)> _loseCallback;

    Tile* _currentTile = nullptr;
};