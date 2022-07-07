#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include <engine/Object.hpp>


class Panel : public Object {
public:
	Panel(
		sf::Vector2f scale,
		sf::Vector2f position = sf::Vector2f{ 0, 0 },
		float border = 0,
		sf::Color backgroundColor = sf::Color{ 150, 150, 150, 200 },
		sf::Color borderColor = sf::Color{ 100, 100, 100, 250 },
		int borderDistortion = 0,
		bool borderFade = false
	);

	void calculateVertices();

	void update() override;


protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;


private:
	std::array<sf::Vertex, 42> _vertices;

	// Border size in pixels
	float _border;
	// Color distortion on the panel border
	int _borderDistortion;
	bool _borderFade;

	sf::Color _backgroundColor;
	sf::Color _borderColor;
};