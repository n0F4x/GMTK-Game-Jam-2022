#pragma once

#include "engine/Assets.hpp"
#include "engine/State.hpp"
#include "engine/StateMachine.hpp"


class GamePlayState : public engine::State {
public:
	GamePlayState();

private:
	int setup() override;

	void handle_event(const sf::Event&) override;

    void on_activate() override;
    void on_deactivate() override;

	void on_update() override;
	void on_draw() override;


	///////////////
	// Variables //
	///////////////
	engine::StateMachine _stateMachine;
    sf::Music _gameplayMusic;

	std::string* _storeState = nullptr;
	std::string* _globalState = nullptr;
	std::string* _globalDice = nullptr;
	std::string* _storeDice = nullptr;
};
