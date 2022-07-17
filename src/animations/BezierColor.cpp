#include "animations/BezierColor.hpp"

#include "engine/Object.hpp"

using namespace animations;


BezierColor::BezierColor(const sf::Vector2f& point1, const sf::Vector2f& point2) : _bezier{ point1, point2 }, _bezierCopy{ point1, point2 } {}


void BezierColor::update(sf::Time deltaTime) {
	if (isPaused()) {
		return;
	}

	_timePassed += deltaTime;

	if (_timePassed >= getTime()) {
		object()->setColor(engine::Color{ *object()->getColor() } + getColor() - _colored);

		stop();
		return;
	}

	float progress = _bezier.GetEasingProgress(_timePassed / getTime());

	// Color
	engine::Color colored = getColor() * progress;
	object()->setColor(engine::Color{ *object()->getColor() } + colored - _colored);
	_colored = colored;
}

void BezierColor::on_start() {
	_bezier = _bezierCopy;

	_timePassed = sf::Time::Zero;

	_colored = { 0, 0, 0, 0 };
}
