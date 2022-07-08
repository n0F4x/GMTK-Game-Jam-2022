#pragma once

#include <functional>
#include <SFML/Graphics.hpp>


namespace engine {

	class Core;

	/**
	 * @brief	Once a Window object is created (inside `Core::run()`), its static functions can be used anywhere in the project
	*/
	class Window {
	public:
		/////////
		// API //
		/////////
		/**
		 * @brief	Getter for inner window. Some SFML functions require window access
		 * @return	Inner static window
		*/
		static const sf::RenderWindow& window();
		/**
		 * @brief	Getter for the size of the window
		 * @return	The size of the window
		*/
		static sf::Vector2f getSize();
		/**
		 * @brief	Getter for the bounds of the window
		 * @return	The bounds of the window
		*/
		static sf::FloatRect getBounds();


		/////////////
		// Drawing //
		/////////////
		/**
		 * @brief	Clears the window
		*/
		static void clear();
		/**
		 * @brief	Draws object to window
		 * @param drawable	Object to be drawn
		 * @param states	Render states
		*/
		static void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
		/**
		 * @brief	Displays the contents of the window
		*/
		static void display();


		/////////////
		// EXITING //
		/////////////
		/**
		 * @brief	Closes the window (and the application).
		*/
		static void close();


	private:
		//////////
		// Core //
		//////////
		friend Core;
		/**
		 * @brief	Opens the window
		*/
		static void open();
		/**
		 * @brief	Checks whether the window is open. Starts timer for limiting FPS via `lock_FPS()`
		 * @return	True if the window is open
		*/
		static bool isOpen();
		/**
		 * @brief	Calls pollEvent on the inner sf::RenderWindow
		 * @param event	Reference to event where information will be distributed
		 * @return	True in case a new event was polled
		*/
		static bool poll_event(sf::Event& event);
		/**
		 * @brief	Locks the number of frames per second.
				Makes sure by causing potential delay that the right amount of time has passed since the last call of the function
		 * @param FPS	Frames per second. Default is 60
		*/
		static void lock_FPS();


		///////////////
		// Variables //
		///////////////
		static sf::RenderWindow _window;
		static std::function<sf::VideoMode()> _getVideoMode;
		static sf::String _title;
		static sf::ContextSettings _settings;
		static sf::Uint32 _style;
		static float _FPS;
		static sf::Clock _FPSClock;
	};

}