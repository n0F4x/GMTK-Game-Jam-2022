#pragma once

#include <SFML/Graphics.hpp>
#include <engine/Node.hpp>


class Panel : public engine::Node {
public:
	Panel(
		sf::Vector2f scale,
		sf::Vector2f position = sf::Vector2f{ 0, 0 },
		float borderWidth = 0,
		sf::Color backgroundColor = sf::Color{ 150, 150, 150, 200 },
		sf::Color borderColor = sf::Color{ 100, 100, 100, 250 },
		int borderDistortion = 0,
		bool borderFade = false
	);

	void apply_changes();

	void update() override;

	void setTexture(const sf::Texture& texture);


private:
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const final;



	///////////////
	// Variables //
	///////////////
	sf::VertexArray _vertices{ sf::Triangles, 42 };
	sf::Sprite _surface;
	sf::VertexArray _border{ sf::TriangleStrip, 16 };

	// Border width in pixels
	float _borderWidth;
	// Color distortion on the panel border
	int _borderDistortion;
	bool _borderFade;

	sf::Color _backgroundColor;
	sf::Color _borderColor;

	sf::Texture _backgroundTexture;
};
