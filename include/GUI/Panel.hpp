#pragma once

#include <SFML/Graphics.hpp>
#include <Engine/Object.hpp>


class Panel : public Object {
private:
	sf::Vertex _vertices[42];

	// Border size in pixels
	float _border;
	// Color distortion on the panel border
	int _borderDistortion;
	bool _borderFade;

	sf::Color _backgroundColor;
	sf::Color _borderColor;

public:
	Panel(sf::Vector2f scale, sf::Vector2f position = sf::Vector2f(0,0), float border = 0, sf::Color backgroundColor = sf::Color(150,150,150,200), sf::Color borderColor = sf::Color(100, 100, 100, 250), int borderDistortion = 0, bool borderFade = false) 
		: _border(border), _borderDistortion(borderDistortion), _borderFade(borderFade), _backgroundColor(backgroundColor), _borderColor(borderColor) {
		Object::setScale(scale);
		Object::setPosition(position);

		calculateVertices();
	};

	void calculateVertices();

	void update() override;

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
};