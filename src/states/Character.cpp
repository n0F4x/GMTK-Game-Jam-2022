#include "states/Character.hpp"
#include "states/CharacterType.hpp"
#include "states//CharacterCallbacks.hpp"

#include <utility>

const int Character::MAX_HAPPINESS = 100;

Character::Character(CharacterType type, int happinessLoss,
                     int favoriteNumber, int favoriteNumberHappinessChange,
                     int hatedNumber, int hatedNumberHappinessChange,
                     TileType favoriteTile, int favoriteTileHappinessChange,
                     TileType hatedTile, int hatedTileHappinessChange,
                     int specialCallbackHappinessChange,
                     std::function<void(Character&)> loseCallback)
        : _type(type), _happinessLoss(happinessLoss),
          _favoriteNumber(favoriteNumber), _favoriteNumberHappinessChange(favoriteNumberHappinessChange),
          _hatedNumber(hatedNumber), _hatedNumberHappinessChange(hatedNumberHappinessChange),
          _favoriteTile(favoriteTile), _favoriteTileHappinessChange(favoriteTileHappinessChange),
          _hatedTile(hatedTile), _hatedTileHappinessChange(hatedTileHappinessChange),
          _specialCallbackHappinessChange(specialCallbackHappinessChange),
          _loseCallback(std::move(loseCallback)) {

    engine::Sprite::setTexture(&getCharacterTexture(type));
    switch (_type) {
        case BOY:
            _specialCallback = boyCallback;
            break;
        case GIRL:
            _specialCallback = girlCallback;
            break;
        case GRANDPA:
            _specialCallback = grandpaCallback;
            break;
        case DOGE:
            _specialCallback = dogeCallback;
            break;
    }
}

void Character::setHappiness(const int amount) {
    _happiness = amount;
    if (_happiness > MAX_HAPPINESS)
        _happiness = MAX_HAPPINESS;
    else if (_happiness <= 0){
        _happiness = 0;
        _loseCallback(*this);
    }
}

void Character::addHappiness(const int amount) {
    _happiness += amount;
    if (_happiness > MAX_HAPPINESS)
        _happiness = MAX_HAPPINESS;
    else if (_happiness <= 0){
        _happiness = 0;
        _loseCallback(*this);
    }
}

int Character::getHappiness() const {
    return _happiness;
}

float Character::getHappinessNormed() const {
    return (float)_happiness / (float)MAX_HAPPINESS;
}

int Character::getHappinessChange() const {
    return _happinessChangeSinceLastTurn;
}

void Character::calculateHappinessAfterTurn(int diceNumber, TileType tile, CharacterType activeCharacter,
                                            BoardGameManager &boardGameMgr, int oldPositions[], int newPositions[]) {
    int oldHappiness = _happiness;
    if (this->_type == activeCharacter) {
        if (diceNumber == _favoriteNumber)
            addHappiness(_favoriteNumberHappinessChange);
        else if (diceNumber == _hatedNumber)
            addHappiness(_hatedNumberHappinessChange);
        if (tile == _favoriteTile)
            addHappiness(_favoriteTileHappinessChange);
        else if (tile == _hatedTile)
            addHappiness(_hatedTileHappinessChange);
    }
    else {
        addHappiness(-_happinessLoss);
    }
    _happinessChangeSinceLastTurn = _happiness - oldHappiness;
    if (_happiness <= 0) return;
    addHappiness(_specialCallbackHappinessChange * _specialCallback(*this, boardGameMgr, oldPositions, newPositions));
}

void Character::setCurrentTile(Tile *tile) {
    _currentTile = tile;
}

Tile *Character::getCurrentTile() {
    return _currentTile;
}

void Character::move(int offset) {
    setCurrentTile(getCurrentTile()->getRelativeTile(offset));
}

void Character::setLoseCallback(std::function<void(Character&)> callback) {
    _loseCallback = std::move(callback);
}
