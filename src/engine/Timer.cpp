#include "Timer.hpp"

using namespace engine;


sf::Clock Timer::_clock;
sf::Time Timer::_elapsedTime;


sf::Time Timer::elapsedTime() {
	return _elapsedTime;
}

void Timer::restart() {
	_elapsedTime = _clock.restart();
}
