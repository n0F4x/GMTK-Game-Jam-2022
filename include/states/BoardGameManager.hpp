#pragma once

#include <utility>

#include "TileManager.hpp"
#include "Character.hpp"
#include "CharacterType.hpp"
#include "engine/Window.hpp"

using namespace engine;

class BoardGameManager : public sf::Drawable {
public:
    BoardGameManager(CharacterType startingCharacter, const std::function<void(Character&)>& gameOverCallback = std::function<void(Character&)>()) {
        _tilesBg.setTexture(&engine::Assets::getTexture("Tiles/board_background"));
        _tilesBg.setPosition(Window::getSize().x / 2.f - (21 * 11 + 1) / 2.f * 3.f - 12, Window::getSize().y / 2.f - (21 * 7 + 1) / 2.f * 3.f - 12);
        _tilesBg.setScale(3, 3);

        _tileMgr.addTile(TileType::NORMAL, RIGHT);
        _tileMgr.addTile(TileType::NORMAL, RIGHT);
        _tileMgr.addTile(TileType::NORMAL, RIGHT);
        _tileMgr.addTile(TileType::NORMAL, RIGHT);
        _tileMgr.addTile(TileType::PLUS_3, RIGHT);
        _tileMgr.addTile(TileType::NORMAL, RIGHT);
        _tileMgr.addTile(TileType::NORMAL, RIGHT);
        _tileMgr.addTile(TileType::SWAP_PLACES, RIGHT);
        _tileMgr.addTile(TileType::NORMAL, RIGHT);
        _tileMgr.addTile(TileType::NORMAL, RIGHT);
        _tileMgr.addTile(TileType::NORMAL, DOWN);
        _tileMgr.addTile(TileType::NORMAL, DOWN);
        _tileMgr.addTile(TileType::NORMAL, DOWN);
        _tileMgr.addTile(TileType::NORMAL, DOWN);
        _tileMgr.addTile(TileType::NORMAL, DOWN);
        _tileMgr.addTile(TileType::NORMAL, DOWN);
        _tileMgr.addTile(TileType::NORMAL, LEFT);
        _tileMgr.addTile(TileType::NORMAL, LEFT);
        _tileMgr.addTile(TileType::NORMAL, LEFT);
        _tileMgr.addTile(TileType::NORMAL, LEFT);
        _tileMgr.addTile(TileType::NORMAL, LEFT);
        _tileMgr.addTile(TileType::NORMAL, UP);
        _tileMgr.addTile(TileType::NORMAL, UP);
        _tileMgr.addTile(TileType::NORMAL, LEFT);
        _tileMgr.addTile(TileType::NORMAL, LEFT);
        _tileMgr.addTile(TileType::NORMAL, LEFT);
        _tileMgr.addTile(TileType::NORMAL, DOWN);
        _tileMgr.addTile(TileType::NORMAL, DOWN);
        _tileMgr.addTile(TileType::NORMAL, LEFT);
        _tileMgr.addTile(TileType::NORMAL, LEFT);
        _tileMgr.addTile(TileType::NORMAL, UP);
        _tileMgr.addTile(TileType::NORMAL, UP);
        _tileMgr.addTile(TileType::NORMAL, UP);
        _tileMgr.addTile(TileType::NORMAL, UP);
        _tileMgr.addTile(TileType::FINISH, UP);
        _tileMgr.setPosition(Window::getSize().x / 2.f - (21 * 11 + 1) / 2.f * 3.f, Window::getSize().y / 2.f - (21 * 7 + 1) / 2.f * 3.f);
        _tileMgr.setScale(3.f);

        _characters[0] = std::make_unique<Character>(
                BOY,
                5,
                1, 5, 2, -5,
                REPEAT_MOVE, 5, NORMAL, -5, 5
        );
        _characters[1] = std::make_unique<Character>(
                GIRL,
                5,
                1, 5, 2, -5,
                REPEAT_MOVE, 5, NORMAL, -5, 5
        );
        _characters[2] = std::make_unique<Character>(
                GRANDPA,
                5,
                1, 5, 2, -5,
                REPEAT_MOVE, 5, NORMAL, -5, 5
        );
        _characters[3] = std::make_unique<Character>(
                DOGE,
                5,
                1, 5, 2, -5,
                REPEAT_MOVE, 5, NORMAL, -5, 5
        );

        _characters[0]->setScale(3.f);
        _characters[1]->setScale(3.f);
        _characters[2]->setScale(3.f);
        _characters[3]->setScale(3.f);

        _characters[0]->setCurrentTile(_tileMgr.getFirstTile());
        _characters[1]->setCurrentTile(_tileMgr.getFirstTile());
        _characters[2]->setCurrentTile(_tileMgr.getFirstTile());
        _characters[3]->setCurrentTile(_tileMgr.getFirstTile());

        _activeCharacter = _characters[startingCharacter].get();
    }

