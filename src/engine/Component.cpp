#include "Component.hpp"

using namespace engine;


void Component::enable() {
	_enabled = true;
}

void Component::disable() {
	_enabled = false;
}

bool Component::isEnabled() const {
	return _enabled;
}

Object* Component::object() {
	return _object;
}
