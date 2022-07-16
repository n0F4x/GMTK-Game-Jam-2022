#pragma once

#include "engine/State.hpp"
#include "UI/Button.hpp"
#include "engine/Assets.hpp"


class MenuState : public engine::State {
public:
	MenuState();

protected:
	void on_draw() override;


private:
	///////////////
	// Variables //
	///////////////
	UI::Button _startButton{ &engine::Assets::getTexture("UI/start"), &engine::Assets::getTexture("UI/start_underline") };
};
