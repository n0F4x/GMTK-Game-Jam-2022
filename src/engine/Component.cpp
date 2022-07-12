#include "Component.hpp"

using namespace engine;


void Component::enable() {
	_enabled = true;
}

void Component::disable() {
	_enabled = false;
}

bool Component::is_enabled() const {
	return _enabled;
}
