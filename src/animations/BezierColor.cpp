#include "animations/BezierColor.hpp"

#include "engine/Object.hpp"

using namespace animations;


sf::Color operator*(sf::Color color, float factor) {
	color.r = static_cast<sf::Uint8>((float)color.r * factor);
	color.g = static_cast<sf::Uint8>((float)color.g * factor);
	color.b = static_cast<sf::Uint8>((float)color.b * factor);
	color.a = static_cast<sf::Uint8>((float)color.a * factor);
	return color;
}


BezierColor::BezierColor(const sf::Vector2f& point1, const sf::Vector2f& point2) : _bezier{ point1, point2 }, _bezierCopy{ point1, point2 } {}


void BezierColor::update(sf::Time deltaTime) {
	if (isPaused()) {
		return;
	}

	_timePassed += deltaTime;

	if (_timePassed >= getTime()) {
		object()->setColor(*object()->getColor() + getColor() - _colored);

		stop();
		return;
	}

	float progress = _bezier.GetEasingProgress(_timePassed / getTime());

	// Color
	sf::Color colored = getColor() * progress;
	object()->setColor(*object()->getColor() + colored - _colored);
	_colored = colored;
}

void BezierColor::on_start() {
	_bezier = _bezierCopy;

	_timePassed = sf::Time::Zero;

	_colored = { 0, 0, 0, 0 };
}