    Character& getCharacter(CharacterType c) {
        return *_characters[c];
    }

    Character& getActiveCharacter() {
        return *_activeCharacter;
    }

    void tick(int moveOffset, int recursionLevel = 0) {
        // move character
        int oldPos[4] = { _characters[0]->getCurrentTile()->getTileIndex(), _characters[1]->getCurrentTile()->getTileIndex(),
                          _characters[2]->getCurrentTile()->getTileIndex(), _characters[3]->getCurrentTile()->getTileIndex()};

        _activeCharacter->move(moveOffset);

        int newPos[4];
        std::copy(std::begin(oldPos), std::end(oldPos), std::begin(newPos));
        newPos[_activeCharacter->getType()] += moveOffset;

        // calculate happiness
        for (int i = 0; i < 4; ++i) {
            _characters[i]->calculateHappinessAfterTurn(recursionLevel > 0 ? 0 : moveOffset, _activeCharacter->getCurrentTile()->getType(),
                                                        _activeCharacter->getType(), *this, oldPos, newPos);
        }

        // process tile type and move character if it is current character
        if (recursionLevel > 20) {
            // TODO finish move if character has visited a tile again that it has already visited in their current turn
            nextCharacter();
            return;
        }

        switch (_activeCharacter->getCurrentTile()->getType()) {
            case PLUS_3:
                tick(3, recursionLevel + 1);
                break;
            case MINUS_5:
                tick(-5, recursionLevel + 1);
                break;
            case SWAP_PLACES:
                int sortedNewPos[4];
                std::copy(std::begin(newPos), std::end(newPos), std::begin(sortedNewPos));
                std::sort(std::begin(sortedNewPos), std::end(sortedNewPos), std::greater<>());

                for (int i = 0; i < 4; ++i) {
                    if (sortedNewPos[i] < newPos[_activeCharacter->getType()]) {
                        for (int j = 0; j < 4; ++j) {
                            if (_characters[j]->getCurrentTile()->getTileIndex() == sortedNewPos[i]) {
                                _characters[j]->move(newPos[_activeCharacter->getType()] - sortedNewPos[i]);
                            }
                        }
                        tick(sortedNewPos[i] - newPos[_activeCharacter->getType()], recursionLevel + 1);
                        break;
                    }
                }
                break;
            case REPEAT_MOVE:
                tick(moveOffset, recursionLevel + 1);
                break;
            case FINISH:
                break;
            default:
                nextCharacter();
                break;
        }
    }

    void setGameOverCallback(std::function<void(Character& character)> callback) {
        _gameOverCallback = std::move(callback);
    }

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        target.draw(_tilesBg);
        target.draw(_tileMgr);
        for (auto &c : _characters) {
            sf::RenderStates statesCopy = states;
            statesCopy.transform *= c->getTransform();
            target.draw(*c);
        }
    }

private:
    void nextCharacter() {
        if (_activeCharacter->getType() == DOGE) {
            _activeCharacter = _characters[0].get();
        } else {
            _activeCharacter = _characters[_activeCharacter->getType() + 1].get();
        }
    }

    TileManager _tileMgr;
    engine::Sprite _tilesBg;
    std::unique_ptr<Character> _characters[4];

    std::function<void(Character&)> _gameOverCallback;

    Character* _activeCharacter = nullptr;
};