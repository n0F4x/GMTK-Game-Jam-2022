#include "states/game/gamestates/GamePlayState.hpp"

#include "states/game/gamestates/gameplaystates/GamePlayLookaroundState.hpp"
#include "states/game/gamestates/gameplaystates/GamePlaySelectState.hpp"


GamePlayState::GamePlayState() {
	_stateMachine.addState("LookAround", std::make_unique<GamePlayLookaroundState>());
	_stateMachine.addState("Select", std::make_unique<GamePlaySelectState>());

	_stateMachine.setInitialState("Lookaround");
}


void GamePlayState::on_draw() { /*TODO*/ }
