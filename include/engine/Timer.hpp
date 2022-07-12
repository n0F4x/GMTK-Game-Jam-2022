#pragma once

#include <SFML/System.hpp>


namespace engine {

	class Core;
	
	class Timer {
	public:
		static sf::Time elapsedTime();

	private:
		friend Core;
		static void restart();

		static sf::Clock _clock;
		static sf::Time _elapsedTime;
	};

}
