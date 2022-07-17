#pragma once

#include "engine/State.hpp"
#include "engine/StateMachine.hpp"


class GamePlayState : public engine::State {
public:
	GamePlayState();

private:
	int setup() override;

	void handle_event(const sf::Event&) override;
	void on_update() override;
	void on_draw() override;


	///////////////
	// Variables //
	///////////////
	engine::StateMachine _stateMachine;
};
