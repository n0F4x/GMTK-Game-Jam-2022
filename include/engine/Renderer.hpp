#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <Object.hpp>


namespace engine {

	/**
	 * @brief	Designed to be used inside States
	 *			Utilize class for intricate drawing logic inside your state
	 *			Call your State's Renderer with `State::renderer()`
	*/
	class Renderer {
	public:
		/**
		 * @brief	Draws currently added objects to Window
		*/
		void render();

		// Static drawing - drawn first
		void add_static(const Object* object);
		void remove_static(const Object* object);
		void flush_static();

		// Dynamic drawing (gets flushed after each frame)
		// Basic - drawn after static
		// Priority - drawn after basic
		void push_basic(const Object* object);
		void push_priority(const Object* object);


	private:
		std::vector<const Object*> _static;
		std::vector<const Object*> _basic;
		std::vector<const Object*> _priority;
	};

}
