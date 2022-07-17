#include "states/Character.hpp"
#include "states/CharacterType.hpp"

#include <utility>

const int Character::MAX_HAPPINESS = 100;

Character::Character(CharacterType type, int happinessLoss,
                     const int favoriteNumber, int favoriteNumberHappinessChange,
                     int hatedNumber, int hatedNumberHappinessChange,
                     TileType favoriteTile, int favoriteTileHappinessChange,
                     TileType hatedTile, int hatedTileHappinessChange,
                     std::string specialDescription,
                     std::function<int(Character& character, BoardGameManager& boardGameMgr, int oldPositions[], int newPositions[])> specialCallback,
                     std::function<void(Character&)> loseCallback)
        : _type(type), _happinessLoss(happinessLoss),
          _favoriteNumber(favoriteNumber), _favoriteNumberHappinessChange(favoriteNumberHappinessChange),
          _hatedNumber(hatedNumber), _hatedNumberHappinessChange(hatedNumberHappinessChange),
          _favoriteTile(favoriteTile), _favoriteTileHappinessChange(favoriteTileHappinessChange),
          _hatedTile(hatedTile), _hatedTileHappinessChange(hatedTileHappinessChange),
          _specialDescription(std::move(specialDescription)),
          _specialCallback(std::move(specialCallback)), _loseCallback(std::move(loseCallback)) {

    engine::Sprite::setTexture(&getCharacterTexture(type));
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

void Character::calculateHappinessAfterTurn(int diceNumber, TileType tile, CharacterType activeCharacter,
                                            BoardGameManager &boardGameMgr, int oldPositions[], int newPositions[]) {
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

    if (_happiness <= 0) return;
    addHappiness(_specialCallback(*this, boardGameMgr, oldPositions, newPositions));
}

void Character::setCurrentTile(Tile *tile) {
    _currentTile = tile;
    setPosition(tile->getPosition());
}

Tile *Character::getCurrentTile() {
    return _currentTile;
}

void Character::move(int offset) {
    setCurrentTile(getCurrentTile()->getRelativeTile(offset));
}

void Character::setSpecialCallback(std::function<int(Character& character, BoardGameManager& boardGameMgr, int oldPositions[], int newPositions[])> callback) {
    _specialCallback = std::move(callback);
}

void Character::setLoseCallback(std::function<void(Character&)> callback) {
    _loseCallback = std::move(callback);
}

std::string Character::getSpecialDescription() {
    return _specialDescription;
}
