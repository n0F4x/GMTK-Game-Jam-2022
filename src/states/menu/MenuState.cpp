#include "states/menu/MenuState.hpp"

#include "engine/Window.hpp"
#include "animations/Bezier.hpp"
#include "animations/BezierScale.hpp"
#include "animations/BezierFillColor.hpp"
#include "animations/BezierOutlineColor.hpp"


MenuState::MenuState() {
	// MAIN MENU
	_floor.setTexture(&engine::Assets::getTexture("Environment/floor"));
	_floor.scale(6.f, 6.f);
	renderer().push_background(&_floor);

	_table.setTexture(&engine::Assets::getTexture("Environment/table"));
	_table.setPosition(480, 270);
	_table.scale(6.f, 6.f);
	renderer().push_background(&_table);

	_table2.setTexture(&engine::Assets::getTexture("Environment/coffeetable"));
	_table2.setPosition(500, -120);
	_table2.scale(6.f, 6.f);
	renderer().push_background(&_table2);

	_croissant.setTexture(&engine::Assets::getTexture("Environment/croissant2"));
	_croissant.setPosition(800, 480);
	_croissant.scale(4.f, 4.f);
	renderer().push_background(&_croissant);

	_title.setTexture(&engine::Assets::getTexture("UI/title"));
	_title.setPosition(935, 480);
	_title.scale(7.5f / 5.f, 7.5f / 5.f);
	renderer().push_background(&_title);

	_plant.setTexture(&engine::Assets::getTexture("Environment/plant"));
	_plant.setPosition(1050, 350);
	_plant.scale(4.f, 4.f);
	renderer().push_background(&_plant);

	_coffee.setTexture(&engine::Assets::getTexture("Environment/coffee"));
	_coffee.setPosition(1050, 550);
	_coffee.scale(4.f, 4.f);
	renderer().push_background(&_coffee);

	_plant2.setTexture(&engine::Assets::getTexture("Environment/plant2"));
	_plant2.setPosition(700, 900);
	_plant2.scale(4.f, 4.f);
	renderer().push_background(&_plant2);

	_scaler.setPosition(960, 540);
	_scaler.setOrigin(960, 540);
	_scaler.attach_child(&_floor);
	_scaler.attach_child(&_table);
	_scaler.attach_child(&_table2);
	_scaler.attach_child(&_croissant);
	_scaler.attach_child(&_plant);
	_scaler.attach_child(&_title);
	_scaler.attach_child(&_coffee);
	_scaler.attach_child(&_plant2);
	_scaler.setScale(5, 5);

	engine::Animator* scaleAnimator = _scaler.setComponent(std::make_unique<engine::Animator>());
	_scaler.getComponent<engine::Animator>()->addAnimation("zoomOut", std::make_unique<animations::EaseScale>());
	scaleAnimator->findAnimation("zoomOut")->setScale({ -4.f, -4.f });
	scaleAnimator->findAnimation("zoomOut")->setTime(sf::seconds(3));

	//TODO - test
	engine::Animator* takerAnimator = _croissant.setComponent(std::make_unique<engine::Animator>());
	_croissant.getComponent<engine::Animator>()->addAnimation("out", std::make_unique<animations::Ease>());
	takerAnimator->findAnimation("out")->setDistance({ -150.f, -1300.f });
	takerAnimator->findAnimation("out")->setTime(sf::seconds(3));
	addObject(&_croissant);

	takerAnimator = _title.setComponent(std::make_unique<engine::Animator>());
	_title.getComponent<engine::Animator>()->addAnimation("out", std::make_unique<animations::Ease>());
	takerAnimator->findAnimation("out")->setDistance({ -630.f, -920.f });
	takerAnimator->findAnimation("out")->setTime(sf::seconds(4));
	addObject(&_title);

	takerAnimator = _coffee.setComponent(std::make_unique<engine::Animator>());
	_coffee.getComponent<engine::Animator>()->addAnimation("out", std::make_unique<animations::Ease>());
	takerAnimator->findAnimation("out")->setDistance({ -400.f, -1300.f });
	takerAnimator->findAnimation("out")->setTime(sf::seconds(3));
	addObject(&_coffee);

	takerAnimator = _plant.setComponent(std::make_unique<engine::Animator>());
	_plant.getComponent<engine::Animator>()->addAnimation("out", std::make_unique<animations::Ease>());
	takerAnimator->findAnimation("out")->setDistance({ 400.f, -900.f });
	takerAnimator->findAnimation("out")->setTime(sf::seconds(2));
	addObject(&_plant);

	addObject(&_scaler);

	_clickText.setOrigin(_clickText.getGlobalBounds().width / 2.f, _clickText.getGlobalBounds().height / 2.f);
	_clickText.setPosition(engine::Window::getSize().x / 2.f, engine::Window::getSize().y * 9.f / 10.f);
	_clickText.setOutlineThickness(3.f);
	_clickText.setFillColor(sf::Color{ 227, 230, 255 });
	_clickText.setOutlineColor(sf::Color::Black);
	engine::Animation* animation = _clickText.setComponent(std::make_unique<engine::Animator>())->addAnimation("fillColorOut", std::make_unique<animations::EaseFillColor>());
	animation->setTime(sf::seconds(2));
	animation->setFillColor({ 0.f, 0.f, 0.f, -255.f });
	animation = _clickText.getComponent<engine::Animator>()->addAnimation("outlineColorOut", std::make_unique<animations::EaseOutlineColor>());
	animation->setTime(sf::seconds(2));
	animation->setOutlineColor({ 0.f, 0.f, 0.f, -255.f });
	_fillPulseOnAnimation = _clickText.getComponent<engine::Animator>()->addAnimation("fillPulseOn", std::make_unique<animations::EaseFillColor>());
	_fillPulseOnAnimation->setTime(sf::seconds(2));
	_fillPulseOnAnimation->setFillColor({ 0.f, 0.f, 0.f, 255.f });
	_fillPulseOffAnimation = _clickText.getComponent<engine::Animator>()->addAnimation("fillPulseOff", std::make_unique<animations::EaseFillColor>());
	_fillPulseOffAnimation->setTime(sf::seconds(2));
	_fillPulseOffAnimation->setFillColor({ 0.f, 0.f, 0.f, -255.f });
	_outlinePulseOnAnimation = _clickText.getComponent<engine::Animator>()->addAnimation("outlinePulseOn", std::make_unique<animations::EaseOutlineColor>());
	_outlinePulseOnAnimation->setTime(sf::seconds(2));
	_outlinePulseOnAnimation->setOutlineColor({ 0.f, 0.f, 0.f, 255.f });
	_outlinePulseOffAnimation = _clickText.getComponent<engine::Animator>()->addAnimation("outlinePulseOff", std::make_unique<animations::EaseOutlineColor>());
	_outlinePulseOffAnimation->setTime(sf::seconds(2));
	_outlinePulseOffAnimation->setOutlineColor({ 0.f, 0.f, 0.f, -255.f });
	addObject(&_clickText);
	renderer().push_background(&_clickText);

	//TODO - animation
}

