#include "StateMachine.hpp"

#include <iostream>

using namespace engine;


void StateMachine::addState(const std::string& name, std::unique_ptr<State> state) {
	_states.try_emplace(name, std::move(state));
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
	if (_currentState == nullptr) {
		if (!_states.empty()) {
			_currentState = _states.begin()->second.get();
		}
		else {
			std::cerr << "\nStateMachine: [ERROR] Failed initializing - state machine has not states!";
			return 1;
		}
	}

	for (const auto& [name, statePtr] : _states) {
		statePtr->initialize();
	}

	return 0;
}


void StateMachine::processChanges() {
	if (!_currentState->isActive()) {
		if (auto nextState = _states.find(_currentState->getNextState()); nextState != _states.end()) {
			_currentState = nextState->second.get();
		}
		else {
			std::cerr << "\nStateMachine: Failed changing state to \"" << _currentState->getNextState() << "\"\n";
		}
		_currentState->activate();
	}
}


State* StateMachine::operator->() {
	return _currentState;
}
