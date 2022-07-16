#pragma once

#include <iostream>
#include <random>
#include "engine/Assets.hpp"
#include "engine/Window.hpp"
#include "engine/State.hpp"
#include "engine/StateMachine.hpp"
#include "engine/Object.hpp"
#include "engine/drawables/Sprite.hpp"
#include "engine/drawables/RectangleShape.hpp"
#include "engine/drawables/CircleShape.hpp"
#include "engine/drawables/Arc.hpp"
#include "animations/Bezier.hpp"
#include "animations/BezierScale.hpp"
#include "UI/Button.hpp"
#include "UI/ProgressBar.hpp"
#include "states/Settings.hpp"
#include "states/Tile.hpp"
#include "states/TileManager.hpp"
#include "states/BoardGameManager.hpp"

class SampleChildState : public engine::State {
public:
	explicit SampleChildState(const std::string_view& side) : _side{ side } {
		_sprite.setTexture(&engine::Assets::getTexture("sample/ThumbsUp"));
		_sprite.setSize({ 100.f, 100.f });
		renderer().push_background(&_sprite);

		if (side == "Left") {
			_sprite.setOrigin(0.f, _sprite.getSize().y / 2.f);
		}
		else if (side == "Right") {
			_sprite.setOrigin(_sprite.getSize().x, _sprite.getSize().y / 2.f);
		}
		_sprite.setPosition(engine::Window::getSize() / 2.f + _sprite.getOrigin() - _sprite.getSize() / 2.f);
	}

	int setup() override {
		if (_restart = globalStore()->get("restart"); _restart == nullptr) {
			return 1;
		}
		return 0;
	}

	void handle_event(const sf::Event&) override { /*empty*/ }

	void on_update() override {
		if (*_restart == "true") {
			_clock.restart();
			*_restart = "false";
		}

		if (_side == "Left") {
			_sprite.rotate(_rotationClock.restart() / _rotationTime * 360 * -1);
		}
		else if (_side == "Right") {
			_sprite.rotate(_rotationClock.restart() / _rotationTime * 360);
		}

		if (_clock.getElapsedTime() >= _rotationTime) {
			if (_side == "Left") {
				changeState("Child2");
			}
			else if (_side == "Right") {
				changeState("Child1");
			}
			_sprite.setRotation(0.f);
			*_restart = "true";
		}
	}

	void on_draw() override {
		renderer().render();
	}


private:
	sf::RectangleShape _sprite;
	sf::Clock _clock;
	sf::Clock _rotationClock;
	sf::Time _rotationTime = sf::seconds(2);

	const std::string _side;
	std::string* _restart = nullptr;
};


