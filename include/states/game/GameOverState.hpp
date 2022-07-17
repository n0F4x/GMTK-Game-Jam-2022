#pragma once

#include "engine/State.hpp"
#include "engine/drawables/Sprite.hpp"
#include "engine/drawables/Text.hpp"
#include "UI/ProgressBar.hpp"
#include "states/BoardGameManager.hpp"
#include "states/CharacterType.hpp"


class GameOverState : public engine::State {
public:
	GameOverState();

protected:
	void on_draw() override;
	void on_update() override;

private:
	void background_setup();
	void character_setup();
	void postits_setup();
	void game_board_setup();
	void helper_setup();

	///////////////
	// Variables //
	///////////////

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

	BoardGameManager _boardGameManager{ CharacterType::BOY };

	// Time
	UI::ProgressBar _timeDisplay{ { 600, 20 } };

	// Helper
	engine::Sprite _tileInfoDisplay;

	engine::Sprite _gameOver, _title;

	sf::Clock _clock;
};
