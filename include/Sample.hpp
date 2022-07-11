#pragma once

#include "engine/Sprite.hpp"
#include "engine/Assets.hpp"
#include "engine/State.hpp"
#include "engine/Window.hpp"

#include "GUI/Panel.hpp"


class SampleObject : public engine::Sprite {
public:
	SampleObject() {
		setTexture(engine::Assets::getTexture("myState/ThumbsUp"));
		setScale(0.1f, 0.1f);
		setOrigin(getLocalBounds().width / 2.f, getLocalBounds().height / 2.f);
		setPosition(engine::Window::getSize() / 2.f);
	}

	void update() override { /*empty*/ }
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
		_panel.setTexture(engine::Assets::getTexture("myState/ThumbsUp"));
		renderer().add_static(&_panel);
		_object.setPosition(_panel.getPosition() + sf::Vector2f{ 100.f, 100.f });
		renderer().add_static(&_object);
		_panel.attach_child(&_object);

		_sprite.setTexture(engine::Assets::getTexture("myState/ThumbsUp"));
		_sprite.setScale(0.1f, 0.1f);
		_sprite.setOrigin(_sprite.getLocalBounds().width / 2.f, _sprite.getLocalBounds().height / 2.f);
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
		_panel.rotate(-1);

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
	Panel _panel{ { 200, 200}, { 200, 200 }, 20 };
	SampleObject _object;
	sf::Sprite _sprite;
};
