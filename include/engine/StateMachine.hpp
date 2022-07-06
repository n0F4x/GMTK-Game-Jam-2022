#pragma once

#include <string>
#include <map>
#include <memory>
#include "State.hpp"


namespace engine {

	class StateMachine {
	public:
		void addState(const std::string& name, std::unique_ptr<State> state);

		/**
		 * @brief	Initializes current state. MUST call function, ONLY after adding states. See 'engine/Engine.cpp': `init()`.
		*/

		/**
		 * @brief	Sets initial state.
					MUST call function, ONLY after adding states. See 'engine/Engine.cpp': `init()`.
		 * @param initState 
		*/
		void initialize(const std::string_view& initState);

		/**
		 * @brief	Switches between states if needed
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
