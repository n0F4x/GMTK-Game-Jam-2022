#include "Object.hpp"

#include <numbers>

static const float PI = std::numbers::pi_v<float>;



Object::Object(const sf::Texture& texture) : _sprite{ texture } {}
Object::Object(const sf::Texture& texture, const sf::IntRect& rectangle) : _sprite{ texture, rectangle } {}


void Object::attach_child(Object* child) {
	if (child == this || child == _parent || child->_parent == this) {
		return;
	}

	child->detach_parent();

	child->_parent = this;
	_children.push_back(child);
}

void Object::detach_child(Object* child) {
	if (_children.remove(child) > 0) {
		child->_parent = nullptr;
	}
}

void Object::attach_parent(Object* parent) {
	if (_parent == this) {
		return;
	}

	parent->attach_child(this);
}

void Object::detach_parent() {
	if (_parent != nullptr) {
		_parent->detach_child(this);
	}
}


///////////////////
// Transformable //
///////////////////

void Object::setPosition(float x, float y) {
	_sprite.setPosition(x, y);
	for (auto sprite : _children) {
		sprite->setPosition(x, y);
	}
}

void Object::setPosition(const sf::Vector2f& position) {
	_sprite.setPosition(position);
	for (auto sprite : _children) {
		sprite->setPosition(position);
	}
}

void Object::setRotation(float angle) {
	rotate(angle - getRotation());
}

void Object::setScale(float factorX, float factorY) {
	_sprite.setScale(factorX, factorY);
	for (auto sprite : _children) {
		auto origin = sprite->getOrigin();
		sprite->setOrigin(getPosition() - sprite->getPosition() + getOrigin());
		sprite->setScale(factorX, factorY);
		sprite->setOrigin(origin);
	}
}

void Object::setScale(const sf::Vector2f& factors) {
	_sprite.setScale(factors);
	for (auto sprite : _children) {
		auto origin = sprite->getOrigin();
		sprite->setOrigin(getPosition() - sprite->getPosition() + getOrigin());
		sprite->setScale(factors);
		sprite->setOrigin(origin);
	}
}

void Object::setOrigin(float x, float y) {
	_sprite.setOrigin(x, y);
}

void Object::setOrigin(const sf::Vector2f& origin) {
	_sprite.setOrigin(origin);
}

const sf::Vector2f& Object::getPosition() const {
	return _sprite.getPosition();
}

float Object::getRotation() const {
	return _sprite.getRotation();
}

const sf::Vector2f& Object::getScale() const {
	return _sprite.getScale();
}

const sf::Vector2f& Object::getOrigin() const {
	return _sprite.getOrigin();
}

void Object::move(float offsetX, float offsetY) {
	_sprite.move(offsetX, offsetY);
	for (auto sprite : _children) {
		sprite->move(offsetX, offsetY);
	}
}

void Object::move(const sf::Vector2f& offset) {
	_sprite.move(offset);
	for (auto sprite : _children) {
		sprite->move(offset);
	}
}

void Object::rotate(float angle) {
	_sprite.rotate(angle);
	for (auto child : _children) {
		sf::Vector2f offset = child->getPosition() - getPosition();
		child->setPosition(getPosition());
		float newX = offset.x * std::cos(angle * PI / 180) - offset.y * std::sin(angle * PI / 180);
		float newY = offset.x * std::sin(angle * PI / 180) + offset.y * std::cos(angle * PI / 180);
		offset.x = newX;
		offset.y = newY;
		child->move(offset);
	}
}

void Object::scale(float factorX, float factorY) {
	_sprite.scale(factorX, factorY);
	for (auto sprite : _children) {
		auto origin = sprite->getOrigin();
		sprite->setOrigin(getPosition() - sprite->getPosition() + getOrigin());
		sprite->scale(factorX, factorY);
		sprite->setOrigin(origin);
	}
}

void Object::scale(const sf::Vector2f& factor) {
	_sprite.scale(factor);
	for (auto sprite : _children) {
		auto origin = sprite->getOrigin();
		sprite->setOrigin(getPosition() - sprite->getPosition() + getOrigin());
		sprite->scale(factor);
		sprite->setOrigin(origin);
	}
}

const sf::Transform& Object::getTransform() const {
	return _sprite.getTransform();
}

const sf::Transform& Object::getInverseTransform() const {
	return _sprite.getInverseTransform();
}


////////////
// Sprite //
////////////

void Object::setTexture(const sf::Texture& texture, bool resetRect) {
	_sprite.setTexture(texture, resetRect);
}

void Object::setTextureRect(const sf::IntRect& rectangle) {
	_sprite.setTextureRect(rectangle);
}

void Object::setColor(const sf::Color& color) {
	_sprite.setColor(color);
}

const sf::Texture* Object::getTexture() const {
	return _sprite.getTexture();
}

const sf::IntRect& Object::getTextureRect() const {
	return _sprite.getTextureRect();
}

const sf::Color& Object::getColor() const {
	return _sprite.getColor();
}

sf::FloatRect Object::getLocalBounds() const {
	return _sprite.getLocalBounds();
}

sf::FloatRect Object::getGlobalBounds() const {
	return _sprite.getGlobalBounds();
}


void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_sprite, states);
}
