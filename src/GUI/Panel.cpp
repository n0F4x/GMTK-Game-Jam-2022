#include "GUI/Panel.hpp"

void Panel::update() {
	//TODO update vertices on animation
}

void Panel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	int verticesToDraw = _border == 0 ? 6 : 42;
	target.draw(_vertices, verticesToDraw, sf::Triangles);
}

void Panel::calculateVertices() {
	sf::Vector2 pos = Object::getPosition();
	auto scaleHalf = sf::Vector2f(Object::getScale().x / 2, Object::getScale().y / 2);


	// Inside triangles
	_vertices[0].position = sf::Vector2f(-scaleHalf.x, scaleHalf.y) + pos;
	_vertices[1].position = sf::Vector2f(scaleHalf.x, scaleHalf.y) + pos;
	_vertices[2].position = sf::Vector2f(-scaleHalf.x, -scaleHalf.y) + pos;

	_vertices[3].position = sf::Vector2f(-scaleHalf.x, -scaleHalf.y) + pos;
	_vertices[4].position = sf::Vector2f(scaleHalf.x, scaleHalf.y) + pos;
	_vertices[5].position = sf::Vector2f(scaleHalf.x, -scaleHalf.y) + pos;

	for (size_t i = 0; i < 6; i++) _vertices[i].color = _backgroundColor;

	if (_border == 0) return;

	// Border corners
	_vertices[6].position = sf::Vector2f(-scaleHalf.x, scaleHalf.y) + pos;
	_vertices[7].position = sf::Vector2f(-scaleHalf.x - _border, scaleHalf.y) + pos;
	_vertices[8].position = sf::Vector2f(-scaleHalf.x, scaleHalf.y + _border) + pos;

	_vertices[9].position = sf::Vector2f(scaleHalf.x, scaleHalf.y) + pos;
	_vertices[10].position = sf::Vector2f(scaleHalf.x + _border, scaleHalf.y) + pos;
	_vertices[11].position = sf::Vector2f(scaleHalf.x, scaleHalf.y + _border) + pos;

	_vertices[12].position = sf::Vector2f(scaleHalf.x, -scaleHalf.y) + pos;
	_vertices[13].position = sf::Vector2f(scaleHalf.x + _border, -scaleHalf.y) + pos;
	_vertices[14].position = sf::Vector2f(scaleHalf.x, -scaleHalf.y - _border) + pos;

	_vertices[15].position = sf::Vector2f(-scaleHalf.x, -scaleHalf.y) + pos;
	_vertices[16].position = sf::Vector2f(-scaleHalf.x - _border, -scaleHalf.y) + pos;
	_vertices[17].position = sf::Vector2f(-scaleHalf.x, -scaleHalf.y - _border) + pos;

	// Border edges
	//(top)
	_vertices[18].position = sf::Vector2f(-scaleHalf.x, scaleHalf.y) + pos;
	_vertices[19].position = sf::Vector2f(scaleHalf.x, scaleHalf.y) + pos;
	_vertices[20].position = sf::Vector2f(-scaleHalf.x, scaleHalf.y + _border) + pos;

	_vertices[21].position = sf::Vector2f(-scaleHalf.x, scaleHalf.y + _border) + pos;
	_vertices[22].position = sf::Vector2f(scaleHalf.x, scaleHalf.y + _border) + pos;
	_vertices[23].position = sf::Vector2f(scaleHalf.x, scaleHalf.y) + pos;

	//(right)
	_vertices[24].position = sf::Vector2f(scaleHalf.x, scaleHalf.y) + pos;
	_vertices[25].position = sf::Vector2f(scaleHalf.x, -scaleHalf.y) + pos;
	_vertices[26].position = sf::Vector2f(scaleHalf.x + _border, -scaleHalf.y) + pos;

	_vertices[27].position = sf::Vector2f(scaleHalf.x + _border, -scaleHalf.y) + pos;
	_vertices[28].position = sf::Vector2f(scaleHalf.x + _border, scaleHalf.y) + pos;
	_vertices[29].position = sf::Vector2f(scaleHalf.x, scaleHalf.y) + pos;

	//(bottom)
	_vertices[30].position = sf::Vector2f(scaleHalf.x, -scaleHalf.y) + pos;
	_vertices[31].position = sf::Vector2f(-scaleHalf.x, -scaleHalf.y) + pos;
	_vertices[32].position = sf::Vector2f(scaleHalf.x, -scaleHalf.y - _border) + pos;

	_vertices[33].position = sf::Vector2f(scaleHalf.x, -scaleHalf.y - _border) + pos;
	_vertices[34].position = sf::Vector2f(-scaleHalf.x, -scaleHalf.y - _border) + pos;
	_vertices[35].position = sf::Vector2f(-scaleHalf.x, -scaleHalf.y) + pos;

	//(left)
	_vertices[36].position = sf::Vector2f(-scaleHalf.x, -scaleHalf.y) + pos;
	_vertices[37].position = sf::Vector2f(-scaleHalf.x, scaleHalf.y) + pos;
	_vertices[38].position = sf::Vector2f(-scaleHalf.x - _border, scaleHalf.y) + pos;

	_vertices[39].position = sf::Vector2f(-scaleHalf.x - _border, scaleHalf.y) + pos;
	_vertices[40].position = sf::Vector2f(-scaleHalf.x - _border, -scaleHalf.y) + pos;
	_vertices[41].position = sf::Vector2f(-scaleHalf.x, -scaleHalf.y) + pos;

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
		for (size_t i = 20; i < 41; i += 6)
		{
			_vertices[i].color.a = 0;
			_vertices[i + 1].color.a = 0;
			_vertices[i + 2].color.a = 0;
		}
	}
}