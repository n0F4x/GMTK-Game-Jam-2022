#pragma once

#include <string>
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>
#include "Object.hpp"
#include "Renderer.hpp"
#include "Store.hpp"


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
		 * @brief	
		*/
		void update();
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


		////////////
		// Update //
		////////////
		/**
		 * @brief	Override this function to update your state.
		 *			This will be called by `update()`.
		 *			You can also update the states of your inner state machine(s) here.
		*/
		virtual void onUpdate() { /*empty by default*/ }


		/////////////
		// Drawing //
		/////////////
		/**
		 * @brief	Call this to render within the state.
		 * @return	The state's renderer
		*/
		Renderer& renderer();


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


		/////////////////////////
		// Inner StateMachines //	Each State will initialize its own machines BY DEFAULT.
		/////////////////////////
		/**
		 * @brief	CALL THIS FUNCTION ONLY INSIDE YOUR STATES CONSTRUCTOR.
		 *			This will set the State <-> StateMachine
		 * @param machine 
		*/
		void addStateMachine(StateMachine* machine);


		//////////////////
		// Data sharing //
		//////////////////
		/**
		 * @brief	Getter for the store of the state
		 * @return	The store of the state
		*/
		Store& store();
		/**
		 * @brief	Getter for the store of the State above the StateMachine
		 * @return	!!! nullptr if the State is not added to a StateMachine. !!!
		*/
		Store* globalStore();


	private:
		/////////////
		// Helpers //
		/////////////

		/**
		 * @brief	Updates the physics component of each object.
		*/
		void apply_physics();

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
		 * @brief	Sets _isActive to true and restarts clocks
		*/
		void activate();
		/**
		 * @brief	Saves elapsed clock times
		*/
		void deactivate();
		bool isActive() const;
		const std::string& getNextState() const;



		///////////////
		// Variables //
		///////////////
		StateMachine* _stateMachine = nullptr;

		bool _isActive = false;
		std::string _nextState;

		std::vector<Object*> _objects;
		std::vector<StateMachine*> _stateMachines;

		Renderer _renderer;
		Store _store;
		Store* _globalStore;

		sf::Clock _physicsClock;
		sf::Time _physicsTime;
		sf::Clock _animationsClock;
		sf::Time _animationsTime;
	};

}
