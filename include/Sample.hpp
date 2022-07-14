#pragma once

#include "engine/Assets.hpp"
#include "engine/Window.hpp"
#include "engine/State.hpp"
#include "engine/StateMachine.hpp"
#include "engine/Object.hpp"
#include "engine/drawables/Sprite.hpp"
#include "engine/drawables/RectangleShape.hpp"
#include "engine/drawables/CircleShape.hpp"
#include "engine/drawables/Arc.hpp"


class SampleChildState : public engine::State {
public:
	explicit SampleChildState(const std::string_view& side) : _side{ side } {
		_sprite.setTexture(&engine::Assets::getTexture("myState/ThumbsUp"));
		_sprite.setSize({ 100.f, 100.f });
		renderer().add_static(&_sprite);

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

	void onUpdate() override {
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
		_sprite.setTexture(engine::Assets::getTexture("myState/ThumbsUp"));
		_sprite.setPosition(engine::Window::getSize() / 2.f + sf::Vector2f{ 0.f, -200.f });
		_sprite.scale(0.2f, 0.2f);
		_sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2);

		// RectangleShape
		_rectangleShape.setTexture(&engine::Assets::getTexture("myState/ThumbsUp"));
		_rectangleShape.setPosition(engine::Window::getSize() / 2.f + sf::Vector2f{ -400.f, 0.f });
		_rectangleShape.setSize({ 200.f, 200.f });
		_rectangleShape.setOutlineThickness(5);
		_rectangleShape.setOutlineColor(sf::Color::White);
		_rectangleShape.setOrigin(_rectangleShape.getSize() / 2.f);

		// CircleShape
		_circleShape.setTexture(&engine::Assets::getTexture("myState/ThumbsUp"));
		_circleShape.setPosition(engine::Window::getSize() / 2.f + sf::Vector2f{ 0.f, +200.f });
		_circleShape.setRadius(100.f);
		_circleShape.setOutlineThickness(5);
		_circleShape.setOutlineColor(sf::Color::White);
		_circleShape.setOrigin(_circleShape.getRadius(), _circleShape.getRadius());

		// Ball
		_ball.setPosition(engine::Window::getSize() / 2.f + sf::Vector2f{ 450.f, -200.f });
		_ball.setColor(sf::Color::Black);
		_ball.getPoint(0).color = sf::Color::Blue;

		// FlashLight
		_flashLight.setPosition(engine::Window::getSize() / 2.f + sf::Vector2f{ 400.f, 0.f });
		_flashLight.setColor(sf::Color::Black);
		_flashLight.getPoint(0).color = sf::Color{ 200, 230, 0, 255 };

		// Triangle
		_triangle.setPosition(engine::Window::getSize() / 2.f + sf::Vector2f{ 400.f, 200.f });
		_triangle.getPoint(0).color = sf::Color::Red;
		_triangle.getPoint(1).color = sf::Color::Yellow;
		_triangle.getPoint(2).color = sf::Color::Blue;

		addStateMachine(&_machine);

		_machine.addState("Child1", std::make_unique<SampleChildState>("Left"));
		_machine.addState("Child2", std::make_unique<SampleChildState>("Right"));
		_machine.setInitialState("Child1");	// this is the default

		store().add("restart", "true");
	}

	void handle_event(const sf::Event&) override { /*empty*/ }

	void onUpdate() override {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			changeState("Physics");
		}

		_machine->update();

		_sprite.rotate(-1);
		_rectangleShape.rotate(1);
		_circleShape.rotate(1);
	}

	void on_draw() override {
		_machine->draw();
		engine::Window::draw(_sprite);
		engine::Window::draw(_rectangleShape);
		engine::Window::draw(_circleShape);
		engine::Window::draw(_ball);
		engine::Window::draw(_flashLight);
		engine::Window::draw(_triangle);
	}


private:
	engine::StateMachine _machine;
	engine::Sprite _sprite;
	engine::RectangleShape _rectangleShape;
	engine::CircleShape _circleShape;
	engine::Object _object;
	engine::Arc _ball{ 80.f, 360.f };
	engine::Arc _flashLight{ 120.f, 60.f, 8 };
	engine::Arc _triangle{ 160.f, 60.f, 2 };
};


class PhysicsSampleState : public engine::State {
public:
	PhysicsSampleState() {
		renderer().add_static(&_sprite);

		_sprite.setOrigin(-500, -500);
		_sprite.scale(0.2f, 0.2f);
	}

	void handle_event(const sf::Event&) override { /*empty*/ }

	void onUpdate() override {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			changeState("Sample");
		}
	}

	void on_draw() override {
		renderer().render();
	}


private:
	engine::Sprite _sprite{ engine::Assets::getTexture("myState/ThumbsUp") };
};