class SampleState : public engine::State {
public:
	SampleState() {
		addStateMachine(&_machine);

		_machine.addState("Child1", std::make_unique<SampleChildState>("Left"));
		_machine.addState("Child2", std::make_unique<SampleChildState>("Right"));
		_machine.setInitialState("Child1");	// this is the default

		store().add("restart", "true");

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

		Animator* scaleAnimator = _scaler.setComponent(std::make_unique<engine::Animator>());
		_scaler.getComponent<engine::Animator>()->addAnimation("zoomOut", std::make_unique<animations::EaseScale>());
		scaleAnimator->findAnimation("zoomOut")->setScale({-4.f, -4.f});
		scaleAnimator->findAnimation("zoomOut")->setTime(sf::seconds(3));

		addObject(&_scaler);

		//_scaler.getComponent<engine::Animator>()->findAnimation("zoomOut")->start();
		//TODO - (click to start game) text on bottom center of screen
		//TODO - take items off table animation, main title, click text fadeOut while zooming out

		// END OF MENU

		_boy.setTexture(&engine::Assets::getTexture("Environment/blue_player"));
		_boy.setPosition(360 - 500, 120 - 500);
		_boy.scale(8.f, 8.f);
		addObject(&_boy);
		renderer().push_background(&_boy);
		auto animator = _boy.setComponent(std::make_unique<engine::Animator>());
		animator->addAnimation("in", std::make_unique<animations::Ease>());
		animator->findAnimation("in")->setDistance({ 500.f, 500.f });
		animator->findAnimation("in")->setTime(sf::seconds(3));

		_girl.setTexture(&engine::Assets::getTexture("Environment/green_player"));
		_girl.setPosition(sf::Vector2f(1320 + 500, 120 - 500));
		_girl.scale(10.f, 10.f);
		addObject(&_girl);
		renderer().push_background(&_girl);
		animator = _girl.setComponent(std::make_unique<engine::Animator>());
		animator->addAnimation("in", std::make_unique<animations::Ease>());
		animator->findAnimation("in")->setDistance({ -500.f, 500.f });
		animator->findAnimation("in")->setTime(sf::seconds(3.5f));

		_grandpa.setTexture(&engine::Assets::getTexture("Environment/red_player"));
		_grandpa.setPosition(1290 + 500, 650 + 500);
		_grandpa.scale(12.f, 12.f);
		addObject(&_grandpa);
		renderer().push_background(&_grandpa);
		animator = _grandpa.setComponent(std::make_unique<engine::Animator>());
		animator->addAnimation("in", std::make_unique<animations::Ease>());
		animator->findAnimation("in")->setDistance({ -500.f, -500.f });
		animator->findAnimation("in")->setTime(sf::seconds(4));

		_dog.setTexture(&engine::Assets::getTexture("Environment/yellow_player"));
		_dog.setPosition(sf::Vector2f(350 - 500, 700 + 500));
		_dog.scale(8.f, 8.f);
		addObject(&_dog);
		renderer().push_background(&_dog);
		animator = _dog.setComponent(std::make_unique<engine::Animator>());
		animator->addAnimation("in", std::make_unique<animations::Ease>());
		animator->findAnimation("in")->setDistance({ 500.f, -500.f });
		animator->findAnimation("in")->setTime(sf::seconds(4.5f));

		// Happinesses
		_boyBarBack.setTexture(&engine::Assets::getTexture("UI/bar_background"));
		_boyBarBack.setPosition(50, 50 - 500);
		_boyBarBack.scale(4.f, 4.f);
		addObject(&_boyBarBack);
		renderer().push_background(&_boyBarBack);
		animator = _boyBarBack.setComponent(std::make_unique<engine::Animator>());
		animator->addAnimation("in", std::make_unique<animations::Ease>());
		animator->findAnimation("in")->setDistance({ 0, 500.f });
		animator->findAnimation("in")->setTime(sf::seconds(6.f));

		_boyBar.setPosition(54, 54 - 500);
		addObject(&_boyBar);
		renderer().push_background(&_boyBar);
		_boyBar.attach_parent(&_boyBarBack);
		_boyBar.setPrimaryColor(sf::Color(88, 193, 53, 255));
		_boyBar.setSecondaryColor(sf::Color(223, 63, 35, 255));

		_girlBarBack.setTexture(&engine::Assets::getTexture("UI/bar_background"));
		_girlBarBack.scale(4.f, 4.f);
		addObject(&_girlBarBack);
		renderer().push_background(&_girlBarBack);
		animator = _girlBarBack.setComponent(std::make_unique<engine::Animator>());
		animator->addAnimation("in", std::make_unique<animations::Ease>());
		animator->findAnimation("in")->setDistance({ 0, 500.f });
		animator->findAnimation("in")->setTime(sf::seconds(6.f));

		addObject(&_girlBar);
		renderer().push_background(&_girlBar);
		_girlBar.attach_parent(&_girlBarBack);
		_girlBar.setPrimaryColor(sf::Color(88, 193, 53, 255));
		_girlBar.setSecondaryColor(sf::Color(223, 63, 35, 255));

		_girlBarBack.rotate(180);
		_girlBarBack.setPosition(1870, 100 - 500);
		_girlBar.setPosition(1866, 96 - 500);

		_dogBarBack.setTexture(&engine::Assets::getTexture("UI/bar_background"));
		_dogBarBack.setPosition(50, 990 + 500);
		_dogBarBack.scale(4.f, 4.f);
		addObject(&_dogBarBack);
		renderer().push_background(&_dogBarBack);
		animator = _dogBarBack.setComponent(std::make_unique<engine::Animator>());
		animator->addAnimation("in", std::make_unique<animations::Ease>());
		animator->findAnimation("in")->setDistance({ 0, -500.f });
		animator->findAnimation("in")->setTime(sf::seconds(6.f));

		_dogBar.setPosition(54, 994 + 500);
		addObject(&_dogBar);
		renderer().push_background(&_dogBar);
		_dogBar.attach_parent(&_dogBarBack);
		_dogBar.setPrimaryColor(sf::Color(88, 193, 53, 255));
		_dogBar.setSecondaryColor(sf::Color(223, 63, 35, 255));

		_gradpaBarBack.setTexture(&engine::Assets::getTexture("UI/bar_background"));
		_gradpaBarBack.scale(4.f, 4.f);
		addObject(&_gradpaBarBack);
		renderer().push_background(&_gradpaBarBack);
		animator = _gradpaBarBack.setComponent(std::make_unique<engine::Animator>());
		animator->addAnimation("in", std::make_unique<animations::Ease>());
		animator->findAnimation("in")->setDistance({ 0, -500.f });
		animator->findAnimation("in")->setTime(sf::seconds(6.f));

		addObject(&_grandpaBar);
		renderer().push_background(&_grandpaBar);
		_grandpaBar.attach_parent(&_gradpaBarBack);
		_grandpaBar.setPrimaryColor(sf::Color(88, 193, 53, 255));
		_grandpaBar.setSecondaryColor(sf::Color(223, 63, 35, 255));

		_gradpaBarBack.rotate(180);
		_gradpaBarBack.setPosition(1870, 1030 + 500);
		_grandpaBar.setPosition(1866, 1026 + 500);

		// START ANIMATIONS
		/*
		_boy.getComponent<engine::Animator>()->findAnimation("in")->start();
		_girl.getComponent<engine::Animator>()->findAnimation("in")->start();
		_grandpa.getComponent<engine::Animator>()->findAnimation("in")->start();
		_dog.getComponent<engine::Animator>()->findAnimation("in")->start();

		_boyBarBack.getComponent<engine::Animator>()->findAnimation("in")->start();
		_girlBarBack.getComponent<engine::Animator>()->findAnimation("in")->start();
		_gradpaBarBack.getComponent<engine::Animator>()->findAnimation("in")->start();
		_dogBarBack.getComponent<engine::Animator>()->findAnimation("in")->start();
		*/
		
	}

