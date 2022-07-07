#pragma once

#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"


namespace engine {

	class Core {
	public:
		static void run();


	private:
		static int initialize();
		static void game_loop();

		static StateMachine _stateMachine;
	};

}