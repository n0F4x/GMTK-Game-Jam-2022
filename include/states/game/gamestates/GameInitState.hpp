#pragma once

#include <vector>
#include "engine/State.hpp"
#include "engine/drawables/Sprite.hpp"
#include "UI/ProgressBar.hpp"

class engine::Animation;


class GameInitState : public engine::State {
public:
	GameInitState();

protected:
	int setup() override;

	void on_update() override;
	void on_draw() override;

	
private:
	///////////////
	// Variables //
	///////////////
	std::string* _storeInit = nullptr;
	bool _init = false;
	bool _init6 = false;

	sf::Clock _clock;

	engine::Sprite _boy, _girl, _grandpa, _dog;

	engine::Sprite _boyBarBack, _girlBarBack, _gradpaBarBack, _dogBarBack;
	UI::ProgressBar _boyBar{ {392.f, 32.f} }, _girlBar{ {392.f, 32.f} }, _grandpaBar{ {392.f, 32.f} }, _dogBar{ {392.f, 32.f} };

	// Background
	engine::Sprite _floor;
	engine::Sprite _table;
	engine::Sprite _table2;

	engine::Sprite _title;
	engine::Sprite _croissant;
	engine::Sprite _plant;
	engine::Sprite _plant2;
	engine::Sprite _coffee;
};
