#include "animations/BezierOutlineColor.hpp"

#include "engine/Object.hpp"
#include <iostream>

using namespace animations;


BezierOutlineColor::BezierOutlineColor(const sf::Vector2f& point1, const sf::Vector2f& point2) : _bezier{ point1, point2 }, _bezierCopy{ point1, point2 } {}


void BezierOutlineColor::update(sf::Time deltaTime) {
	if (isPaused()) {
		return;
	}

	_timePassed += deltaTime;

	if (_timePassed >= getTime()) {
		object()->setOutlineColor(engine::Color{ *object()->getOutlineColor() } + getOutlineColor() - _colored);

		stop();
		return;
	}

	float progress = _bezier.GetEasingProgress(_timePassed / getTime());

	// Color
	engine::Color colored = getOutlineColor() * progress;
	object()->setOutlineColor(engine::Color{ *object()->getOutlineColor() } + colored - _colored);
	_colored = colored;
}

void BezierOutlineColor::on_start() {
	if (object()->getOutlineColor() == nullptr) {
		std::cerr << "\nBezierOutlineColor: [Error] object has no outline color\n";
		stop();
	}

	_bezier = _bezierCopy;

	_timePassed = sf::Time::Zero;

	_colored = { 0, 0, 0, 0 };
}
