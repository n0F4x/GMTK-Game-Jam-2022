#include "StateMachine.hpp"

#include <iostream>

using namespace engine;


void StateMachine::addState(const std::string& name, std::unique_ptr<State> state) {
	if (auto [it, success] = _states.try_emplace(name, std::move(state)); success) {
		it->second->_stateMachine = this;
		it->second->_globalStore = _store;
	}
	else {
		std::cerr << "\nStateMachine: Failed adding state\"" << name << "', as one with the same name is already added.\n";
	}
}

void StateMachine::setInitialState(const std::string_view& name) {
	if (auto nextState = _states.find(name); nextState != _states.end()) {
		_currentState = nextState->second.get();
	}
	else {
		_currentState = _states.begin()->second.get();
	}
	_currentState->activate();
}


int StateMachine::initialize() {
	if (_states.empty()) {
		std::cerr << "\nStateMachine: [ERROR] Failed initializing - state machine has no states!";
		return 1;
	}

	for (const auto& [name, statePtr] : _states) {
		if (statePtr->initialize() != 0) {
			return 1;
		}
	}

	if (_currentState == nullptr) {
		_currentState = _states.begin()->second.get();
	}

	return 0;
}


void StateMachine::processChanges() {
	if (!_currentState->isActive()) {
		if (auto nextState = _states.find(_currentState->getNextState()); nextState != _states.end()) {
			_currentState->deactivate();
			_currentState = nextState->second.get();
		}
		else {
			std::cerr << "\nStateMachine: Failed changing state to \"" << _currentState->getNextState() << "\"\n";
		}
		_currentState->activate();
	}

	_currentState->processChanges();
}


State* StateMachine::operator->() {
	return _currentState;
}


void StateMachine::addStore(Store* store) {
	_store = store;
}
