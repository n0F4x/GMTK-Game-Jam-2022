#pragma once

#include <SFML/Graphics.hpp>
#include <list>

class Object : public sf::Drawable, public sf::Transformable {
private:
	Object *_parent = nullptr;
	std::list<Object*> _children;

public:
	virtual void update() { /*empty by default*/ }

	const Object* getParent() const { return _parent; }

	/*
	* @brief Methods creating or destroying parent - child connections (setting both sides in one call)
	*/
	void attachChild(Object* c) {
		if (_parent == c || c->getParent() == this) return;
		c->attachParent(this);
		_children.push_back(c);
	}
	void detachChild(Object* c) {
		_children.remove(c);
		if (c->getParent() != this) return;
		c->detachParent();
	}
	void attachParent(Object* p) {
		if (_parent == this) return;
		if (_parent != nullptr) detachParent();
		_parent = p;
		_parent->attachChild(this);
	}
	void detachParent() {
		Object* p = _parent;
		_parent = nullptr;
		if (p != nullptr) p->detachChild(this);
	}
};
