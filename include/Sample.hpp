#pragma once

#include "engine/Assets.hpp"
#include "engine/State.hpp"
#include "engine/Window.hpp"
#include "engine/Object.hpp"


class SampleChildState : public engine::State {
public:
	SampleChildState() {
		renderer().add_static(&_sprite);
	}

	int setup() override {
		if (globalStore()->get("side") == nullptr) {
			return 1;
		}
		return 0;
	}

	void handle_event(const sf::Event&) override { /*empty*/ }

	void update() override {
		if (*globalStore()->get("restart") == "true") {
			if (*globalStore()->get("side") == "Left") {
				_sprite.setPosition(engine::Window::getSize() / 2.f - sf::Vector2f{ 50, 0 });
			}
			else if (*globalStore()->get("side") == "Right") {
				_sprite.setPosition(engine::Window::getSize() / 2.f + sf::Vector2f{ 50, 0 });
			}
			_clock.restart();
			*globalStore()->get("restart") = "false";
		}

		if (_clock.getElapsedTime().asSeconds() > 1.f) {
			if (*globalStore()->get("side") == "Left") {
				*globalStore()->get("side") = "Right";
				changeState("Child2");
			}
			else if (*globalStore()->get("side") == "Right") {
				*globalStore()->get("side") = "Left";
				changeState("Child1");
			}
			*globalStore()->get("restart") = "true";
		}
	}

	void draw() override {
		renderer().render();
	}


private:
	sf::RectangleShape _sprite;
	sf::Clock _clock;
};


class SampleState : public engine::State {
public:
	SampleState() {
		_object.setComponent(std::make_unique<engine::Animator>());
		_object.getComponent<engine::Animator>();

		_sprite.setTexture(&engine::Assets::getTexture("myState/ThumbsUp"));
		_sprite.setSize({ 100.f, 100.f });
		_sprite.setOrigin(_sprite.getSize() / 2.f);
		_sprite.setPosition(engine::Window::getSize() / 2.f + sf::Vector2f{ 200.f, 0.f });

		addStateMachine(&_machine);

		_machine.addState("Child1", std::make_unique<SampleChildState>());
		_machine.addState("Child2", std::make_unique<SampleChildState>());
		_machine.setInitialState("Child1");	// this is the default

		store().add("side", "Right");
		store().add("restart", "true");
	}

	void handle_event(const sf::Event&) override { /*empty*/ }

	void update() override {
		_machine->update();

		_sprite.rotate(-1);
	}

	void draw() override {
		renderer().render();
		_machine->draw();
		engine::Window::draw(_sprite);
	}


private:
	engine::StateMachine _machine;
	sf::RectangleShape _sprite;
	engine::Object _object;
};
