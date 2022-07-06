#pragma once

#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "StateMachine.hpp"


namespace engine {

	class Engine {
	public:
		void run();


	private:
		void initialize();
		void game_loop();

		Window _window;
		StateMachine _stateMachine;
	};

}