#pragma once

#include <string>
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>
#include "Object.hpp"
#include "Renderer.hpp"


namespace engine {

	class StateMachine;

	/**
	 * @brief	Abstract class for describing a state inside a StateMachine.
	*/
	class State {
	public:
		///////////////
		// Game loop //
		///////////////
		/**
		 * @brief	Overwrite this function to handle events.
		 *			You can also handle events from inner state machines here.
		 * @param	sf::Event from 'main.cpp'
		*/
		virtual void handle_event(const sf::Event&) = 0;
		/**
		 * @brief	Override this function to update your object and state.
		 *			You can also update the states of your inner state machine here.
		 *			Use `update_objects()` for simple updates.
		*/
		virtual void update() = 0;
		/**
		 * @brief	Overwrite this function for drawing.
		 *			You can also draw stuff from inner state machines here.
		 *			Use `renderer().render()' if you want.
		*/
		virtual void draw() = 0;


		// Virtual destructor //
		virtual ~State() = default;

	protected:
		//////////////////
		// StateMachine //
		//////////////////
		/**
		 * @brief	Tells state machine to swap the active state with `processChanges()`
		 * @param nextState	The name of the next state
		*/
		void changeState(const std::string_view& nextState);


		//////////////////
		// Initializing //
		//////////////////
		/**
		 * @brief	Override this function for setting up your state.
		 *			This function will be called by `initialize()`
		 *			Print error message to std::cerr before returning with non-zero.
		 * @return	0 ON SUCCESS
		*/
		virtual int setup() { return 0; }


		////////////////////
		// Object Support //
		////////////////////
		/**
		 * @brief	Adds object to state.
		 * @param object 
		*/
		void addObject(Object* object);
		/**
		 * @brief	Calls `Object::update()` on all objects that you added via `addObject()`.
		*/
		void update_objects() const;


		/////////////
		// Drawing //
		/////////////
		/**
		 * @brief	Call this to render within the state.
		 * @return	The state's renderer
		*/
		Renderer& renderer();


		/////////////////////////
		// Inner StateMachines //	Each State will initialize its own machines BY DEFAULT.
		/////////////////////////
		/**
		 * @brief	CALL THIS FUNCTION ONLY INSIDE YOUR STATES CONSTRUCTOR.
		 * @param machine 
		*/
		void addStateMachine(StateMachine* machine);


	private:
		//////////////////
		// StateMachine //
		//////////////////
		friend StateMachine;

		/**
		 * @brief	Initializes inner StateMachines and calls `load_assets()'.
		 * @return	0 on success
		*/
		int initialize();
		/**
		 * @brief	Calls `processChanges()` for inner StateMachines
		*/
		void processChanges() const;

		/**
		 * @brief	Sets _isActive to true
		*/
		void activate();
		bool isActive() const;
		const std::string& getNextState() const;



		///////////////
		// Variables //
		///////////////
		bool _isActive = false;
		std::string _nextState;

		std::vector<Object*> _objects;
		std::vector<std::function<void()>> _logicBlocks;

		Renderer _renderer;

		std::vector<StateMachine*> _stateMachines;
	};

}
