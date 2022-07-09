#pragma once

#include <list>
#include <SFML/Graphics.hpp>


class Object : public sf::Drawable, private sf::Transformable {
public:
	virtual void update() { /*empty by default*/ }

	/*
	* @brief Methods creating or destroying parent - child connections (setting both sides in one call)
	*/
	void attach_child(Object* child);
	void detach_child(Object* child);
	void attach_parent(Object* parent);
	void detach_parent();

    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& position);
    void setRotation(float angle);
    void setScale(float factorX, float factorY);
    void setScale(const sf::Vector2f& factors);
    void setOrigin(float x, float y);
    void setOrigin(const sf::Vector2f& origin);
    const sf::Vector2f& getPosition() const;
    float getRotation() const;
    const sf::Vector2f& getScale() const;
    const sf::Vector2f& getOrigin() const;
    void move(float offsetX, float offsetY);
    void move(const sf::Vector2f& offset);
    void rotate(float angle);
    void scale(float factorX, float factorY);
    void scale(const sf::Vector2f& factor);
    const sf::Transform& getTransform() const;
    const sf::Transform& getInverseTransform() const;

private:
	Object* _parent = nullptr;
	std::list<Object*> _children;
};
