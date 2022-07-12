#pragma once

#include "Component.hpp"
#include "SFML/Graphics/Rect.hpp"

namespace engine {

	class Collider : public Component {
	public:
		// If collisionLayer is -1, collides with nothing, else if is 0 collides with everything, else collides with own layer
		Collider(sf::FloatRect rect, int layer = 0) : _rectangle(rect), _collisionLayer(layer) {}

		sf::FloatRect getRect() const;
		void setRect(sf::FloatRect);

		int getLayer() const;
		int setLayer(int layer);

	private:
		sf::FloatRect _rectangle;
		int _collisionLayer;
	};

}
