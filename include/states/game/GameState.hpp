#pragma once

#include "engine/State.hpp"
#include "engine/StateMachine.hpp"


class GameState : public engine::State {
public:
	GameState();

private:
	void on_draw() override;


	///////////////
	// Variables //
	///////////////
	engine::StateMachine _stateMachine;
};
