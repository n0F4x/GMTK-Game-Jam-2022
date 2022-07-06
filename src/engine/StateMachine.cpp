#include "StateMachine.hpp"

#include <iostream>

using namespace engine;


bool StateMachine::isActive() const {
	return false;
}


void engine::StateMachine::addState(const std::string& name, std::unique_ptr<State> state) {
	_states.try_emplace(name, std::move(state));
}


void engine::StateMachine::init(const std::string_view& initState) {
	if (auto nextState = _states.find(initState); nextState != _states.end()) {
		_currentState = nextState->second.get();
	}
	else {
		_currentState = _states.begin()->second.get();
	}
	_currentState->activate();
}


void StateMachine::processChanges() {
	if (!_currentState->isActive()) {
		if (auto nextState = _states.find(_currentState->getNextState()); nextState != _states.end()) {
			_currentState = nextState->second.get();
		}
		else {
			std::cerr << "StateMachine: Failed changing state to \"" << _currentState->getNextState() << "\"\n";
		}
	}
	_currentState->activate();
}


State* StateMachine::operator->() {
	return _currentState;
}
