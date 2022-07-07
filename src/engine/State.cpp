#include "State.hpp"

#include "engine/Window.hpp"

using namespace engine;


void State::update() const {
	for (auto object : _objects) {
		object->update();
	}

	for (const auto& logic : _logicBlocks) {
		logic();
	}
}

void engine::State::draw() {
	_renderer.render();
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


void engine::State::addLogic(const std::function<void()>& logic) {
	_logicBlocks.push_back(logic);
}


Renderer& engine::State::renderer() {
	return _renderer;
}
