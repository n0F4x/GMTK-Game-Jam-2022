#pragma once

#include <functional>
#include <utility>
#include "engine/drawables/Sprite.hpp"
#include "states/TileType.hpp"
#include "Tile.hpp"

class Character : public engine::Sprite {
public:
    static const int MAX_HAPPINESS;

    Character( const sf::Texture* texture, int happinessLoss,
               const int favoriteNumber, int favoriteNumberHappinessChange,
               int hatedNumber, int hatedNumberHappinessChange,
               TileType favoriteTile, int favoriteTileHappinessChange,
               TileType hatedTile, int hatedTileHappinessChange,
               std::string specialDescription,
               std::function<int()> specialCallback = std::function<int()>(),
               std::function<void()> loseCallback = std::function<void()>());

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
    void calculateHappinessAfterTurn(Character* activeCharacter, int diceNumber, TileType tile);

    void setCurrentTile(Tile* tile);

    Tile* getCurrentTile();

    void move(int offset);

    void setSpecialCallback(const std::function<int()> callback);
    void setLoseCallback(const std::function<void()> callback);

    std::string getSpecialDescription();

private:
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

    std::function<int()> _specialCallback;
    std::function<void()> _loseCallback;

    Tile* _currentTile = nullptr;
};