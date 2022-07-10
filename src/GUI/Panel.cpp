#include "GUI/Panel.hpp"

Panel::Panel(sf::Vector2f scale, sf::Vector2f position, float border, sf::Color backgroundColor, sf::Color borderColor, int borderDistortion, bool borderFade)
	: _border{ border }, _borderDistortion{ borderDistortion }, _borderFade{ borderFade }, _backgroundColor{ backgroundColor }, _borderColor{ borderColor }
{
	Object::setScale(scale);
	Object::setPosition(position);

	apply_changes();
}


void Panel::update() {
	//TODO update vertices on animation
}

void Panel::setTexture(const sf::Texture& texture) {
	_backgroundSprite.setTexture(texture);
}

const sf::Texture* Panel::getTexture() const {
	return _backgroundSprite.getTexture();
}


void Panel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	const size_t verticesToDraw = _border == 0 ? 6 : 42;

	std::array<sf::Vertex, 42> transformedVertices;
	for (size_t i = 0; i < verticesToDraw; i++) {
		transformedVertices[i].position = getTransform().transformPoint(_vertices[i].position);
		transformedVertices[i].color = _vertices[i].color;
	}

	if (getTexture()) {
		//TODO...
		target.draw(_backgroundSprite);
		//TODO draw
	}

	target.draw(transformedVertices.data(), verticesToDraw, sf::Triangles);
}


void Panel::apply_changes() {
	sf::Vector2f scale = getScale();

	// Inside triangles
	_vertices[0].position = sf::Vector2f{ -.5f, .5f };
	_vertices[1].position = sf::Vector2f{ .5f, .5f };
	_vertices[2].position = sf::Vector2f{ -.5f, -.5f };

	_vertices[3].position = sf::Vector2f{ -.5f, -.5f };
	_vertices[4].position = sf::Vector2f{ .5f, .5f };
	_vertices[5].position = sf::Vector2f{ .5f, -.5f };

	for (size_t i = 0; i < 6; i++) _vertices[i].color = _backgroundColor;

	if (_border == 0) return;

	// Border corners
	_vertices[6].position = sf::Vector2f{ -.5f, .5f };
	_vertices[7].position = sf::Vector2f{ -.5f - _border / scale.x, .5f };
	_vertices[8].position = sf::Vector2f{ -.5f, .5f + _border / scale.y };

	_vertices[9].position = sf::Vector2f{ .5f, .5f };
	_vertices[10].position = sf::Vector2f{ .5f + _border / scale.x, .5f };
	_vertices[11].position = sf::Vector2f{ .5f, .5f + _border / scale.y };

	_vertices[12].position = sf::Vector2f{ .5f, -.5f };
	_vertices[13].position = sf::Vector2f{ .5f + _border / scale.x, -.5f };
	_vertices[14].position = sf::Vector2f{ .5f, -.5f - _border / scale.y };

	_vertices[15].position = sf::Vector2f{ -.5f, -.5f };
	_vertices[16].position = sf::Vector2f{ -.5f - _border / scale.x, -.5f };
	_vertices[17].position = sf::Vector2f{ -.5f, -.5f - _border / scale.y };

	// Border edges
	//(top)
	_vertices[18].position = sf::Vector2f{ -.5f, .5f };
	_vertices[19].position = sf::Vector2f{ .5f, .5f };
	_vertices[20].position = sf::Vector2f{ -.5f, .5f + _border / scale.y };

	_vertices[21].position = sf::Vector2f{ -.5f, .5f + _border / scale.y };
	_vertices[22].position = sf::Vector2f{ .5f, .5f + _border / scale.y };
	_vertices[23].position = sf::Vector2f{ .5f, .5f };

	//(right)
	_vertices[24].position = sf::Vector2f{ .5f, .5f };
	_vertices[25].position = sf::Vector2f{ .5f, -.5f };
	_vertices[26].position = sf::Vector2f{ .5f + _border / scale.x, -.5f };

	_vertices[27].position = sf::Vector2f{ .5f + _border / scale.x, -.5f };
	_vertices[28].position = sf::Vector2f{ .5f + _border / scale.x, .5f };
	_vertices[29].position = sf::Vector2f{ .5f, .5f };

	//(bottom)
	_vertices[30].position = sf::Vector2f{ .5f, -.5f };
	_vertices[31].position = sf::Vector2f{ -.5f, -.5f };
	_vertices[32].position = sf::Vector2f{ .5f, -.5f - _border / scale.y };

	_vertices[33].position = sf::Vector2f{ .5f, -.5f - _border / scale.y };
	_vertices[34].position = sf::Vector2f{ -.5f, -.5f - _border / scale.y };
	_vertices[35].position = sf::Vector2f{ -.5f, -.5f };

	//(left)
	_vertices[36].position = sf::Vector2f{ -.5f, -.5f };
	_vertices[37].position = sf::Vector2f{ -.5f, .5f };
	_vertices[38].position = sf::Vector2f{ -.5f - _border / scale.x, .5f };

	_vertices[39].position = sf::Vector2f{ -.5f - _border / scale.x, .5f };
	_vertices[40].position = sf::Vector2f{ -.5f - _border / scale.x, -.5f };
	_vertices[41].position = sf::Vector2f{ -.5f, -.5f };

	if (_borderDistortion == 0)
		for (size_t i = 6; i < 42; i++) _vertices[i].color = _borderColor;
	else {
		sf::Color color;
		for (size_t i = 6; i < 42; i += 3) {
			color = _borderColor;
			color.r += _borderDistortion * (1 - 2 * (i % 2));
			color.g += _borderDistortion * (1 - 2 * (i % 2));
			color.b += _borderDistortion * (1 - 2 * (i % 2));
			_vertices[i].color = color;
			_vertices[i + 1].color = color;
			_vertices[i + 2].color = color;
		}
	}

	if (_borderFade) {
		for (size_t i = 7; i < 18; i++)
			if (i % 3 != 0) _vertices[i].color.a = 0;
		for (size_t i = 20; i < 41; i += 6) {
			_vertices[i].color.a = 0;
			_vertices[i + 1].color.a = 0;
			_vertices[i + 2].color.a = 0;
		}
	}
}