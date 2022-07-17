#include "states/game/gamestates/GamePlayState.hpp"

#include "states/game/gamestates/gameplaystates/GamePlayLookAroundState.hpp"
#include "states/game/gamestates/gameplaystates/GamePlaySelectState.hpp"


GamePlayState::GamePlayState() {
	addStateMachine(&_stateMachine);
	_stateMachine.addState("LookAround", std::make_unique<GamePlayLookAroundState>());
	_stateMachine.addState("Select", std::make_unique<GamePlaySelectState>());

	_stateMachine.setInitialState("LookAround");
}


int GamePlayState::setup() {
	store().add("selector", "LookAround");

	return 0;
}


void GamePlayState::handle_event(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
		if (*store().get("selector") == "LookAround") {
			*store().get("selector") = "Select";
		}
		else if (*store().get("selector") == "Select") {
			*store().get("selector") = "LookAround";
		}
	}

	_stateMachine->handle_event(event);
}

void GamePlayState::on_update() {
	_stateMachine->update();
}

void GamePlayState::on_draw() { 
	_stateMachine->draw();
}
