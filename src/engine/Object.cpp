#include "Object.hpp"


const Object* Object::getParent() const {
	return _parent;
}


void Object::attachChild(Object* child) {
	if (_parent == child || child->getParent() == this) return;
	child->attachParent(this);
	_children.push_back(child);
}
void Object::detachChild(Object* child) {
	_children.remove(child);
	if (child->getParent() != this) return;
	child->detachParent();
}
void Object::attachParent(Object* parent) {
	if (_parent == this) return;
	if (_parent != nullptr) detachParent();
	_parent = parent;
	_parent->attachChild(this);
}
void Object::detachParent() {
	Object* parent = _parent;
	_parent = nullptr;
	if (parent != nullptr) parent->detachChild(this);
}
