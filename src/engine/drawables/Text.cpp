#include "engine/drawables/Text.hpp"

using namespace engine;


Text::Text(const sf::String& string, const sf::Font& font, unsigned int characterSize) : _text{ string, font, characterSize } {}


void Text::setString(const sf::String& string) {
	_text.setString(string);
}

void Text::setFont(const sf::Font& font) {
	_text.setFont(font);
}

void Text::setCharacterSize(unsigned int size) {
	_text.setCharacterSize(size);
}

void Text::setLineSpacing(float spacingFactor) {
	_text.setLineSpacing(spacingFactor);
}

void Text::setLetterSpacing(float spacingFactor) {
	_text.setLetterSpacing(spacingFactor);
}

void Text::setStyle(sf::Uint32 style) {
	_text.setStyle(style);
}

void Text::setFillColor(const sf::Color& color) {
	_text.setFillColor(color);
}

void Text::setOutlineColor(const sf::Color& color) {
	_text.setOutlineColor(color);
}

void Text::setOutlineThickness(float thickness) {
	_text.setOutlineThickness(thickness);
}


const sf::String& Text::getString() const {
	return _text.getString();
}

const sf::Font* Text::getFont() const {
	return _text.getFont();
}

unsigned int Text::getCharacterSize() const {
	return _text.getCharacterSize();
}

float Text::getLetterSpacing() const {
	return _text.getLetterSpacing();
}

float Text::getLineSpacing() const {
	return _text.getLineSpacing();
}

sf::Uint32 Text::getStyle() const {
	return _text.getStyle();
}

const sf::Color& Text::getFillColor() const {
	return _text.getFillColor();
}

const sf::Color& Text::getOutlineColor() const {
	return _text.getOutlineColor();
}

float Text::getOutlineThickness() const {
	return _text.getOutlineThickness();
}


sf::Vector2f Text::findCharacterPos(std::size_t index) const {
	return _text.findCharacterPos(index);
}


sf::FloatRect Text::getLocalBounds() const {
	return _text.getLocalBounds();
}

sf::FloatRect Text::getGlobalBounds() const {
	return _text.getGlobalBounds();
}


void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(_text, states);
}
