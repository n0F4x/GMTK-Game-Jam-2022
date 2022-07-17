#include "states/game/gamestates/gameplaystates/GamePlayLookAroundState.hpp"

#include <iostream>


int GamePlayLookAroundState::setup() {
	if (_storeState = globalStore()->get("selector"); _storeState == nullptr) {
		std::cerr << "\nGamePlayLookAroundState: [ERROR] _storeState is nullptr.\n";
		return 1;
	}
	return 0;
}


void GamePlayLookAroundState::on_update() {
	if (*_storeState != "LookAround") {
		changeState("Select");
	}
}

void GamePlayLookAroundState::on_draw() { /*empty*/ }
