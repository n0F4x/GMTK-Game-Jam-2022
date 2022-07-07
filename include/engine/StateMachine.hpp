#pragma once

#include <string>
#include <map>
#include <memory>
#include "State.hpp"


namespace engine {

	class StateMachine {
	public:
		/**
		 * @brief	This one should be obvious. Please add states before initializing.
		 * @param name 
		 * @param state 
		*/
		void addState(const std::string& name, std::unique_ptr<State> state);

		/**
		 * @brief	Sets the initial state of the machine. ONLY call function before initializing machine!
		 * @param name
		*/
		void setInitialState(const std::string_view& name);

		/**
		 * @brief	Initializes states.
					MUST call function, ONLY after adding states. See 'engine/Engine.cpp': `init()`.
		 * @return	0 on success
		*/
		int initialize();

		/**
		 * @brief	Switches between states when needed
		*/
		void processChanges();

		/**
		 * @return	The current active state
		*/
		State* operator->();


	private:
		std::map<const std::string, std::unique_ptr<State>, std::less<>> _states;
		State* _currentState;
	};

}
