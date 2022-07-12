#include "Components/Physics.hpp"

#include "Object.hpp"

using namespace engine;

void Physics::update() {
	if (!_enabled) return;
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
	_object->move(_velocity * Timer::elapsedTime().asSeconds());
}

// Public methods used by the physics engine and at initialison

void Physics::apply_force(sf::Vector2f force) {
	_sumF += force;
}

void Physics::setForce(sf::Vector2f force) {
	_sumF = force;
}

void Physics::setVelocity(sf::Vector2f velocity) {
	_velocity = velocity;
}

void Physics::setMass(float mass) {
	_mass = mass;
}

void Physics::setFriction(float friction) {
	_friction = friction;
}