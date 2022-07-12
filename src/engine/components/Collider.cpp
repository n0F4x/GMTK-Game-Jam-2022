#include <engine/components/Collider.hpp>

using namespace engine;


Collider::Collider(sf::FloatRect rect, int layer) : _rectangle(rect), _collisionLayer(layer) {}


sf::FloatRect Collider::getRect() const {
	return _rectangle;
}

void Collider::setRect(sf::FloatRect rect) {
	_rectangle = rect;
}

int Collider::getLayer() const {
	return _collisionLayer;
}

void Collider::setLayer(int layer) {
	_collisionLayer = layer;
}
