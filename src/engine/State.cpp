#include "engine/State.hpp"

#include "engine/StateMachine.hpp"
#include "engine/Window.hpp"

using namespace engine;


///////////////
// Game loop //
///////////////
void State::update() {
    update_physics();
	update_animations();

	on_update();

    update_objects();
}

void State::draw() {
    on_draw();
}


///////////////
// Protected //
///////////////
//////////////////
// StateMachine //
//////////////////
void State::changeState(const std::string_view& nextState) {
	_nextState = nextState;
	_isActive = false;
}


/////////////
// Drawing //
/////////////
Renderer& State::renderer() {
	return _renderer;
}


////////////////////
// Object Support //
////////////////////
void State::addObject(Object* object) {
    _objects.push_back(object);
}


/////////////////////////
// Inner StateMachines //
/////////////////////////
void State::addStateMachine(StateMachine* machine) {
	machine->addStore(&_store);
	_stateMachines.push_back(machine);
}


//////////////////
// Data sharing //
//////////////////
Store& State::store() {
	return _store;
}

Store* State::globalStore() {
	return _globalStore;
}


/////////////
// Private //
/////////////

void State::update_objects() const {
	for (const auto& object : _objects) {
		object->update();
	}
}

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
		if (const Physics* physics1 = object1->getComponent<Physics>(); physics1 != nullptr) {
			hitBox1 = move(hitBox1, physics1->getVelocity() * deltaTime.asSeconds());
		}

		// Check for collisions
		for (auto object2 : _objects) {
			collider1->resolve(object2, deltaTime, hitBox1);
		}
	}

	// Update physics
	for (auto object : _objects) {
		if (auto physics = object->getComponent<Physics>(); physics != nullptr && physics->isEnabled()) {
			physics->update(deltaTime);
		}
	}
}

void State::update_animations() {
	sf::Time deltaTime = _animationsClock.restart();

	if (_animationsTime != sf::Time::Zero) {
		deltaTime += _animationsTime;
		_animationsTime = sf::Time::Zero;
	}

	for (auto object : _objects) {
		if (auto animator = object->getComponent<Animator>(); animator != nullptr && animator->isEnabled()) {
			animator->animate(deltaTime);
		}
	}
}


//////////////////
// StateMachine //
//////////////////
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

	on_activate();

    for (auto machine : _stateMachines) {
        machine->operator->()->activate();
    }
}

void State::deactivate() {
	_physicsTime = _physicsClock.getElapsedTime();
	_animationsTime = _animationsClock.getElapsedTime();

	on_deactivate();

	for (auto machine : _stateMachines) {
		machine->operator->()->deactivate();
	}
}

bool State::isActive() const {
	return _isActive;
}

const std::string& State::getNextState() const {
	return _nextState;
}
