#include "states/game/gamestates/gameplaystates/GamePlaySelectState.hpp"

#include <iostream>
#include "engine/Assets.hpp"
#include "animations/Bezier.hpp"


GamePlaySelectState::GamePlaySelectState() {
	_selectHolder.setPosition(960, 540);

	_selectBackdrop.setTexture(&engine::Assets::getTexture("UI/backdrop"));
	_selectBackdrop.setPosition(0, -540 + 270); // y=-540
	_selectBackdrop.setScale(8.f, 6.f);
	renderer().push_priority(&_selectBackdrop);

	_dice1.setTexture(&engine::Assets::getTexture("DiceSides/1"));
	_dice1.scale(7.f, 7.f);
	_dice1.setPosition(369, 700);
	renderer().push_priority(&_dice1);
	_dice2.setTexture(&engine::Assets::getTexture("DiceSides/2"));
	_dice2.scale(7.f, 7.f);
	_dice2.setPosition(569, 700);
	renderer().push_priority(&_dice2);
	_dice3.setTexture(&engine::Assets::getTexture("DiceSides/3"));
	_dice3.scale(7.f, 7.f);
	_dice3.setPosition(769, 700);
	renderer().push_priority(&_dice3);
	_dice4.setTexture(&engine::Assets::getTexture("DiceSides/4"));
	_dice4.scale(7.f, 7.f);
	_dice4.setPosition(969, 700);
	renderer().push_priority(&_dice4);
	_dice5.setTexture(&engine::Assets::getTexture("DiceSides/5"));
	_dice5.scale(7.f, 7.f);
	_dice5.setPosition(1169, 700);
	renderer().push_priority(&_dice5);
	_dice6.setTexture(&engine::Assets::getTexture("DiceSides/6"));
	_dice6.scale(7.f, 7.f);
	_dice6.setPosition(1369, 700);
	renderer().push_priority(&_dice6);


	_button1.setPosition(369, 700);
	_button1.scale(7.f, 7.f);
	_button2.setPosition(569, 700);
	_button2.scale(7.f, 7.f);
	_button3.setPosition(769, 700);
	_button3.scale(7.f, 7.f);
	_button4.setPosition(969, 700);
	_button4.scale(7.f, 7.f);
	_button5.setPosition(1169, 700);
	_button5.scale(7.f, 7.f);
	_button6.setPosition(1369, 700);
	_button6.scale(7.f, 7.f);

	_selectText.setTexture(&engine::Assets::getTexture("UI/select"));
	_selectText.scale(10.f, 10.f);
	_selectText.setPosition(485, 300);
	renderer().push_priority(&_selectText);

	_selectTime.setPrimaryColor(sf::Color::White);
	_selectTime.setSecondaryColor(sf::Color::White);
	_selectTime.setPosition({ 495,600 });
	renderer().push_priority(&_selectTime);
	addObject(&_selectTime);

	_selectHolder.attach_child(&_dice1);
	_selectHolder.attach_child(&_dice2);
	_selectHolder.attach_child(&_dice3);
	_selectHolder.attach_child(&_dice4);
	_selectHolder.attach_child(&_dice5);
	_selectHolder.attach_child(&_dice6);
	_selectHolder.attach_child(&_selectBackdrop);
	_selectHolder.attach_child(&_selectText);
	_selectHolder.attach_child(&_selectTime);
	addObject(&_selectHolder);

	//_selectHolder.setPosition(960, -540 - 250);
	engine::Animator* selectAnimator = _selectHolder.setComponent(std::make_unique<engine::Animator>());
	_selectHolder.getComponent<engine::Animator>()->addAnimation("in", std::make_unique<animations::Ease>());
	selectAnimator->findAnimation("in")->setDistance({ 0, 1080 + 250 });
	selectAnimator->findAnimation("in")->setTime(sf::seconds(0.5));
	_selectHolder.getComponent<engine::Animator>()->addAnimation("out", std::make_unique<animations::Ease_In_Out>());
	selectAnimator->findAnimation("out")->setDistance({ 0, 1080 + 250 });
	selectAnimator->findAnimation("out")->setTime(sf::seconds(0.5));
}


int GamePlaySelectState::setup() {
	if (_storeState = globalStore()->get("selector"); _storeState == nullptr) {
		std::cerr << "\nGamePlaySelectState: [ERROR] _storeState is nullptr.\n";
		return 1;
	}
	return 0;
}

void GamePlaySelectState::on_activate() {
	_selectHolder.setPosition(960, -790);
	_selectHolder.getComponent<engine::Animator>()->findAnimation("in")->start();
	_clock.restart();
	_exiting = false;
	_active = false;
}


void GamePlaySelectState::on_update() {
	if (!_exiting && _clock.getElapsedTime() > sf::seconds(0.5f)) {
		_selectTime.setProgress(1.f - (_clock.getElapsedTime().asSeconds() - 0.5f) / 3.f);

		_button1.update();
		_button2.update();
		_button3.update();
		_button4.update();
		_button5.update();
		_button6.update();
		if (!_active) {
			renderer().push_priority(&_button1);
			renderer().push_priority(&_button2);
			renderer().push_priority(&_button3);
			renderer().push_priority(&_button4);
			renderer().push_priority(&_button5);
			renderer().push_priority(&_button6);
			_active = true;
		}
	}
	if (_clock.getElapsedTime() > sf::seconds(3.5f)) {
		_selectHolder.getComponent<engine::Animator>()->findAnimation("out")->start();
		_clock.restart();
		_exiting = true;
		renderer().remove_priority(&_button1);
		renderer().remove_priority(&_button2);
		renderer().remove_priority(&_button3);
		renderer().remove_priority(&_button4);
		renderer().remove_priority(&_button5);
		renderer().remove_priority(&_button6);
	}
	if (_exiting && _clock.getElapsedTime() > sf::seconds(0.5f)) {
		*_storeState = "LookAround";
		changeState("LookAround");
	}
}

void GamePlaySelectState::on_draw() { 
	renderer().render();
}
