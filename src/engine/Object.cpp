#include "engine/Object.hpp"

#include <numbers>
#include <cmath>

using namespace engine;

static const float PI = std::numbers::pi_v<float>;


///////////////
// Hierarchy //
///////////////
void Object::attach_child(Object* child) {
	if (child == this || child == _parent || child->_parent == this) {
		return;
	}

	child->detach_parent();

	child->_parent = this;
	_children.push_back(child);
}

void Object::detach_child(Object* child) {
	for (auto it = _children.begin(); it != _children.end(); it++) {
		if (*it == child) {
			_children.erase(it);
		}
	}
	child->_parent = nullptr;
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

bool Object::hasParent() const {
	return _parent != nullptr;
}

std::size_t Object::getChildrenCount() const {
    return _children.size();
}

Object *Object::getChild(size_t index) const {
    return _children.at(index);
}


////////////////
// Components //
////////////////
Animator* Object::setComponent(std::unique_ptr<Animator> component) {
	_animator = std::move(component);
	static_cast<Component*>(_animator.get())->_object = this;
	return _animator.get();
}
Collider* Object::setComponent(std::unique_ptr<Collider> component) {
	_collider = std::move(component);
	static_cast<Component*>(_collider.get())->_object = this;
	return _collider.get();
}
Physics* Object::setComponent(std::unique_ptr<Physics> component) {
	_physics = std::move(component);
	static_cast<Component*>(_physics.get())->_object = this;
	return _physics.get();
}

template<typename COMPONENT>
COMPONENT* Object::getComponent() {
	return nullptr;
}
template<>
Animator* Object::getComponent() {
	return _animator.get();
}
template<>
Collider* Object::getComponent() {
	return _collider.get();
}
template<>
Physics* Object::getComponent() {
	return _physics.get();
}


void Object::update() { /*currently empty*/ }


///////////////////
// Transformable //
///////////////////
void Object::setPosition(float x, float y) {
	auto newPos = sf::Vector2f{ x, y };

    for (auto sprite : _children) {
        sprite->move(newPos - getPosition());
    }

	_transformable.move(newPos - getPosition());
}

void Object::setPosition(const sf::Vector2f& position) {
    for (auto sprite : _children) {
        sprite->move(position - getPosition());
    }

	_transformable.move(position - getPosition());
}

void Object::setRotation(float angle) {
	rotate(angle - getRotation());
}

void Object::setScale(float factor) {
    scale(factor);
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

	for (auto sprite : _children) {
		sprite->move(offsetX, offsetY);
	}
}

void Object::move(const sf::Vector2f& offset) {
	_transformable.move(offset);

	for (auto sprite : _children) {
		sprite->move(offset);
	}
}

void Object::rotate(float angle) {
	_transformable.rotate(angle);

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

void Object::scale(float factor) {
    scale(factor, factor);
}

void Object::scale(float factorX, float factorY) {
	_transformable.scale(factorX, factorY);

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
