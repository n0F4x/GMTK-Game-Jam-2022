#include "engine/components/Physics.hpp"

#include "engine/Object.hpp"
#include "engine/Timer.hpp"

using namespace engine;


void Physics::update() {
	if (!isEnabled() || _mass <= 0) return;
	calc_acceleration();
	calc_velocity();
	apply_movement();
}

// Private methods used by update()

void Physics::calc_acceleration() {
	_acceleration = _sumF / _mass;
}

void Physics::calc_velocity() {
	_velocity += _acceleration * Timer::elapsedTime().asSeconds();
}

void Physics::apply_movement() {
	object()->move(_velocity * Timer::elapsedTime().asSeconds());
}

// Public methods used by the physics engine and at initialization

void Physics::setMass(float mass) {
	_mass = mass;
}
float Physics::getMass() const {
	return _mass;
}

void Physics::setFriction(float friction) {
	_friction = friction;
}
float Physics::getFriction() const {
	return _friction;
}

void Physics::setBounciness(float bounciness) {
	_bounciness = bounciness;
}
float Physics::getBounciness() const {
	return _bounciness;
}

void Physics::setVelocity(sf::Vector2f velocity) {
	_velocity = velocity;
}
sf::Vector2f Physics::getVelocity() const {
	return _velocity;
}

void Physics::apply_force(sf::Vector2f force) {
	_sumF += force;
}
void Physics::setForce(sf::Vector2f force) {
	_sumF = force;
}
sf::Vector2f Physics::getForce() const {
	return _sumF;
}