void MenuState::handle_event(const sf::Event& event) {
	if (!_startGame && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		_startGame = true;
		_clock.restart();
	}
}


void MenuState::on_activate() {
	_startGame = false;
}


void MenuState::on_update() {
	if (_startGame) {
		_fillPulseOnAnimation->stop();
		_fillPulseOffAnimation->stop();
		_outlinePulseOnAnimation->stop();
		_outlinePulseOffAnimation->stop();

		_clickText.getComponent<engine::Animator>()->findAnimation("fillColorOut")->start();
		_clickText.getComponent<engine::Animator>()->findAnimation("outlineColorOut")->start();


		_scaler.getComponent<engine::Animator>()->findAnimation("zoomOut")->start();
		_croissant.getComponent<engine::Animator>()->findAnimation("out")->start();
		_title.getComponent<engine::Animator>()->findAnimation("out")->start();
		_coffee.getComponent<engine::Animator>()->findAnimation("out")->start();
		_plant.getComponent<engine::Animator>()->findAnimation("out")->start();
		_startGame = false;
		if (_clock.getElapsedTime() >= sf::seconds(3)) {
			changeState("Game");
		}
	}
	else {
		if (_pulseClock.getElapsedTime() >= sf::seconds(2)) {
			if (_pulseOn) {
				_fillPulseOnAnimation->stop();
				_fillPulseOnAnimation->start();
				_outlinePulseOnAnimation->stop();
				_outlinePulseOnAnimation->start();
			}
			else {
				_fillPulseOffAnimation->stop();
				_fillPulseOffAnimation->start();
				_outlinePulseOffAnimation->stop();
				_outlinePulseOffAnimation->start();
			}
			_pulseOn = !_pulseOn;
			_pulseClock.restart();
		}
	}
}

void MenuState::on_draw() {
	renderer().render();
}
