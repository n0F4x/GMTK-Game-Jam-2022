#pragma once

#include <functional>
#include <utility>
#include "engine/drawables/Sprite.hpp"
#include "states/TileType.hpp"

class Character : public engine::Sprite {
public:
    static const int MAX_HAPPINESS;

    Character( const sf::Texture* texture,
               const int favoriteNumber, int favoriteNumberHappinessChange,
               int hatedNumber, int hatedNumberHappinessChange,
               TileType favoriteTile, int favoriteTileHappinessChange,
               TileType hatedTile, int hatedTileHappinessChange,
               std::function<int()> specialCallback, std::function<void()> gameOverCallback)
                : Sprite(texture),
                _favoriteNumber(favoriteNumber), _favoriteNumberHappinessChange(favoriteNumberHappinessChange),
                _hatedNumber(hatedNumber), _hatedNumberHappinessChange(hatedNumberHappinessChange),
                _favoriteTile(favoriteTile), _favoriteTileHappinessChange(favoriteTileHappinessChange),
                _hatedTile(hatedTile), _hatedTileHappinessChange(hatedTileHappinessChange),
                _specialCallback(std::move(specialCallback)), _gameOverCallback(std::move(gameOverCallback)) {}

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



private:
    int _happiness = MAX_HAPPINESS;

    int _favoriteNumber;
    int _favoriteNumberHappinessChange;

    int _hatedNumber;
    int _hatedNumberHappinessChange;

    TileType _favoriteTile;
    int _favoriteTileHappinessChange;

    TileType _hatedTile;
    int _hatedTileHappinessChange;

    std::function<int()> _specialCallback;
    std::function<void()> _gameOverCallback;
};