#include "states/Character.hpp"

const int Character::MAX_HAPPINESS = 100;

void Character::setHappiness(const int amount) {
    _happiness = amount;
    if (_happiness > MAX_HAPPINESS)
        _happiness = MAX_HAPPINESS;
    else if (_happiness < 0)
        _happiness = 0;
}

void Character::addHappiness(const int amount) {
    _happiness += amount;
    if (_happiness > MAX_HAPPINESS)
        _happiness = MAX_HAPPINESS;
    else if (_happiness < 0)
        _happiness = 0;
}

int Character::getHappiness() const {
    return _happiness;
}

float Character::getHappinessNormed() const {
    return (float)_happiness / (float)MAX_HAPPINESS;
}