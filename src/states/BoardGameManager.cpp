#include "states/BoardGameManager.hpp"

BoardGameManager::BoardGameManager(CharacterType startingCharacter,
                                   const std::function<void(Character & )> &gameOverCallback) :
        _gameOverCallback(gameOverCallback) {
    setPosition(Window::getSize().x / 2.f - (21 * 11 + 1) / 2.f * 3.f - 12, Window::getSize().y / 2.f - (21 * 7 + 1) / 2.f * 3.f - 12);

    _tilesBg.setTexture(&engine::Assets::getTexture("Tiles/board_background"));
    _tilesBg.setPosition(getPosition());
    _tilesBg.setScale(3, 3);
    attach_child(&_tilesBg);

    _tileMgr.addTile(TileType::NORMAL, RIGHT);
    _tileMgr.addTile(TileType::NORMAL, RIGHT);
    _tileMgr.addTile(TileType::SWAP_PLACES, RIGHT);
    _tileMgr.addTile(TileType::NORMAL, RIGHT);
    _tileMgr.addTile(TileType::REPEAT_MOVE, RIGHT);
    _tileMgr.addTile(TileType::NORMAL, RIGHT);
    _tileMgr.addTile(TileType::PLUS_3, RIGHT);
    _tileMgr.addTile(TileType::MINUS_5, RIGHT);
    _tileMgr.addTile(TileType::NORMAL, RIGHT);
    _tileMgr.addTile(TileType::REPEAT_MOVE, RIGHT);
    _tileMgr.addTile(TileType::NORMAL, DOWN);
    _tileMgr.addTile(TileType::NORMAL, DOWN);
    _tileMgr.addTile(TileType::MINUS_5, DOWN);
    _tileMgr.addTile(TileType::NORMAL, DOWN);
    _tileMgr.addTile(TileType::REPEAT_MOVE, DOWN);
    _tileMgr.addTile(TileType::NORMAL, DOWN);
    _tileMgr.addTile(TileType::NORMAL, LEFT);
    _tileMgr.addTile(TileType::MINUS_5, LEFT);
    _tileMgr.addTile(TileType::NORMAL, LEFT);
    _tileMgr.addTile(TileType::REPEAT_MOVE, LEFT);
    _tileMgr.addTile(TileType::NORMAL, LEFT);
    _tileMgr.addTile(TileType::NORMAL, UP);
    _tileMgr.addTile(TileType::NORMAL, UP);
    _tileMgr.addTile(TileType::NORMAL, LEFT);
    _tileMgr.addTile(TileType::REPEAT_MOVE, LEFT);
    _tileMgr.addTile(TileType::NORMAL, LEFT);
    _tileMgr.addTile(TileType::NORMAL, DOWN);
    _tileMgr.addTile(TileType::NORMAL, DOWN);
    _tileMgr.addTile(TileType::NORMAL, LEFT);
    _tileMgr.addTile(TileType::PLUS_3, LEFT);
    _tileMgr.addTile(TileType::NORMAL, UP);
    _tileMgr.addTile(TileType::NORMAL, UP);
    _tileMgr.addTile(TileType::PLUS_3, UP);
    _tileMgr.addTile(TileType::NORMAL, UP);
    _tileMgr.addTile(TileType::FINISH, UP);



    _tileMgr.setPosition(Window::getSize().x / 2.f - (21 * 11 + 1) / 2.f * 3.f, Window::getSize().y / 2.f - (21 * 7 + 1) / 2.f * 3.f);
    _tileMgr.setScale(3.f);
    attach_child(&_tileMgr);

    _characters[0] = std::make_unique<Character>(
            BOY,
            6,
            6, 3, 1, -5,
            PLUS_3, 5, SWAP_PLACES, -7, 10
    );
    _characters[1] = std::make_unique<Character>(
            GIRL,
            3,
            3, 3, 5, -5,
            REPEAT_MOVE, 5, PLUS_3, -7, 10
    );
    _characters[2] = std::make_unique<Character>(
            GRANDPA,
            3,
            1, 3, 4, -5,
            SWAP_PLACES, 5, MINUS_5, -7, 10
    );
    _characters[3] = std::make_unique<Character>(
            DOGE,
            3,
            4, 3, 2, -5,
            MINUS_5, 5, REPEAT_MOVE, -7, 10
    );

    for (int i = 0; i < 4; ++i) {
        _characters[i]->setScale(3.f);
        _characters[i]->setPosition(_tileMgr.getFirstTile()->getPosition());
        _characters[i]->setCurrentTile(_tileMgr.getFirstTile());
        attach_child(_characters[i].get());

        auto anim = _characters[i]->setComponent(std::make_unique<Animator>())->addAnimation("anim", std::make_unique<animations::Ease>());
        anim->setTime(sf::seconds(0.25f));
    }

    _activeCharacter = _characters[startingCharacter].get();
}

