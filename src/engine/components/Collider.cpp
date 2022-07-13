#include <engine/components/Collider.hpp>
#include "engine/Object.hpp"

using namespace engine;


Collider::Collider(sf::FloatRect rect, bool trigger, int layer) : _rectangle(rect), _isTrigger(trigger), _collisionLayer(layer) {}


sf::FloatRect Collider::getRect() {
	sf::FloatRect rectWithPosition = _rectangle;
	rectWithPosition.left += object()->getPosition().x;
	rectWithPosition.top += object()->getPosition().y;
	return rectWithPosition;
}

void Collider::setRect(sf::FloatRect rect) {
	_rectangle = rect;
}

int Collider::getLayer() const {
	return _collisionLayer;
}

void Collider::setLayer(int layer) {
	_collisionLayer = layer;
}

bool Collider::is_trigger() const {
	return _isTrigger;
}
void Collider::setIsTrigger(bool isTrigger) {
	_isTrigger = isTrigger;
}

bool Collider::collided_with(const Collider *collider) const {
	if (std::count(_collisions.begin(), _collisions.end(), collider)) {
		return true;
	}
	return false;
}

void Collider::add_collision(Collider* collider) {
	_collisions.push_back(collider);
}

void Collider::clear_collisions() {
	_collisions.clear();
}