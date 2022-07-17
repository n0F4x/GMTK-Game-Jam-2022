#pragma once

#include "engine/State.hpp"


class GamePlayLookAroundState : public engine::State {
protected:
	int setup() override;

	void on_update() override;
	void on_draw() override;


	///////////////
	// Variables //
	///////////////
	std::string* _storeState = nullptr;
};