Character &BoardGameManager::getCharacter(CharacterType c) {
    return *_characters[c];
}

Character &BoardGameManager::getActiveCharacter() {
    return *_activeCharacter;
}

bool BoardGameManager::isBoardOccupied() const {
    return _boardOccupied;
}

void BoardGameManager::diceRoll(int moveOffset) {
    if (_boardOccupied) return;
    _boardOccupied = true;
    recursionLevel = 0;
    calculateNewMove(_activeCharacter->getType(), moveOffset);
}

void BoardGameManager::updateBoard() {
    if (stepFinishedInTurn) {
        if (clock.getElapsedTime() >= sf::seconds(0.5f)) {
            stepFinishedInTurn = false;
        } else {
            return;
        }
    }

    for (int i = 0; i < 4; ++i) {
        auto anim = _characters[i]->getComponent<Animator>()->findAnimation("anim");
        if (moveOffsetsRemaining[i] != 0 && !anim->isActive()) {
            if (moveOffsetsRemaining[i] > 0) {
                if (_characters[i]->getCurrentTile()->getRelativeTile(1) == nullptr) {
                    moveOffsetsRemaining[i] = 0;
                } else {
                    switch (_activeCharacter->getCurrentTile()->getDirToNext()) {
                        case LEFT:
                            anim->setDistance({-63, 0});
                            break;
                        case RIGHT:
                            anim->setDistance({63, 0});
                            break;
                        case UP:
                            anim->setDistance({0, -63});
                            break;
                        case DOWN:
                            anim->setDistance({0, 63});
                            break;
                        case NONE:
                            break;
                    }
                    _characters[i]->setCurrentTile(_characters[i]->getCurrentTile()->getRelativeTile(1));
                    moveOffsetsRemaining[i]--;
                    anim->start();
                }
            } else {
                if (_characters[i]->getCurrentTile()->getRelativeTile(-1) == nullptr) {
                    moveOffsetsRemaining[i] = 0;
                } else {
                    switch (_activeCharacter->getCurrentTile()->getDirFromPrev()) {
                        case LEFT:
                            anim->setDistance({63, 0});
                            break;
                        case RIGHT:
                            anim->setDistance({-63, 0});
                            break;
                        case UP:
                            anim->setDistance({0, 63});
                            break;
                        case DOWN:
                            anim->setDistance({0, -63});
                            break;
                        case NONE:
                            break;
                    }
                    _characters[i]->setCurrentTile(_characters[i]->getCurrentTile()->getRelativeTile(-1));
                    moveOffsetsRemaining[i]++;
                    anim->start();
                }
            }
        }
    }

    bool done = true;
    for (int i = 0; i < 4; ++i) {
        auto anim = _characters[i]->getComponent<Animator>()->findAnimation("anim");
        if (anim->isActive()) {
            done = false;
            break;
        }
    }

    if (done) {
        if (_boardOccupied && calculateTilesAndHappiness()) {
            // done with the entire turn of the active character
            _boardOccupied = false;
        }
    }
}

void BoardGameManager::setGameOverCallback(std::function<void(Character &)> callback) {
    _gameOverCallback = std::move(callback);
}

