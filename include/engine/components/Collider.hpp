#pragma once

#include "engine/Component.hpp"
#include "SFML/Graphics/Rect.hpp"
#include <vector>

namespace engine {

	class Collider : public Component {
	public:
		// If collisionLayer is 0 collides with everything, else collides with own layer (trigger does not affect physics/movement)
		// Position of rect must be relative to object's position (if no offset needed: top = left = 0)
		Collider(sf::FloatRect hitBox, bool trigger = false, int layer = 0);

		sf::FloatRect getHitBox();
		void setHitBox(sf::FloatRect hitBox);

		int getLayer() const;
		void setLayer(int layer);

		bool isTrigger() const;
		void setTrigger(bool isTrigger);

		bool collided_with(const Collider *collider) const;
		void add_collision(Collider* collider);
		void clear_collisions();

	private:
		sf::FloatRect _hitBox;
		bool _trigger;
		int _collisionLayer;
		std::vector<Collider*> _collisions;
	};

}
