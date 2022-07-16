#pragma once

#include "engine/State.hpp"
#include "engine/StateMachine.hpp"


class GameState : public engine::State {
public:
	GameState();

protected:
	void on_activate() override;

	void handle_event(const sf::Event& event) override;
	void on_update() override;
	void on_draw() override;


private:
	///////////////
	// Variables //
	///////////////
	engine::StateMachine _stateMachine;
};
