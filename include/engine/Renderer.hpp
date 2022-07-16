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

		// Drawn first
		void push_background(const sf::Drawable* drawable);
		void remove_background(const sf::Drawable* drawable);
		void flush_background();

		// Basic - drawn on top of background
		void push_basic(const sf::Drawable* drawable);
		void remove_basic(const sf::Drawable* drawable);
		void flush_basic();

		// Priority - drawn on top of basic
		void push_priority(const sf::Drawable* drawable);
		void remove_priority(const sf::Drawable* drawable);
		void flush_priority();


	private:
		std::vector<const sf::Drawable*> _static;
		std::vector<const sf::Drawable*> _basic;
		std::vector<const sf::Drawable*> _priority;
	};

}
