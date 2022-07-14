#include "engine/components/Collider.hpp"

#include <ranges>
#include "engine/Object.hpp"

using namespace engine;


Collider::Collider(sf::FloatRect hitBox, bool trigger, int layer) : _hitBox(hitBox), _trigger(trigger), _collisionLayer(layer) {}


sf::FloatRect Collider::getHitBox() {
	sf::FloatRect rectWithPosition = _hitBox;
	sf::Vector2f offset = object()->getPosition() - object()->getOrigin();

	rectWithPosition.left += offset.x;
	rectWithPosition.top += offset.y;

	return rectWithPosition;
}

void Collider::setHitBox(sf::FloatRect hitBox) {
	_hitBox = hitBox;
}

int Collider::getLayer() const {
	return _collisionLayer;
}

void Collider::setLayer(int layer) {
	_collisionLayer = layer;
}

bool Collider::isTrigger() const {
	return _trigger;
}
void Collider::setTrigger(bool isTrigger) {
	_trigger = isTrigger;
}

bool Collider::collided_with(const Collider *collider) const {
	return std::ranges::count(_collisions.begin(), _collisions.end(), collider) > 0;
}

void Collider::add_collision(Collider* collider) {
	_collisions.push_back(collider);
}

void Collider::clear_collisions() {
	_collisions.clear();
}
