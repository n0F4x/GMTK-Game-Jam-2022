#include "states/Character.hpp"

const int Character::MAX_HAPPINESS = 100;

void Character::setHappiness(const int amount) {
    _happiness = amount;
    if (_happiness > MAX_HAPPINESS)
        _happiness = MAX_HAPPINESS;
    else if (_happiness < 0){
        _happiness = 0;
        _gameOverCallback();
    }
}

void Character::addHappiness(const int amount) {
    _happiness += amount;
    if (_happiness > MAX_HAPPINESS)
        _happiness = MAX_HAPPINESS;
    else if (_happiness < 0){
        _happiness = 0;
        _gameOverCallback();
    }
}

int Character::getHappiness() const {
    return _happiness;
}

float Character::getHappinessNormed() const {
    return (float)_happiness / (float)MAX_HAPPINESS;
}

void Character::calculateHappinessAfterOwnTurn(int diceNumber, TileType tile) {
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

void Character::calculateHappinessAfterOthersTurn() {
    addHappiness(-_happinessLoss);
}