#pragma once

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include "engine/Component.hpp"
#include "engine/components/HitBox.hpp"


namespace engine {

	class State;

	class Collider : public Component {
	public:
		// If collisionLayer is 0 collides with everything, else collides with own layer (trigger does not affect physics/movement)
		// Position of rect must be relative to object's position (if no offset needed: top = left = 0)
		// If you want to live another day you don't set the object's origin if it has a collider.
		Collider(sf::FloatRect hitBox, bool trigger = false, int layer = 0);

		sf::FloatRect getHitBox();
		void setHitBox(sf::FloatRect hitBox);

		int getLayer() const;
		void setLayer(int layer);

		bool isTrigger() const;
		void setTrigger(bool isTrigger);

		bool collided_with(const Collider *collider) const;
		bool collided() const;
		void add_collision(Collider* collider);

	private:
		friend State;
		void clear_collisions();
		void resolve(Object* object2, sf::Time deltaTime, sf::FloatRect& newHitBox);


		///////////////
		// Variables //
		///////////////
		sf::FloatRect _hitBox;
		bool _trigger;
		int _collisionLayer;
		std::vector<Collider*> _collisions;
	};

}
