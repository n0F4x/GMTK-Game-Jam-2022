#pragma once

#include "engine/Assets.hpp"
#include "engine/State.hpp"
#include "engine/drawables/Sprite.hpp"
#include "engine/drawables/Text.hpp"


class MenuState : public engine::State {
public:
	MenuState();

	void handle_event(const sf::Event&) override;

protected:
	void on_activate() override;

	void on_update() override;
	void on_draw() override;


private:
	///////////////
	// Variables //
	///////////////
	bool _startGame = false;
	sf::Clock _clock;

	engine::Sprite _floor;
	engine::Sprite _table;
	engine::Object _scaler;
	//Tabletop
	engine::Sprite _title;
	engine::Sprite _croissant;
	engine::Sprite _plant;
	engine::Sprite _coffee;

	engine::Text _clickText{ "( click to start the game )", engine::Assets::getFont("unlearned2"), 56 };
};
