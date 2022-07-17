#include "states/game/gamestates/GameOverState.hpp"

#include "states/Settings.hpp"


void GameOverState::on_draw() { /*TODO*/ }

GameOverState::GameOverState() {


    _gameoverMusic.openFromFile(engine::Assets::ASSETS_PATH + "/music/endgame.ogg");
    _gameoverMusic.setLoop(false);
}

void GameOverState::on_activate() {
    if(Settings::soundOn) _gameoverMusic.play();
}

void GameOverState::on_deactivate() {
    _gameoverMusic.stop();
}
