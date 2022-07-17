#pragma once

#include <utility>

#include "TileManager.hpp"
#include "Character.hpp"
#include "CharacterType.hpp"
#include "engine/Window.hpp"
#include "animations/Bezier.hpp"

using namespace engine;

class BoardGameManager : public Sprite {
public:
    BoardGameManager(CharacterType startingCharacter, const std::function<void(Character&)>& gameOverCallback = std::function<void(Character&)>());

    Character& getCharacter(CharacterType c);

    Character& getActiveCharacter();

    bool isBoardOccupied() const;

    void diceRoll(int moveOffset);

    void updateBoard();

    void setGameOverCallback(std::function<void(Character& character)> callback);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    void calculateNewMove(CharacterType c, int moveOffset);

    // return true if character is done with their turns
    bool calculateTilesAndHappiness();

    void nextCharacter();

    TileManager _tileMgr;
    engine::Sprite _tilesBg;
    std::unique_ptr<Character> _characters[4];

    std::function<void(Character&)> _gameOverCallback;

    Character* _activeCharacter = nullptr;

    int recursionLevel = 0, activeCharMoveOffset = 0;
    int moveOffsetsRemaining[4] = { 0 };
    int oldPos[4], newPos[4];

    sf::Clock clock;
    bool stepFinishedInTurn = false;

    bool _boardOccupied = false;
};