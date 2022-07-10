#include "Object.hpp"
#include <numbers>

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

void Object::setPosition(float x, float y) {
	move(x - getPosition().x, y - getPosition().y);
}

void Object::setPosition(const sf::Vector2f& position) {
	move(position - getPosition());
}

void Object::setRotation(float angle) {
	rotate(angle - getRotation());
}

void Object::rotate(float angle) {
	Transformable::rotate(angle);

	if (_parent != nullptr) {
		sf::Vector2f offset = getPosition() - _parent->getPosition();
		setPosition(_parent->getPosition());
		const float pi = 3.14159265358979323846f;
		float newX = offset.x * cos(angle * pi / 180) - offset.y * sin(angle * pi / 180);
		float newY = offset.x * sin(angle * pi / 180) + offset.y * cos(angle * pi / 180);
		offset.x = newX;
		offset.y = newY;
		move(offset);
	}

	for (auto object : _children) {
		object->rotate(angle);
	}
}

void Object::setScale(float factorX, float factorY) {
	scale(factorX / getScale().x, factorY / getScale().y);
}

void Object::setScale(const sf::Vector2f& factors) {
	setScale(factors.x, factors.y);
}

void Object::setOrigin(float x, float y) {
	Transformable::setOrigin(x, y);
}

void Object::setOrigin(const sf::Vector2f& origin) {
	Transformable::setOrigin(origin);
}

const sf::Vector2f& Object::getPosition() const {
	return Transformable::getPosition();
}

float Object::getRotation() const {
	return Transformable::getRotation();
}

const sf::Vector2f& Object::getScale() const {
	return Transformable::getScale();
}

const sf::Vector2f& Object::getOrigin() const {
	return Transformable::getOrigin();
}

void Object::move(float offsetX, float offsetY) {
	Transformable::move(offsetX, offsetY);
	for (auto object : _children) {
		object->move(offsetX, offsetY);
	}
}

void Object::move(const sf::Vector2f& offset) {
	Transformable::move(offset);
	for (auto object : _children) {
		object->move(offset);
	}
}

void Object::scale(float factorX, float factorY) {
	Transformable::scale(factorX, factorY);

	if (_parent != nullptr) {
		sf::Vector2f distance = getPosition() - _parent->getPosition();

		distance.x *= factorX;
		distance.y *= factorY;

		distance -= getPosition() - _parent->getPosition();
		move(distance);
	}

	for (auto object : _children) {
		object->scale(factorX, factorY);
	}
}

void Object::scale(const sf::Vector2f& factor) {
	Transformable::scale(factor);
	
	if (_parent != nullptr) {
		sf::Vector2f distance = getPosition() - _parent->getPosition();

		distance.x *= factor.x;
		distance.y *= factor.y;

		distance -= getPosition() - _parent->getPosition();
		move(distance);
	}

	for (auto object : _children) {
		object->scale(factor);
	}
}

const sf::Transform& Object::getTransform() const {
	return Transformable::getTransform();
}

const sf::Transform& Object::getInverseTransform() const {
	return Transformable::getInverseTransform();
}