	void handle_event(const sf::Event& event) override {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Right) changeState("Physics");
			if (event.key.code == sf::Keyboard::Enter) changeState("Menu");
		}
	}

	void on_update() override {
		_machine->update();
	}

	void on_draw() override {
		_machine->draw();

		renderer().render();

        Window::draw(_boardGameMgr);
	}


private:
	engine::StateMachine _machine;

	engine::Object _scaler;

	engine::Sprite _floor, _table, _boy, _girl, _grandpa, _dog;
	engine::Sprite _boyBarBack, _girlBarBack, _gradpaBarBack, _dogBarBack;

	UI::ProgressBar _boyBar { {392.f, 32.f} }, _girlBar{ {392.f, 32.f} }, _grandpaBar{ {392.f, 32.f} }, _dogBar{ {392.f, 32.f} };

	//Tabletop
	engine::Sprite _title;
	engine::Sprite _croissant, _plant, _coffee;

	TileManager _tileMgr;
	engine::RectangleShape _tilesBg;
    BoardGameManager _boardGameMgr;
};


class PhysicsSampleState : public engine::State {
public:
	PhysicsSampleState() {
		renderer().push_background(&_sprite);
		renderer().push_background(&_shape);
		music.openFromFile(engine::Assets::ASSETS_PATH + "/music/sample/calmbgm.ogg");
		music.setLoop(true);

		_shape.setOutlineThickness(5);
		_shape.setFillColor(sf::Color(0, 0, 0, 0));
		_shape.setOutlineColor(sf::Color::Red);

		_sprite.scale(0.1f, 0.1f);

		_sprite.setComponent(std::make_unique<engine::Physics>());
		_sprite.setPosition(300, 100);

		_sprite.setComponent(std::make_unique<engine::Collider>(sf::FloatRect(0, _sprite.getSize().y / 4.f, _sprite.getSize().x, _sprite.getSize().y / 2.f)));

		auto* physicsComponent = _sprite.getComponent<engine::Physics>();
		physicsComponent->setVelocity(sf::Vector2f(160, 160));
		physicsComponent->apply_force(sf::Vector2f(0, 0));

		_bottomWall.setComponent(std::make_unique<engine::Collider>(sf::FloatRect(0, 0, _bottomWall.getSize().x, _bottomWall.getSize().y)));
		_bottomWall.setPosition(0.f, engine::Window::getSize().y);
		_leftWall.setComponent(std::make_unique<engine::Collider>(sf::FloatRect(0, 0, _leftWall.getSize().x, _leftWall.getSize().y)));
		_leftWall.setPosition(-50.f, 0.f);
		_topWall.setComponent(std::make_unique<engine::Collider>(sf::FloatRect(0, 0, _topWall.getSize().x, _topWall.getSize().y)));
		_topWall.setPosition(0.f, -50.f);
		_rightWall.setComponent(std::make_unique<engine::Collider>(sf::FloatRect(0, 0, _rightWall.getSize().x, _rightWall.getSize().y)));
		_rightWall.setPosition(engine::Window::getSize().x, 0.f);

		addObject(&_sprite);
		addObject(&_bottomWall);
		addObject(&_leftWall);
		addObject(&_topWall);
		addObject(&_rightWall);
	}

