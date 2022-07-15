#include "animations/Bezier.hpp"

#include "engine/Object.hpp"

using namespace animations;


Bezier::Bezier(const sf::Vector2f& point1, const sf::Vector2f& point2) : _bezier{ point1, point2 }, _bezierCopy{point1, point2} {}


void Bezier::update(sf::Time deltaTime) {
	_timePassed += deltaTime;

	if (isPaused()) {
		return;
	}
	if (_timePassed >= getTime()) {
		object()->move(getDistance() - _distanceTraveled);
		stop();
		return;
	}

	sf::Vector2f distanceTraveled = getDistance() * (_bezier.GetEasingProgress(_timePassed / getTime()));
	object()->move(distanceTraveled - _distanceTraveled);
	_distanceTraveled = distanceTraveled;
}

void Bezier::on_start() {
	_timePassed = sf::Time::Zero;
	_distanceTraveled = { 0.f, 0.f };
	_bezier = _bezierCopy;
}
