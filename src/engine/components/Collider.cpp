#include <engine/components/Collider.hpp>

using namespace engine;

sf::FloatRect Collider::getRect() const {
	return _rectangle;
}

void Collider::setRect(sf::FloatRect rect) {
	_rectangle = rect;
}

int Collider::getLayer() const {
	return _collisionLayer;
}

int Collider::setLayer(int layer) {
	_collisionLayer = layer;
}
