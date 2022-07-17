#include "states/game/gamestates/GamePlayState.hpp"

#include "states/game/gamestates/gameplaystates/GamePlayLookAroundState.hpp"
#include "states/game/gamestates/gameplaystates/GamePlaySelectState.hpp"
#include "states/Settings.hpp"

GamePlayState::GamePlayState() {
	addStateMachine(&_stateMachine);
	_stateMachine.addState("LookAround", std::make_unique<GamePlayLookAroundState>());
	_stateMachine.addState("Select", std::make_unique<GamePlaySelectState>());

	_stateMachine.setInitialState("LookAround");

    _gameplayMusic.openFromFile(engine::Assets::ASSETS_PATH + "/music/gameplay.ogg");
    _gameplayMusic.setLoop(true);
}


int GamePlayState::setup() {
	store().add("selector", "LookAround");
	_storeState = store().get("selector");
	globalStore()->add("selector", "LookAround");
	_globalState = globalStore()->get("selector");
	store().add("dice", "0"); // from 1 to 6 is valid
	_storeDice = store().get("dice");
	globalStore()->add("dice", "0"); // from 1 to 6 is valid
	_globalDice = globalStore()->get("dice");

	return 0;
}


void GamePlayState::handle_event(const sf::Event& event) {
	//if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
	//	if (*store().get("selector") == "LookAround") {
	//		*store().get("selector") = "Select";
	//	}
	//	else if (*store().get("selector") == "Select") {
	//		*store().get("selector") = "LookAround";
	//	}
	//}

	_stateMachine->handle_event(event);
}

void GamePlayState::on_activate() {
    if(Settings::soundOn) _gameplayMusic.play();
}

void GamePlayState::on_deactivate() {
    _gameplayMusic.stop();
}

void GamePlayState::on_update() {
	_stateMachine->update();
	if (*_storeDice == "-1") {
		*_globalDice = "0";
		*_storeDice = "0";
	}
	if (*_storeDice != "0") {
		*_globalDice = *_storeDice;
		*_storeDice = "0";
	}
	*_storeState = *_globalState;
}

void GamePlayState::on_draw() { 
	_stateMachine->draw();
}
