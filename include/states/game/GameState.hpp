#pragma once

#include "engine/State.hpp"
#include "engine/StateMachine.hpp"
#include "engine/drawables/Sprite.hpp"
#include "engine/drawables/Text.hpp"
#include "engine/Assets.hpp"
#include "UI/ProgressBar.hpp"


class GameState : public engine::State {
public:
	GameState();

protected:
	void handle_event(const sf::Event& event) override;
	void on_update() override;
	void on_draw() override;


private:
	void background_setup();
	void character_setup();
	void postits_setup();
	void helper_setup();

	///////////////
	// Variables //
	///////////////
	engine::StateMachine _stateMachine;


	// Background
	engine::Sprite _floor;
	engine::Sprite _table;
	engine::Sprite _table2;
	engine::Sprite _croissant;
	engine::Sprite _plant;
	engine::Sprite _plant2;
	engine::Sprite _coffee;
	engine::Object _scaler;


	bool _characterAnimations = false;
	// Characters
	engine::Sprite _boy, _girl, _grandpa, _dog;
	engine::Sprite _boyBarBack, _girlBarBack, _gradpaBarBack, _dogBarBack;
	UI::ProgressBar _boyBar{ {392.f, 32.f} }, _girlBar{ {392.f, 32.f} }, _grandpaBar{ {392.f, 32.f} }, _dogBar{ {392.f, 32.f} };


	// Postits
	engine::Sprite _boyPostit, _girlPostit, _grandpaPostit, _dogPostit;
	engine::Text _boyText{ "taking over", engine::Assets::getFont("unlearned"), 26 };
	engine::Text _girlText{ "anyone going back", engine::Assets::getFont("unlearned"), 26 };
	engine::Text _grandpaText{ "standing on corner", engine::Assets::getFont("unlearned"), 26 };
	engine::Text _dogText{ "being with someone", engine::Assets::getFont("unlearned"), 26 };

	// Helper
	engine::Sprite _tileInfoDisplay;
};
