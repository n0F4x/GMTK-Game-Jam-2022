#pragma once

#include <SFML/Graphics.hpp>


class Object : public sf::Drawable {
public:
	virtual void handle_event(const sf::Event&) { /*empty by default*/ }
	virtual void update() { /*empty by default*/ }
};
