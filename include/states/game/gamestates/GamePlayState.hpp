#pragma once

#include "engine/State.hpp"
#include "engine/StateMachine.hpp"


class GamePlayState : public engine::State {
public:
	GamePlayState();

private:
	void on_draw() override;


	///////////////
	// Variables //
	///////////////
	engine::StateMachine _stateMachine;
};
