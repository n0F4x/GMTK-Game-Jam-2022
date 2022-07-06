#include "State.hpp"

#include "engine/Window.hpp"

using namespace engine;


void State::handle_event_objects(const sf::Event& event) const {
	for (const auto object : _objects) {
		object->handle_event(event);
	}
}

void State::update_objects() const {
	for (const auto object : _objects) {
		object->update();
	}
}

void State::draw_objects() const {
	for (const Object* object : _objects) {
		Window::draw(*object);
	}
}


void State::activate() {
	_isActive = true;
}

bool State::isActive() const {
	return _isActive;
}

const std::string& State::getNextState() const {
	return _nextState;
}


void State::changeState(const std::string_view& nextState) {
	_nextState = nextState;
	_isActive = false;
}


void engine::State::addObject(Object* object) {
	_objects.push_back(object);
}
