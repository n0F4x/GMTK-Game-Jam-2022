#include "states/Character.hpp"

#include <utility>

const int Character::MAX_HAPPINESS = 100;

Character::Character(  const sf::Texture* texture, int happinessLoss,
                       const int favoriteNumber, int favoriteNumberHappinessChange,
                       int hatedNumber, int hatedNumberHappinessChange,
                       TileType favoriteTile, int favoriteTileHappinessChange,
                       TileType hatedTile, int hatedTileHappinessChange,
                       std::string specialDescription,
                       std::function<int()> specialCallback, std::function<void()> loseCallback)
                    : Sprite(texture), _happinessLoss(happinessLoss),
                      _favoriteNumber(favoriteNumber), _favoriteNumberHappinessChange(favoriteNumberHappinessChange),
                      _hatedNumber(hatedNumber), _hatedNumberHappinessChange(hatedNumberHappinessChange),
                      _favoriteTile(favoriteTile), _favoriteTileHappinessChange(favoriteTileHappinessChange),
                      _hatedTile(hatedTile), _hatedTileHappinessChange(hatedTileHappinessChange),
                      _specialDescription(std::move(specialDescription)),
                      _specialCallback(std::move(specialCallback)), _loseCallback(std::move(loseCallback)) {}

void Character::setHappiness(const int amount) {
    _happiness = amount;
    if (_happiness > MAX_HAPPINESS)
        _happiness = MAX_HAPPINESS;
    else if (_happiness <= 0){
        _happiness = 0;
        _loseCallback();
    }
}

void Character::addHappiness(const int amount) {
    _happiness += amount;
    if (_happiness > MAX_HAPPINESS)
        _happiness = MAX_HAPPINESS;
    else if (_happiness <= 0){
        _happiness = 0;
        _loseCallback();
    }
}

int Character::getHappiness() const {
    return _happiness;
}

float Character::getHappinessNormed() const {
    return (float)_happiness / (float)MAX_HAPPINESS;
}

void Character::calculateHappinessAfterTurn(Character *activeCharacter, int diceNumber, TileType tile) {
    if (activeCharacter == this) {
        if (diceNumber == _favoriteNumber)
            addHappiness(_favoriteNumberHappinessChange);
        else if (diceNumber == _hatedNumber)
            addHappiness(_hatedNumberHappinessChange);
        if (tile == _favoriteTile)
            addHappiness(_favoriteTileHappinessChange);
        else if (tile == _hatedTile)
            addHappiness(_hatedTileHappinessChange);

        addHappiness(_specialCallback());
    }
    else {
        addHappiness(-_happinessLoss);
    }
}

void Character::setCurrentTile(Tile *tile) {
    _currentTile = tile;
}

Tile *Character::getCurrentTile() {
    return _currentTile;
}

void Character::setSpecialCallback(const std::function<int()> callback) {
    _specialCallback = callback;
}

void Character::setLoseCallback(const std::function<void()> callback) {
    _loseCallback = callback;
}

std::string Character::getSpecialDescription() {
    return _specialDescription;
}