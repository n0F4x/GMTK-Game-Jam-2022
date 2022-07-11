#pragma once

#include <vector>
#include <SFML/Graphics.hpp>


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
		void add_static(const sf::Drawable* object);
		void remove_static(const sf::Drawable* object);
		void flush_static();

		// Dynamic drawing (gets flushed after each frame)
		// Basic - drawn after static
		// Priority - drawn after basic
		void push_basic(const sf::Drawable* object);
		void push_priority(const sf::Drawable* object);


	private:
		std::vector<const sf::Drawable*> _static;
		std::vector<const sf::Drawable*> _basic;
		std::vector<const sf::Drawable*> _priority;
	};

}
