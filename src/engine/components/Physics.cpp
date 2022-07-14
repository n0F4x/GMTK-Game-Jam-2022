#include "engine/components/Physics.hpp"

#include <algorithm>
#include "engine/Object.hpp"

using namespace engine;


Physics::Physics(float mass, float friction, float bounciness, sf::Vector2f initialVelocity) :
	_mass(mass), _friction(std::clamp(friction, 0.f, 1.f)), _bounciness(std::clamp(bounciness, 0.f, 1.f)), _velocity(initialVelocity) {};


void Physics::update(sf::Time deltaTime) {
	if (!isEnabled() || _mass <= 0 || object()->hasParent()) return;
	
	apply_movement();

	_deltaTime = deltaTime;
	calc_acceleration();
	calc_velocity();
}

// Private methods used by `update()` & `apply()` //

void Physics::calc_acceleration() {
	_acceleration = _sumF / _mass;
}

void Physics::calc_velocity() {
	_velocity += _acceleration * _deltaTime.asSeconds();
}

void Physics::apply_movement() {
	object()->move(_acceleration / 2.f * _deltaTime.asSeconds() * _deltaTime.asSeconds() + _velocity * _deltaTime.asSeconds());
}


// Public methods used by the physics engine and at initialization //

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