void BoardGameManager::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(_tilesBg);
    target.draw(_tileMgr);
    for (auto &c : _characters) {
        sf::RenderStates statesCopy = states;
        statesCopy.transform *= c->getTransform();
        target.draw(*c);
    }
}

void BoardGameManager::calculateNewMove(CharacterType c, int moveOffset) {
    int canMove = 0;
    if (moveOffset > 0) {
        while (true) {
            if (_characters[c]->getCurrentTile()->getRelativeTile(canMove + 1) != nullptr) {
                canMove++;
            } else {
                break;
            }
        }
        moveOffsetsRemaining[c] = std::min(canMove, moveOffset);
    } else {
        while (true) {
            if (_characters[c]->getCurrentTile()->getRelativeTile(canMove - 1) != nullptr) {
                canMove--;
            } else {
                break;
            }
        }
        moveOffsetsRemaining[c] = std::max(canMove, moveOffset);
    }

    if (_activeCharacter->getType() == c) {
        activeCharMoveOffset = moveOffsetsRemaining[c];
        recursionLevel++;

        int oldPosTemp[4] = { _characters[0]->getCurrentTile()->getTileIndex(), _characters[1]->getCurrentTile()->getTileIndex(),
                              _characters[2]->getCurrentTile()->getTileIndex(), _characters[3]->getCurrentTile()->getTileIndex()};
        std::copy(std::begin(oldPosTemp), std::end(oldPosTemp), std::begin(oldPos));

        std::copy(std::begin(oldPosTemp), std::end(oldPosTemp), std::begin(newPos));
        newPos[_activeCharacter->getType()] += activeCharMoveOffset;
    }
}

bool BoardGameManager::calculateTilesAndHappiness() {
    // calculate happiness
    for (int i = 0; i < 4; ++i) {
        _characters[i]->calculateHappinessAfterTurn(recursionLevel > 0 ? 0 : activeCharMoveOffset, _activeCharacter->getCurrentTile()->getType(),
                                                    _activeCharacter->getType(), *this, oldPos, newPos);
        printf("%d\n", _characters[i]->getHappiness());
    }

    // process tile type and move character if it is current character
    if (recursionLevel > 35) {
        // TODO finish move if character has visited a tile again that it has already visited in their current turn
        nextCharacter();
        return true;
    }

    switch (_activeCharacter->getCurrentTile()->getType()) {
        case PLUS_3:
            calculateNewMove(_activeCharacter->getType(), 3);
            break;
        case MINUS_5:
            calculateNewMove(_activeCharacter->getType(), -5);
            break;
        case SWAP_PLACES:
            int sortedNewPos[4];
            std::copy(std::begin(newPos), std::end(newPos), std::begin(sortedNewPos));
            std::sort(std::begin(sortedNewPos), std::end(sortedNewPos), std::greater<>());

            for (int i = 0; i < 4; ++i) {
                if (sortedNewPos[i] < newPos[_activeCharacter->getType()]) {
                    for (int j = 0; j < 4; ++j) {
                        if (_characters[j]->getCurrentTile()->getTileIndex() == sortedNewPos[i]) {
                            calculateNewMove(_characters[j]->getType(), newPos[_activeCharacter->getType()] - sortedNewPos[i]);
                        }
                    }
                    calculateNewMove(_activeCharacter->getType(), sortedNewPos[i] - newPos[_activeCharacter->getType()]);
                    break;
                }
            }
            break;
        case REPEAT_MOVE:
            calculateNewMove(_activeCharacter->getType(), activeCharMoveOffset);
            break;
        case FINISH:
            _gameOverCallback(*_activeCharacter);
            return true;
        default:
            nextCharacter();
            return true;
    }

    clock.restart();
    stepFinishedInTurn = true;
    return false;
}

void BoardGameManager::nextCharacter() {
    if (_activeCharacter->getType() == DOGE) {
        _activeCharacter = _characters[0].get();
    } else {
        _activeCharacter = _characters[_activeCharacter->getType() + 1].get();
    }
}
