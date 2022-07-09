#pragma once

#include <string>
#include <map>
#include <memory>
#include "State.hpp"


namespace engine {

	/**
	 * @brief	StateMachines' main purpose is to be used inside States
	*/
	class StateMachine {
	public:
		/**
		 * @brief	Add ALL states BEFORE initializing.
		 * @param name 
		 * @param state 
		*/
		void addState(const std::string& name, std::unique_ptr<State> state);

		/**
		 * @brief	Sets the initial state of the machine. ONLY CALL FUNCTION BEFORE INITIALIZING MACHINE!
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
		 * @brief	Switches between states when the current state goes inactive. 
					Reactivates previous state as current, if the next one is not found.
					Then does the same with all state machines inside the current state.
		*/
		void processChanges();

		/**
		 * @return	The current active state.
		 *			Cannot return nullptr.
		*/
		State* operator->();


	protected:
		//////////////////
		// Data sharing //
		//////////////////
		friend State;
		void addStore(Store* store);



	private:
		//////////////
		// Variable //
		//////////////
		std::map<const std::string, std::unique_ptr<State>, std::less<>> _states;
		State* _currentState = nullptr;

		Store* _store = nullptr;
	};

}
