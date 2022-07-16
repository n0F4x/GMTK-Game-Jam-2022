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
#include "UI/Button.hpp"
#include "UI/ProgressBar.hpp"
#include "states/Settings.hpp"
#include "states/Tile.hpp"
#include "states/TileManager.hpp"

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
		_object.setComponent(std::make_unique<engine::Animator>());
		_object.getComponent<engine::Animator>();

		// Sprite
		_sprite.setTexture(&engine::Assets::getTexture("sample/ThumbsUp"));
		_sprite.setPosition(engine::Window::getSize() / 2.f + sf::Vector2f{ 0.f, -200.f });
		_sprite.scale(0.2f, 0.2f);
		_sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2);

		// Button
		_button.scale(sf::Vector2f{ 0.5f, 0.5f });
		_button.setPosition(engine::Window::getSize() / 2.f + sf::Vector2f{ -350.f, 500.f });
		_button.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2);
		_button.setCallback([this] { changeState("Physics"); });

		// RectangleShape
		_rectangleShape.setTexture(&engine::Assets::getTexture("sample/ThumbsUp"));
		_rectangleShape.setPosition(engine::Window::getSize() / 2.f + sf::Vector2f{ -400.f, 0.f });
		_rectangleShape.setSize({ 200.f, 200.f });
		_rectangleShape.setOutlineThickness(5);
		_rectangleShape.setOutlineColor(sf::Color::White);
		_rectangleShape.setOrigin(_rectangleShape.getSize() / 2.f);

		// CircleShape
		_circleShape.setTexture(&engine::Assets::getTexture("sample/ThumbsUp"));
		_circleShape.setPosition(engine::Window::getSize() / 2.f + sf::Vector2f{ 0.f, +200.f });
		_circleShape.setRadius(100.f);
		_circleShape.setOutlineThickness(5);
		_circleShape.setOutlineColor(sf::Color::White);
		_circleShape.setOrigin(_circleShape.getRadius(), _circleShape.getRadius());

		// Progressbar
		_progressbar.setPosition(engine::Window::getSize() / 2.f + sf::Vector2f{ 100.f, 370.f });
		_progressbar.setProgress(0.f);
		_progressbar.setPrimaryColor(sf::Color::Green);
		_progressbar.setSecondaryColor(sf::Color::Red);

		addStateMachine(&_machine);

		_machine.addState("Child1", std::make_unique<SampleChildState>("Left"));
		_machine.addState("Child2", std::make_unique<SampleChildState>("Right"));
		_machine.setInitialState("Child1");	// this is the default

		store().add("restart", "true");
		
		// Environment
		_table.setTexture(&engine::Assets::getTexture("Environment/table"));
		_table.setPosition(480, 270);
		_table.scale(6.f, 6.f);
		renderer().push_background(&_table);

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
		_grandpa.setPosition(1270 + 500, 630 + 500);
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

		//TODO - remove
		_boy.getComponent<engine::Animator>()->findAnimation("in")->start();
		_girl.getComponent<engine::Animator>()->findAnimation("in")->start();
		_grandpa.getComponent<engine::Animator>()->findAnimation("in")->start();
		_dog.getComponent<engine::Animator>()->findAnimation("in")->start();
	}

	void handle_event(const sf::Event& event) override {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Right) changeState("Physics");
			if (event.key.code == sf::Keyboard::Enter) changeState("Menu");
        }
    }

	void on_update() override {
		_machine->update();

		_sprite.rotate(-1.f);
		_button.update();
		_rectangleShape.rotate(1.f);
		_circleShape.rotate(1.f);

		if (_progressClock.getElapsedTime() > sf::seconds(2)) {
			_progressbar.setSize({ 500.f, 40.f });
		}
		_progressbar.addToProgress(0.005f);
	}

	void on_draw() override {
		_machine->draw();

		renderer().render();

		engine::Window::draw(_sprite);
		engine::Window::draw(_rectangleShape);
		engine::Window::draw(_circleShape);
		engine::Window::draw(_button);
		engine::Window::draw(_progressbar);
        engine::Window::draw(_button);
	}


private:
	engine::StateMachine _machine;
	engine::Sprite _sprite;
	engine::RectangleShape _rectangleShape;
	engine::CircleShape _circleShape;
	engine::Object _object;
	UI::Button _button{ &engine::Assets::getTexture("sample/Button"), &engine::Assets::getTexture("sample/ButtonHover")};
	sf::Clock _progressClock;
	UI::ProgressBar _progressbar{ {400.f, 20.f} };

	engine::Sprite _table, _boy, _girl, _grandpa, _dog;
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
        if(Settings::soundOn) music.play();
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
		return 0;
	}

	void handle_event(const sf::Event& event) override {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left) changeState("Physics");
        }
    }

	void on_update() override {
		if (_tempTime + _clock.getElapsedTime() >= sf::seconds(1) && _animation->start()) {
			_clock.restart();
			_animation->setDistance(_animation->getDistance() * -1.f);
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
};
