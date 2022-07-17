#pragma once

#include "engine/State.hpp"
#include "engine/Assets.hpp"
#include "engine/drawables/Sprite.hpp"
#include "engine/drawables/RectangleShape.hpp"
#include "UI/Button.hpp"
#include "UI/ProgressBar.hpp"


class GamePlaySelectState : public engine::State {
public:
	GamePlaySelectState();

private:
	int setup() override;
	void on_activate() override;

	void on_update() override;
	void on_draw() override;

	///////////////
	// Variables //
	///////////////
	std::string* _storeState = nullptr;
	sf::Clock _clock;
	bool _exiting = false;
	bool _active = false;

	engine::Object _selectHolder;
	engine::Sprite _dice1, _dice2, _dice3, _dice4, _dice5, _dice6;
	UI::Button _button1{ &engine::Assets::getTexture("UI/transparent"), &engine::Assets::getTexture("UI/outline") };
	UI::Button _button2{ &engine::Assets::getTexture("UI/transparent"), &engine::Assets::getTexture("UI/outline") };
	UI::Button _button3{ &engine::Assets::getTexture("UI/transparent"), &engine::Assets::getTexture("UI/outline") };
	UI::Button _button4{ &engine::Assets::getTexture("UI/transparent"), &engine::Assets::getTexture("UI/outline") };
	UI::Button _button5{ &engine::Assets::getTexture("UI/transparent"), &engine::Assets::getTexture("UI/outline") };
	UI::Button _button6{ &engine::Assets::getTexture("UI/transparent"), &engine::Assets::getTexture("UI/outline") };
	engine::Sprite _selectText;
	UI::ProgressBar _selectTime{ { 930, 30 } };
	engine::Sprite _selectBackdrop;
};
