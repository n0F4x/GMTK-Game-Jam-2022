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

bool Collider::collided() const {
	return !_collisions.empty();
}

void Collider::add_collision(Collider* collider) {
	_collisions.push_back(collider);
}

void Collider::clear_collisions() {
	_collisions.clear();
}

void Collider::resolve(Object* object2, sf::Time deltaTime, sf::FloatRect& newHitBox) {
	Object* object1 = object();
	Physics* physics1 = object1->getComponent<Physics>();

	if (object() == object2) return;
	Collider* collider2 = object2->getComponent<Collider>();
	if (collider2 == nullptr) return;

	// Skip collision check if colliders are not on the same layer and neither is on the global collision layer
	if (getLayer() != collider2->getLayer() && getLayer() != 0 && collider2->getLayer() != 0) return;

	// Calculate the potential position of the second collider for the next frame
	sf::FloatRect hitBox2 = collider2->getHitBox();
	if (const Physics* physics2 = object2->getComponent<Physics>(); physics2 != nullptr) {
		hitBox2 = move(hitBox2, physics2->getVelocity() * deltaTime.asSeconds());
	}

	// Resolve collision
	if (newHitBox.intersects(hitBox2)) {
		// Add collider to collision list
		add_collision(collider2);

		// If both objects are physical and the first object has no parent, update physics parameters
		if (physics1 != nullptr && !isTrigger() && !collider2->isTrigger() && !object()->hasParent()) {
			sf::FloatRect rectCopy = newHitBox;
			newHitBox.left -= 2 * physics1->getVelocity().x * deltaTime.asSeconds();

			// If collision is not avoidable when the x axis is reverted, reverse y axis. Otheriwise, reverse x axis so no collision will happen.
			if (rectCopy.intersects(hitBox2)) {
				physics1->setVelocity(sf::Vector2f(physics1->getVelocity().x, -physics1->getVelocity().y * physics1->getBounciness()));
			}
			else {
				physics1->setVelocity(sf::Vector2f(-physics1->getVelocity().x * physics1->getBounciness(), physics1->getVelocity().y));
			}
		}
	}
}
