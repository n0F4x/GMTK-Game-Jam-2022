#include "State.hpp"

#include "StateMachine.hpp"
#include "Window.hpp"

using namespace engine;

State::State() {
    _view.reset(Window::getBounds());
}

void State::update() {
    apply_physics();

    update_objects();
    onUpdate();

    update_physics();
}

void State::draw() {
    Window::setView(_view);
    on_draw();
    Window::resetToPreviousView();
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


Renderer& State::renderer() {
	return _renderer;
}

sf::View& State::camera() {
    return _view;
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

void State::update_physics() {
	sf::Time deltaTime = _physicsClock.restart();

	if (_physicsTime != sf::Time::Zero) {
		deltaTime += _physicsTime;
		_physicsTime = sf::Time::Zero;
	}

	// Resolve collisions
	for (auto object1 : _objects) {
		Collider* collider1 = object1->getComponent<Collider>();
		if (collider1 == nullptr) continue;

		// Clear list of collisions for frame
		collider1->clear_collisions();

		// Calculate the potential position of the first collider for the next frame
		sf::FloatRect hitBox1 = collider1->getHitBox();
		Physics* physics1 = object1->getComponent<Physics>();
		if (physics1 != nullptr) {
			sf::Vector2f movementInFrame = physics1->getVelocity() * deltaTime.asSeconds();
			hitBox1.left += movementInFrame.x;
			hitBox1.top += movementInFrame.y;
		}

		// Check for collisions
		for (auto object2 : _objects) {
			if (object1 == object2) continue;
			Collider* collider2 = object2->getComponent<Collider>();
			if (collider2 == nullptr) continue;

			// Skip collision check if colliders are not on the same layer and neither is on the global collision layer
			if (collider1->getLayer() != collider2->getLayer() && collider1->getLayer() != 0 && collider2->getLayer() != 0) continue;

			// Calculate the potential position of the second collider for the next frame
			sf::FloatRect hitBox2 = collider2->getHitBox();
			if (const Physics* physics2 = object2->getComponent<Physics>(); physics2 != nullptr) {
				sf::Vector2f movementInFrame2 = physics2->getVelocity() * deltaTime.asSeconds();
				hitBox2.left += movementInFrame2.x;
				hitBox2.top += movementInFrame2.y;
			}

			// Resolve collision
			if (hitBox1.intersects(hitBox2)) {
				// Add collider to collision list
				collider1->add_collision(collider2);

				// If both objects are physical and the first object has no parent, update physics parameters
				if (physics1 != nullptr && !collider1->isTrigger() && !collider2->isTrigger() && !object1->hasParent()) {
					sf::FloatRect rectCopy = hitBox1;
					hitBox1.left -= 2 * physics1->getVelocity().x * deltaTime.asSeconds();

					// If collision is not avoidable when the x axis is reverted, reverse y axis. Otheriwise, reverse x axis so no collision will happen.
					if (rectCopy.intersects(hitBox2)) {
						physics1->setVelocity(sf::Vector2f(physics1->getVelocity().x, -physics1->getVelocity().y * physics1->getBounciness()));
					}
					else {
						physics1->setVelocity(sf::Vector2f(-physics1->getVelocity().x * physics1->getBounciness(), physics1->getVelocity().y));
					}
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

void State::apply_physics() const {
	for (auto object : _objects) {
		if (auto physics = object->getComponent<Physics>(); physics != nullptr && physics->isEnabled()) {
			physics->apply();
		}
	}
}


void State::update_objects() const {
	for (const auto& object : _objects) {
		object->update();
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
