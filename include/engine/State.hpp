#pragma once

#include <string>
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>
#include "Object.hpp"
#include "Renderer.hpp"


namespace engine {

	class State {
	public:
		///////////////
		// Game loop //
		///////////////
		virtual void handle_event(const sf::Event&) = 0;
		/**
		 * @brief	Updates the following in order:
		 *				_objects
		 *				_logicBlocks
		*/
		void update();
		/**
		 * @brief	Equivalent to calling Renderer::render() within the state
		*/
		void draw();


		//////////////////
		// StateMachine //
		//////////////////
		/**
		 * @brief	Sets _isActive to true
		*/
		void activate();
		bool isActive() const;
		const std::string& getNextState() const;


		virtual ~State() = default;

	protected:
		////////////////////
		// Object Support //
		////////////////////
		/**
		 * @brief	Adds object to state
		 * @param object 
		*/
		void addObject(Object* object);


		/////////////////
		// State Logic //
		/////////////////
		/**
		 * @brief	Adds a script that will be called with update.
		 * @param logic	Lambda function describing the relation of objects. Try making it simple. :)
		*/
		void addLogic(const std::function<void()>& logic);


		/////////////
		// Drawing //
		/////////////
		/**
		 * @brief	Call this to render within the state.
		 * @return	The state's renderer
		*/
		Renderer& renderer();


		//////////////////
		// StateMachine //
		//////////////////
		/**
		 * @brief	Tells statemachine to swap the active state with `processChanges()`
		 * @param nextState	The name of the next state
		*/
		void changeState(const std::string_view& nextState);


	private:
		bool _isActive = false;
		std::string _nextState;

		std::vector<Object*> _objects;
		std::vector<std::function<void()>> _logicBlocks;

		Renderer _renderer;
	};

}
