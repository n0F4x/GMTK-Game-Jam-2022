#include "State.hpp"

#include "StateMachine.hpp"
#include "engine/Window.hpp"

using namespace engine;


int State::initialize() const {
	for (const auto& machine : _stateMachines) {
		if (machine->initialize() != 0) {
			return 1;
		}
	}

	return 0;
}


// DON'T MAKE THIS FUNCTION CONST
void State::update() {
	for (auto object : _objects) {
		object->update();
	}

	for (const auto& logic : _logicBlocks) {
		logic();
	}
}

void State::draw() {
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


void State::addStateMachine(StateMachine* machine) {
	_stateMachines.push_back(machine);
}


void State::addObject(Object* object) {
	_objects.push_back(object);
}


void State::addLogic(const std::function<void()>& logic) {
	_logicBlocks.push_back(logic);
}


Renderer& State::renderer() {
	return _renderer;
}
