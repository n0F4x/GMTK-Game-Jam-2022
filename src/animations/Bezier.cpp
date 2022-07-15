#include "animations/Bezier.hpp"

#include "engine/Object.hpp"

using namespace animations;


void Ease::update(sf::Time deltaTime) {
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

void Ease::on_start() {
	_timePassed = sf::Time::Zero;
	_distanceTraveled = { 0.f, 0.f };
	_bezier = BezierEasing{ { 0.25f, 0.1f }, { 0.25f, 1.f } };
}
