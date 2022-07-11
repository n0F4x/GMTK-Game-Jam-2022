#include "Object.hpp"

#include <numbers>
#include <cmath>

using namespace engine;

static const float PI = std::numbers::pi_v<float>;



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
	auto newPos = sf::Vector2f{ x, y };
	_transformable.move(newPos - getPosition());

	for (auto sprite : _children) {
		sprite->setPosition(x, y);
	}
}

void Object::setPosition(const sf::Vector2f& position) {
	_transformable.move(position - getPosition());

	for (auto sprite : _children) {
		sprite->setPosition(position);
	}
}

void Object::setRotation(float angle) {
	rotate(angle - getRotation());
}

void Object::setScale(float factorX, float factorY) {
	scale(factorX / getScale().x, factorY / getScale().y);
}

void Object::setScale(const sf::Vector2f& factors) {
	setScale(factors.x, factors.y);
}

void Object::setOrigin(float x, float y) {
	_transformable.setOrigin(x, y);
}

void Object::setOrigin(const sf::Vector2f& origin) {
	_transformable.setOrigin(origin);
}

const sf::Vector2f& Object::getPosition() const {
	return _transformable.getPosition();
}

float Object::getRotation() const {
	return _transformable.getRotation();
}

const sf::Vector2f& Object::getScale() const {
	return _transformable.getScale();
}

const sf::Vector2f& Object::getOrigin() const {
	return _transformable.getOrigin();
}

void Object::move(float offsetX, float offsetY) {
	_transformable.move(offsetX, offsetY);

	onMove(offsetX, offsetY);

	for (auto sprite : _children) {
		sprite->move(offsetX, offsetY);
	}
}

void Object::move(const sf::Vector2f& offset) {
	_transformable.move(offset);

	onMove(offset);

	for (auto sprite : _children) {
		sprite->move(offset);
	}
}

void Object::rotate(float angle) {
	_transformable.rotate(angle);

	onRotate(angle);

	for (auto child : _children) {
		child->rotate(angle);

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
	_transformable.scale(factorX, factorY);

	onScale(factorX, factorY);

	for (auto sprite : _children) {
		sprite->scale(factorX, factorY);

		sf::Vector2f distance = sprite->getPosition() - getPosition();
		distance.x *= factorX;
		distance.y *= factorY;
		distance -= sprite->getPosition() - getPosition();
		sprite->move(distance);
	}
}

void Object::scale(const sf::Vector2f& factor) {
	_transformable.scale(factor);

	onScale(factor);

	for (auto sprite : _children) {
		sprite->scale(factor);

		sf::Vector2f distance = sprite->getPosition() - getPosition();
		distance.x *= factor.x;
		distance.y *= factor.y;
		distance -= sprite->getPosition() - getPosition();
		sprite->move(distance);
	}
}

const sf::Transform& Object::getTransform() const {
	return _transformable.getTransform();
}

const sf::Transform& Object::getInverseTransform() const {
	return _transformable.getInverseTransform();
}
