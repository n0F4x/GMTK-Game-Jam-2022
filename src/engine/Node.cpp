#include "Node.hpp"

#include <numbers>
#include <cmath>

using namespace engine;

static const float PI = std::numbers::pi_v<float>;



void Node::attach_child(Node* child) {
	if (child == this || child == _parent || child->_parent == this) {
		return;
	}

	child->detach_parent();

	child->_parent = this;
	_children.push_back(child);
}

void Node::detach_child(Node* child) {
	if (_children.remove(child) > 0) {
		child->_parent = nullptr;
	}
}

void Node::attach_parent(Node* parent) {
	if (_parent == this) {
		return;
	}

	parent->attach_child(this);
}

void Node::detach_parent() {
	if (_parent != nullptr) {
		_parent->detach_child(this);
	}
}


///////////////////
// Transformable //
///////////////////

void Node::setPosition(float x, float y) {
	auto newPos = sf::Vector2f{ x, y };
	_transformable.move(newPos - getPosition());

	for (auto sprite : _children) {
		sprite->setPosition(x, y);
	}
}

void Node::setPosition(const sf::Vector2f& position) {
	_transformable.move(position - getPosition());

	for (auto sprite : _children) {
		sprite->setPosition(position);
	}
}

void Node::setRotation(float angle) {
	rotate(angle - getRotation());
}

void Node::setScale(float factorX, float factorY) {
	scale(factorX / getScale().x, factorY / getScale().y);
}

void Node::setScale(const sf::Vector2f& factors) {
	setScale(factors.x, factors.y);
}

void Node::setOrigin(float x, float y) {
	_transformable.setOrigin(x, y);
}

void Node::setOrigin(const sf::Vector2f& origin) {
	_transformable.setOrigin(origin);
}

const sf::Vector2f& Node::getPosition() const {
	return _transformable.getPosition();
}

float Node::getRotation() const {
	return _transformable.getRotation();
}

const sf::Vector2f& Node::getScale() const {
	return _transformable.getScale();
}

const sf::Vector2f& Node::getOrigin() const {
	return _transformable.getOrigin();
}

void Node::move(float offsetX, float offsetY) {
	_transformable.move(offsetX, offsetY);

	onMove(offsetX, offsetY);

	for (auto sprite : _children) {
		sprite->move(offsetX, offsetY);
	}
}

void Node::move(const sf::Vector2f& offset) {
	_transformable.move(offset);

	onMove(offset);

	for (auto sprite : _children) {
		sprite->move(offset);
	}
}

void Node::rotate(float angle) {
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

void Node::scale(float factorX, float factorY) {
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

void Node::scale(const sf::Vector2f& factor) {
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

const sf::Transform& Node::getTransform() const {
	return _transformable.getTransform();
}

const sf::Transform& Node::getInverseTransform() const {
	return _transformable.getInverseTransform();
}
