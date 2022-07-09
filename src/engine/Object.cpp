#include "Object.hpp"


void Object::attachChild(Object* child) {
	// TODO: Recursive parent/child relation check
	if (child == this) {
		return;
	}
	if (child == _parent) {
		return;
	}
	if (child->_parent == this) {
		return;
	}

	child->detachParent();

	child->_parent = this;
	_children.push_back(child);
}

void Object::detachChild(Object* child) {
	if (_children.remove(child) > 0) {
		child->_parent = nullptr;
	}
}

void Object::attachParent(Object* parent) {
	// TODO: Recursive parent/child relation check
	if (_parent == this) {
		return;
	}

	parent->attachChild(this);
}

void Object::detachParent() {
	if (_parent != nullptr) {
		_parent->detachChild(this);
	}
}
