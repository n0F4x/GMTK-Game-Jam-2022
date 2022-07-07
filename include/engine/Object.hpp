#pragma once

#include <list>
#include <SFML/Graphics.hpp>


class Object : public sf::Drawable, public sf::Transformable {
public:
	virtual void update() { /*empty by default*/ }

	const Object* getParent() const;

	/*
	* @brief Methods creating or destroying parent - child connections (setting both sides in one call)
	*/
	void attachChild(Object* child);
	void detachChild(Object* child);
	void attachParent(Object* parent);
	void detachParent();


private:
	Object* _parent = nullptr;
	std::list<Object*> _children;
};
