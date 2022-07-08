#pragma once

#include "engine/Object.hpp"
#include "engine/State.hpp"
#include "engine/Window.hpp"


class SampleObject : public Object {
public:
	SampleObject() {
		_shape.setOrigin(_shape.getGlobalBounds().width, _shape.getGlobalBounds().width);
		_shape.setPosition(
			engine::Window::getSize() / 2.f - sf::Vector2f{ _shape.getGlobalBounds().width, _shape.getGlobalBounds().height }
		);
	}

	void update() override { 
		switch (static_cast<int>(_clock.getElapsedTime().asSeconds()) % 4) {
		case 0:
			_shape.setPosition(
				engine::Window::getSize() / 2.f + sf::Vector2f{ _shape.getGlobalBounds().width, _shape.getGlobalBounds().height }
			);
			break;
		case 1:
			_shape.setPosition(
				engine::Window::getSize() / 2.f + sf::Vector2f{ -_shape.getGlobalBounds().width, _shape.getGlobalBounds().height }
			);
			break;
		case 2:
			_shape.setPosition(
				engine::Window::getSize() / 2.f + sf::Vector2f{ -_shape.getGlobalBounds().width, -_shape.getGlobalBounds().height }
			);
			break;
		case 3:
			_shape.setPosition(
				engine::Window::getSize() / 2.f + sf::Vector2f{ _shape.getGlobalBounds().width, -_shape.getGlobalBounds().height }
			);
			break;
		default:
			break;
		}
	}

private:
	// Overriding sf::Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(_shape);
	}


	// Variables //
	sf::CircleShape _shape{ 30.f, 50 };
	sf::Clock _clock;
};



class SampleState : public engine::State {
public:
	SampleState() {
		addObject(&_sampleObject);

		renderer().add_static(&_sampleObject);
	}

	void handle_event(const sf::Event&) override { /*empty*/ }

	void update() override {
		update_objects();
	}

	void draw() override {
		renderer().render();
	}


private:
	SampleObject _sampleObject;
};
