#pragma once

#include <functional>
#include <stack>
#include <SFML/Graphics.hpp>

namespace engine {

	class Core;

	/**
	 * @brief	Once a Window object is created (inside `Core::run()`), its static functions can be used anywhere in the project
	*/
	class Window {
	public:
        Window();

		/////////
		// API //
		/////////
		/**
		 * @brief	Getter for inner window. Some SFML functions require window access
		 * @return	Inner static window
		*/
		static const sf::RenderWindow& get();
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

        ////////////
        // Camera //
        ////////////

        /**
         * @brief Sets the window's view (camera). Everything drawn after setting the view
         * will be drawn using this view. To revert to the previous view, use `resetToPreviousView()`.
         */
        static void setView(sf::View view);

        /**
         * @brief Sets the window's view (camera) to the window's default view (fill entire window).
         * To revert to the previous view, use `resetToPreviousView()`.
         */
        static void setDefaultView();

        /**
         * @brief Reverts the window's view (camera) to the previously used one.
         * This can be called as many times as the `setView`/`setDefaultView` functions have been called,
         * stepping to the previous view with each call.
         */
        static void resetToPreviousView();


		/////////////
		// Drawing //
		/////////////
		/**
		 * @brief	Draws object to window
		 * @param drawable	Object to be drawn
		 * @param states	Render states
		*/
		static void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);


        ////////////////////
        // Video settings //
        ////////////////////

        static bool getVSyncEnabled();

        static void setVSyncEnabled(bool enabled);

        static int getFPSLimit();

        static void setFPSLimit(int limit);


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
		 * @brief	Clears the window
		*/
		static void clear();
		/**
		 * @brief	Displays the contents of the window
		*/
		static void display();


		///////////////
		// Variables //
		///////////////
		static sf::RenderWindow _window;
		static sf::VideoMode _videoMode;
		static sf::String _title;
		static sf::ContextSettings _settings;
		static sf::Uint32 _style;
        static std::stack<sf::View> _prevViews;
		static int _FPSLimit;
        static bool _vSyncEnabled;
	};

}