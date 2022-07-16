#include "animations/BezierScale.hpp"

#include "engine/Object.hpp"

using namespace animations;


BezierScale::BezierScale(const sf::Vector2f& point1, const sf::Vector2f& point2) : _bezier{ point1, point2 }, _bezierCopy{ point1, point2 } {}


void BezierScale::update(sf::Time deltaTime) {
	if (isPaused()) {
		return;
	}

	_timePassed += deltaTime;

	if (_timePassed >= getTime()) {
		object()->setScale(object()->getScale() + getScale() - _scaled);

		stop();
		return;
	}

	float progress = _bezier.GetEasingProgress(_timePassed / getTime());

	// Scale
	sf::Vector2f scaled = getScale() * progress;
	object()->setScale(object()->getScale() + scaled - _scaled);
	_scaled = scaled;
}

void BezierScale::on_start() {
	_bezier = _bezierCopy;

	_timePassed = sf::Time::Zero;

	_scaled = { 0.f, 0.f };
}
