#pragma once

#include <SFML/Graphics.hpp>
#include "Window.hpp"


namespace engine {

	class Engine {
	public:
		void run();

	private:
		Window _window;
	};

}