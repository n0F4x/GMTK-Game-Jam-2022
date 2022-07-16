#include "animations/Bezier.hpp"

#include "engine/Object.hpp"

using namespace animations;


Bezier::Bezier(const sf::Vector2f& point1, const sf::Vector2f& point2) : _bezier{ point1, point2 }, _bezierCopy{point1, point2} {}


void Bezier::update(sf::Time deltaTime) {
	if (isPaused()) {
		return;
	}

	_timePassed += deltaTime;

	if (_timePassed >= getTime()) {
		object()->move(getDistance() - _distanceTraveled);

		stop();
		return;
	}

	float progress = _bezier.GetEasingProgress(_timePassed / getTime());

	// Move
	sf::Vector2f distanceTraveled = getDistance() * progress;
	object()->move(distanceTraveled - _distanceTraveled);
	_distanceTraveled = distanceTraveled;
}

void Bezier::on_start() {
	_bezier = _bezierCopy;

	_timePassed = sf::Time::Zero;
	
	_distanceTraveled = { 0.f, 0.f };
}
