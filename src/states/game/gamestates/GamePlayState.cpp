#include "states/game/gamestates/GamePlayState.hpp"

#include "states/game/gamestates/gameplaystates/GamePlayLookAroundState.hpp"
#include "states/game/gamestates/gameplaystates/GamePlaySelectState.hpp"


GamePlayState::GamePlayState() {
	addStateMachine(&_stateMachine);
	_stateMachine.addState("LookAround", std::make_unique<GamePlayLookAroundState>());
	_stateMachine.addState("Select", std::make_unique<GamePlaySelectState>());

	_stateMachine.setInitialState("LookAround");
}


void GamePlayState::on_draw() { /*TODO*/ }