	void on_activate() override {
		if (Settings::soundOn) music.play();
	}

	void on_deactivate() override {
		music.pause();
	}

	void handle_event(const sf::Event& event) override {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Right) changeState("Animations");
			else if (event.key.code == sf::Keyboard::Left) changeState("Sample");
		}
	}

	void on_update() override {
		_shape.setPosition(sf::Vector2f(_sprite.getComponent<engine::Collider>()->getHitBox().left, _sprite.getComponent<engine::Collider>()->getHitBox().top));
		_shape.setSize(sf::Vector2f(_sprite.getComponent<engine::Collider>()->getHitBox().width, _sprite.getComponent<engine::Collider>()->getHitBox().height));

		if (_sprite.getComponent<engine::Collider>()->collided()) {
			_sprite.setColor(
				sf::Color{
					static_cast<sf::Uint8>(std::uniform_int_distribution{ 0, 155 }(_randomEngine)+100),
					static_cast<sf::Uint8>(std::uniform_int_distribution{ 0, 155 }(_randomEngine)+100),
					static_cast<sf::Uint8>(std::uniform_int_distribution{ 0, 155 }(_randomEngine)+100),
					255
				}
			);
		}
	}

	void on_draw() override {
		renderer().render();
	}


private:
	engine::Sprite _sprite{ &engine::Assets::getTexture("sample/surprise") };
	engine::RectangleShape _shape;

	engine::RectangleShape _bottomWall{ { engine::Window::getSize().x, 50.f } };
	engine::RectangleShape _leftWall{ { 50.f, engine::Window::getSize().y } };
	engine::RectangleShape _topWall{ { engine::Window::getSize().x, 50.f } };
	engine::RectangleShape _rightWall{ { 50.f, engine::Window::getSize().y } };

	std::mt19937 _randomEngine{ std::random_device{}() };

	sf::Music music;
};


class AnimationsSampleState : public engine::State {
public:
	AnimationsSampleState() {
		_shape.setOrigin(_shape.getSize() / 2.f);
		_shape.setPosition(engine::Window::getSize() / 2.f - sf::Vector2f{ 200.f, 0.f });
		_shape.setTexture(&engine::Assets::getTexture("sample/ThumbsUp"));
		addObject(&_shape);
	}

	int setup() override {
		auto animator = _shape.setComponent(std::make_unique<engine::Animator>());
		animator->addAnimation("Ease", std::make_unique<animations::Ease>());
		if (_animation = animator->findAnimation("Ease"); _animation == nullptr) {
			std::cerr << "\nAnimationsSampleState: _animation is nullptr\n";
			return 1;
		}
		_animation->setDistance({ -400.f, 0.f });
		_animation->setTime(sf::seconds(1));

		animator->addAnimation("EaseScale", std::make_unique<animations::EaseScale>());
		if (_animationScale = animator->findAnimation("EaseScale"); _animationScale == nullptr) {
			std::cerr << "\nAnimationsSampleState: _animationScale is nullptr\n";
			return 1;
		}
		_animationScale->setScale({ -1, -1.f });
		_animationScale->setTime(sf::seconds(1));

		return 0;
	}

	void handle_event(const sf::Event& event) override {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Left) changeState("Physics");
		}
	}

	void on_update() override {
		if (_tempTime + _clock.getElapsedTime() >= sf::seconds(1) && _animation->start()) {
			_animationScale->start();
			_clock.restart();
			_animation->setDistance(_animation->getDistance() * -1.f);
			_animationScale->setScale(_animationScale->getScale() * -1.f);
			_tempTime = sf::Time::Zero;
		}
	}

	void on_draw() override {
		engine::Window::draw(_shape);
	}

	void on_activate() override {
		_clock.restart();
	}

	void on_deactivate() override {
		_tempTime += _clock.getElapsedTime();
	}


private:
	sf::Clock _clock;
	sf::Time _tempTime;
	engine::RectangleShape _shape{ { 200.f, 200.f } };
	engine::Animation* _animation = nullptr;
	engine::Animation* _animationScale = nullptr;
};
