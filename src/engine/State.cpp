#include "State.hpp"

#include "StateMachine.hpp"
#include "engine/Window.hpp"

using namespace engine;


void State::changeState(const std::string_view& nextState) {
	_nextState = nextState;
	_isActive = false;
}


void State::addObject(Object* object) {
	_objects.push_back(object);
}

void State::update_objects() const {
	for (auto object : _objects) {
		object->update();
	}
}


Renderer& State::renderer() {
	return _renderer;
}


void State::addStateMachine(StateMachine* machine) {
	_stateMachine->addStore(&_store);
	_stateMachines.push_back(machine);
}


Store& State::store() {
	return _store;
}

Store* State::globalStore() {
	return _globalStore;
}



int State::initialize() {
	if (setup() != 0) {
		return 1;
	}

	for (const auto& machine : _stateMachines) {
		if (machine->initialize() != 0) {
			return 1;
		}
	}

	return 0;
}


void State::processChanges() const {
	for (auto stateMachine : _stateMachines) {
		stateMachine->processChanges();
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
