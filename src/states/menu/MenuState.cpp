#include "states/menu/MenuState.hpp"

#include "engine/Window.hpp"
#include "animations/Bezier.hpp"
#include "animations/BezierScale.hpp"
#include "animations/BezierColor.hpp"


sf::Color operator*(sf::Color color, float factor);


MenuState::MenuState() {
	// MAIN MENU
	_floor.setTexture(&engine::Assets::getTexture("Environment/floor"));
	_floor.scale(6.f, 6.f);
	renderer().push_background(&_floor);

	_table.setTexture(&engine::Assets::getTexture("Environment/table"));
	_table.setPosition(480, 270);
	_table.scale(6.f, 6.f);
	renderer().push_background(&_table);

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

	_scaler.setPosition(960, 540);
	_scaler.setOrigin(960, 540);
	_scaler.attach_child(&_floor);
	_scaler.attach_child(&_table);
	_scaler.attach_child(&_croissant);
	_scaler.attach_child(&_plant);
	_scaler.attach_child(&_title);
	_scaler.attach_child(&_coffee);
	_scaler.setScale(5, 5);

	engine::Animator* scaleAnimator = _scaler.setComponent(std::make_unique<engine::Animator>());
	_scaler.getComponent<engine::Animator>()->addAnimation("zoomOut", std::make_unique<animations::EaseScale>());
	scaleAnimator->findAnimation("zoomOut")->setScale({ -4.f, -4.f });
	scaleAnimator->findAnimation("zoomOut")->setTime(sf::seconds(3));

	//TODO - test
	engine::Animator* testAnimator = _croissant.setComponent(std::make_unique<engine::Animator>());
	_croissant.getComponent<engine::Animator>()->addAnimation("out", std::make_unique<animations::Ease>());
	testAnimator->findAnimation("out")->setDistance({ -400.f, -600.f });
	testAnimator->findAnimation("out")->setTime(sf::seconds(3));
	addObject(&_croissant);

	addObject(&_scaler);

	_clickText.setOrigin(_clickText.getGlobalBounds().width / 2.f, _clickText.getGlobalBounds().height / 2.f);
	_clickText.setPosition(engine::Window::getSize().x / 2.f, engine::Window::getSize().y * 9.f / 10.f);
	_clickText.setOutlineThickness(4.f);
	_clickText.setFillColor(sf::Color{ 227, 230, 255 });
	_clickText.setOutlineColor(sf::Color::Black);
	addObject(&_clickText);
	renderer().push_background(&_clickText);

	//_scaler.getComponent<engine::Animator>()->findAnimation("zoomOut")->start();
	//TODO - (click to start game) text on bottom center of screen
	//TODO - take items off table animation, main title, click text fadeOut while zooming out
}

void MenuState::handle_event(const sf::Event& event) {
	if (!_startGame && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		_startGame = true;
		_clock.restart();
		renderer().remove_background(&_clickText);
	}
}


void MenuState::on_activate() {
	_startGame = false;
}


void MenuState::on_update() {
	if (_startGame) {
		_scaler.getComponent<engine::Animator>()->findAnimation("zoomOut")->start();
		_croissant.getComponent<engine::Animator>()->findAnimation("out")->start();
		if (_clock.getElapsedTime() >= sf::seconds(3)) {
			//changeState("Game");
		}
	}
}

void MenuState::on_draw() {
	renderer().render();
}
