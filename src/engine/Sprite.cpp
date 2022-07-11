#include "Sprite.hpp"

using namespace engine;


Sprite::Sprite(const sf::Texture& texture) :_sprite{texture} {}

Sprite::Sprite(const sf::Texture& texture, const sf::IntRect& rectangle) : _sprite{texture, rectangle} {}


void Sprite::setTexture(const sf::Texture& texture, bool resetRect) {
	_sprite.setTexture(texture, resetRect);
}

void Sprite::setTextureRect(const sf::IntRect& rectangle) {
	_sprite.setTextureRect(rectangle);
}

void Sprite::setColor(const sf::Color& color) {
	_sprite.setColor(color);
}

const sf::Texture* Sprite::getTexture() const {
	return _sprite.getTexture();
}

const sf::IntRect& Sprite::getTextureRect() const {
	return _sprite.getTextureRect();
}

const sf::Color& Sprite::getColor() const {
	return _sprite.getColor();
}

sf::FloatRect Sprite::getLocalBounds() const {
	return _sprite.getLocalBounds();
}

sf::FloatRect Sprite::getGlobalBounds() const {
	return _sprite.getGlobalBounds();
}


void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();

	target.draw(_sprite, states);
}
