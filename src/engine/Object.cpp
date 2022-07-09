#include "Object.hpp"


void Object::attachChild(Object* child) {
	if (child == this || child == _parent || child->_parent == this) {
		return;
	}

	child->detachParent();

	child->_parent = this;
	_children.push_back(child);
}

void Object::detachChild(Object* child) {
	if (auto it = std::ranges::find(_children, child); it != _children.end()) {
		child->_parent = nullptr;

		_children.erase(it);
	}
}

void Object::attachParent(Object* parent) {
	if (_parent == this) {
		return;
	}

	parent->attachChild(this);
}

void Object::detachParent() {
	if (_parent != nullptr) {
		_parent->detachChild(this);
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
	/*if (_parent == nullptr) Transformable::rotate(angle);
	else {
		sf::Transform t = getTransform();
		t.rotate(angle, _parent->getOrigin());
	}*/
	Transformable::rotate(angle);
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