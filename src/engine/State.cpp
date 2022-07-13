#include "State.hpp"

#include "StateMachine.hpp"
#include "engine/Window.hpp"

using namespace engine;


void State::update() {
	apply_physics();
	update_objects();
	onUpdate();
}


///////////////
// Protected //
///////////////

void State::changeState(const std::string_view& nextState) {
	_nextState = nextState;
	_isActive = false;
}


void State::addObject(Object* object) {
	_objects.push_back(object);
}

void State::update_objects() const {
	for (const auto& object : _objects) {
		object->update();
	}
}


Renderer& State::renderer() {
	return _renderer;
}


void State::addStateMachine(StateMachine* machine) {
	machine->addStore(&_store);
	_stateMachines.push_back(machine);
}


Store& State::store() {
	return _store;
}

Store* State::globalStore() {
	return _globalStore;
}


/////////////
// Private //
/////////////

void State::apply_physics() {
	sf::Time deltaTime = _physicsClock.restart();

	if (_physicsTime != sf::Time::Zero) {
		deltaTime += _physicsTime;
		_physicsTime = sf::Time::Zero;
	}

	for (auto object : _objects) {
		Collider* collider = object->getComponent<Collider>();
		if (collider == nullptr) continue;
		//clear list of collisions for frame
		collider->clear_collisions();

		//calculate the position of the first collider for the next frame
		sf::FloatRect rect = collider->getRect();
		Physics* physics = object->getComponent<Physics>();
		if (physics != nullptr) {
			sf::Vector2f movementInFrame = physics->getVelocity() * deltaTime.asSeconds();
			rect.left += movementInFrame.x;
			rect.top += movementInFrame.y;
		}

		for (auto object2 : _objects) {
			if (object == object2) continue;
			Collider* collider2 = object2->getComponent<Collider>();
			if (collider2 == nullptr) continue;
			//skip collision check if colliders are not on the same layer and neither is on the global collision layer
			if (collider->getLayer() != collider2->getLayer() && collider->getLayer() != 0 && collider2->getLayer() != 0) continue;

			//calculate the position of the second collider for the next frame
			sf::FloatRect rect2 = collider2->getRect();
			if (object2->getComponent<Physics>() != nullptr) {
				sf::Vector2f movementInFrame2 = object2->getComponent<Physics>()->getVelocity() * deltaTime.asSeconds();
				rect2.left += movementInFrame2.x;
				rect2.top += movementInFrame2.y;
			}

			//if collision is happened, resolve
			if (rect.intersects(rect2)) {
				//add collider to collision list
				collider->add_collision(collider2);
				//if both objects are physical and the first object is not a child update physics parameters
				if (object->getComponent<Physics>() != nullptr && !collider->is_trigger() && !collider2->is_trigger() && object->getParent() == nullptr) {
					sf::FloatRect rectCopy = rect;
					rect.left -= 2 * physics->getVelocity().x * deltaTime.asSeconds();
					//if collision is not avoidable if the x axis is reverted, then reverse y axis, else reverse x axis so no collision will happen
					if (rectCopy.intersects(rect2)) physics->setVelocity(sf::Vector2f(physics->getVelocity().x, -physics->getVelocity().y * physics->getBounciness()));
					else physics->setVelocity(sf::Vector2f(-physics->getVelocity().x * physics->getBounciness(), physics->getVelocity().y));
				}
			}

			//TODO: apply friction
		}
	}

	for (auto object : _objects) {
		if (auto physics = object->getComponent<Physics>(); physics != nullptr && physics->isEnabled()) {
			physics->update(deltaTime);
		}
	}
}

int State::initialize() {
	if (setup() != 0) {
		return 1;
	}

	for (const auto& machine : _stateMachines) {
		if (machine->initialize() != 0) {
			return 1;
		}
	}

	return 0;
}


void State::processChanges() const {
	for (auto stateMachine : _stateMachines) {
		stateMachine->processChanges();
	}
}


void State::activate() {
	_isActive = true;

	_physicsClock.restart();
	_animationsClock.restart();
}

void State::deactivate() {
	_physicsTime = _physicsClock.getElapsedTime();
	_animationsTime = _animationsClock.getElapsedTime();
}

bool State::isActive() const {
	return _isActive;
}

const std::string& State::getNextState() const {
	return _nextState;
}
