#pragma once

#include "TileManager.hpp"
#include "Character.hpp"
#include "Characters.hpp"

using namespace engine;

class BoardGameManager : public sf::Drawable {
public:
    BoardGameManager() {
        _tilesBg.setTexture(&engine::Assets::getTexture("Tiles/board_background"));
        _tilesBg.setPosition(Window::getSize().x / 2.f - (21 * 11 + 1) / 2.f * 3.f - 12, Window::getSize().y / 2.f - (21 * 7 + 1) / 2.f * 3.f - 12);
        _tilesBg.setScale(3, 3);

        _tileMgr.addTile(TileType::NORMAL, RIGHT);
        _tileMgr.addTile(TileType::NORMAL, RIGHT);
        _tileMgr.addTile(TileType::NORMAL, RIGHT);
        _tileMgr.addTile(TileType::NORMAL, RIGHT);
        _tileMgr.addTile(TileType::NORMAL, RIGHT);
        _tileMgr.addTile(TileType::NORMAL, RIGHT);
        _tileMgr.addTile(TileType::NORMAL, RIGHT);
        _tileMgr.addTile(TileType::NORMAL, RIGHT);
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
                &Assets::getTexture("Figures/blu"),
                5,
                1, 5, 2, -5,
                REPEAT_MOVE, 5, NORMAL, -5,
                ""
        );
        _characters[1] = std::make_unique<Character>(
                &Assets::getTexture("Figures/gren"),
                5,
                1, 5, 2, -5,
                REPEAT_MOVE, 5, NORMAL, -5,
                ""
        );
        _characters[2] = std::make_unique<Character>(
                &Assets::getTexture("Figures/red"),
                5,
                1, 5, 2, -5,
                REPEAT_MOVE, 5, NORMAL, -5,
                ""
        );
        _characters[3] = std::make_unique<Character>(
                &Assets::getTexture("Figures/yelow"),
                5,
                1, 5, 2, -5,
                REPEAT_MOVE, 5, NORMAL, -5,
                ""
        );
        _characters[0]->setScale(3.f);
        _characters[1]->setScale(3.f);
        _characters[2]->setScale(3.f);
        _characters[3]->setScale(3.f);

        _characters[0]->setCurrentTile(
                _tileMgr.getFirstTile()->getRelativeTile()->getRelativeTile()->getRelativeTile()->getRelativeTile()->getRelativeTile()->getRelativeTile()->getRelativeTile()->getRelativeTile()->getRelativeTile()->getRelativeTile()->getRelativeTile());
        _characters[1]->setCurrentTile(_tileMgr.getFirstTile());
        _characters[2]->setCurrentTile(_tileMgr.getFirstTile());
        _characters[3]->setCurrentTile(_tileMgr.getFirstTile());
    }

    Character& getCharacter(Characters c) {
        return *_characters[c];
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
    TileManager _tileMgr;
    engine::Sprite _tilesBg;
    std::unique_ptr<Character> _characters[4];
};