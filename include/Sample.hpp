#pragma once

#include "engine/Object.hpp"
#include "engine/Assets.hpp"
#include "engine/State.hpp"
#include "engine/Window.hpp"

#include "GUI/Panel.hpp"


class SampleObject : public Object {
public:
	SampleObject() {
		_shape.setOrigin(_shape.getGlobalBounds().width / 2.f, _shape.getGlobalBounds().height / 2.f);
		_shape.setPosition(engine::Window::getSize() / 2.f);
		_shape.setTexture(&engine::Assets::getTexture("myState/ThumbsUp"));
	}

	void setPosition(const sf::Vector2f& amount) { _shape.setPosition(amount); }

	void update() override { /*empty*/ }

private:
	// Overriding sf::Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(_shape);
	}

	// Variables //
	sf::CircleShape _shape{ 30.f, 50 };
};


class SampleChildState : public engine::State {
public:
	SampleChildState() {
		renderer().add_static(&_sampleObject);
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
				_sampleObject.setPosition(engine::Window::getSize() / 2.f - sf::Vector2f{ 50, 0 });
			}
			else if (*globalStore()->get("side") == "Right") {
				_sampleObject.setPosition(engine::Window::getSize() / 2.f + sf::Vector2f{ 50, 0 });
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
	SampleObject _sampleObject;
	sf::Clock _clock;
};


class SampleState : public engine::State {
public:
	SampleState() {
		_panel.setTexture(engine::Assets::getTexture(""));
		renderer().add_static(&_panel);

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
	}

	void draw() override {
		renderer().render();
		_machine->draw();
	}


private:
	engine::StateMachine _machine;
	Panel _panel{ { 200, 200}, { 200, 200 }, 20 };
};
