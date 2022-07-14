#pragma once

#include <SFML/Graphics/Rect.hpp>


inline sf::FloatRect move(sf::FloatRect rect, const sf::Vector2f& amount) {
	rect.left += amount.x;
	rect.top += amount.y;
	return rect;
}
