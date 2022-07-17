#pragma once

#include "engine/State.hpp"
#include "engine/Assets.hpp"


class GameOverState : public engine::State {
public:
    GameOverState();

private:
    void on_activate() override;
    void on_deactivate() override;
	void on_draw() override;

    ///////////////
    // Variables //
    ///////////////
    sf::Music _gameoverMusic;
};
