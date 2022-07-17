#include "animations/BezierFillColor.hpp"

#include "engine/Object.hpp"
#include <iostream>

using namespace animations;


BezierFillColor::BezierFillColor(const sf::Vector2f& point1, const sf::Vector2f& point2) : _bezier{ point1, point2 }, _bezierCopy{ point1, point2 } {}


void BezierFillColor::update(sf::Time deltaTime) {
	if (isPaused()) {
		return;
	}

	_timePassed += deltaTime;

	if (_timePassed >= getTime()) {
		object()->setFillColor(engine::Color{ *object()->getFillColor() } + getFillColor() - _colored);

		stop();
		return;
	}

	float progress = _bezier.GetEasingProgress(_timePassed / getTime());

	// Color
	engine::Color colored = getFillColor() * progress;
	object()->setFillColor(engine::Color{ *object()->getFillColor() } + colored - _colored);
	_colored = colored;
}

void BezierFillColor::on_start() {
	if (object()->getFillColor() == nullptr) {
		std::cerr << "\nBezierFillColor: [Error] object has no outline color\n";
		stop();
	}

	_bezier = _bezierCopy;

	_timePassed = sf::Time::Zero;

	_colored = { 0, 0, 0, 0 };
}
