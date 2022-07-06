#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Object.hpp"


namespace engine {

	class State {
	public:
		///////////////
		// Game loop //
		///////////////
		virtual void handle_event(const sf::Event&) = 0;
		virtual void update() = 0;
		virtual void draw() = 0;

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
		// Object support //
		////////////////////
		void addObject(Object* object);

		void handle_event_objects(const sf::Event&) const;
		void update_objects() const;
		void draw_objects() const;

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
	};

}
