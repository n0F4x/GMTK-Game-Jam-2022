#include "states/game/GameState.hpp"

#include "states/game/gamestates/GameInitState.hpp"
#include "states/game/gamestates/GamePlayState.hpp"
#include "states/game/gamestates/GamePausedState.hpp"
#include "states/game/gamestates/GameOverState.hpp"


GameState::GameState() {
	store().add("init", "false");

	addStateMachine(&_stateMachine);
	_stateMachine.addState("Init", std::make_unique<GameInitState>());
	_stateMachine.addState("Play", std::make_unique<GamePlayState>());
	_stateMachine.addState("Paused", std::make_unique<GamePausedState>());
	_stateMachine.addState("Over", std::make_unique<GameOverState>());

	_stateMachine.setInitialState("Init");
}


void GameState::on_activate() {
	*store().get("init") = "true";
}


void GameState::handle_event(const sf::Event& event) {
	_stateMachine->handle_event(event);
}

void GameState::on_update() {
	_stateMachine->update();
}

void GameState::on_draw() {
	_stateMachine->draw();
}
