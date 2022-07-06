#pragma once

#include <SFML/Graphics.hpp>


class Object : public sf::Drawable, public sf::Transformable {
public:
	virtual void update() { /*empty by default*/ }
};
