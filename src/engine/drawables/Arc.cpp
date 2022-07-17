#include "engine/drawables/Arc.hpp"

#include <numbers>
#include <cmath>

static const float PI = std::numbers::pi_v<float>;

using namespace engine;


Arc::Arc(float radius, float spread, size_t pointCount) : _radius{ radius }, _pointCount{ pointCount } {
	setSpread(spread);
}

void Arc::setRadius(float radius) {
	_radius = radius;
	updateVertices();
}

float Arc::getRadius() const {
	return _radius;
}

void Arc::setSpread(float degrees) {
	_spread = degrees * PI / 180.f;
	updateVertices();
}

float Arc::getSpread() const {
	return _spread / PI * 180.f;
}

void Arc::setPointCount(size_t pointCount) {
	_pointCount = pointCount;
	updateVertices();
}

size_t Arc::getPointCount() const {
	return _pointCount;
}

sf::Vertex& Arc::getPoint(size_t index) {
	return _vertices[index];
}


void Arc::setFillColor(const sf::Color& color) {
	for (auto& vertex : _vertices) {
		vertex.color = color;
	}
}

const sf::Color* engine::Arc::getFillColor() const {
	return &_vertices[0].color;
}


void Arc::updateVertices() {
	_vertices.clear();
	_vertices.emplace_back();
	for (size_t i = 0; i < _pointCount; i++) {
		const float angle = (_angle - _spread / 2.f) + (static_cast<float>(i) * _spread) / static_cast<float>(_pointCount - 1);
		_vertices.emplace_back(_radius * sf::Vector2f{ std::cos(angle), std::sin(angle) });
	}
}

void Arc::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(_vertices.data(), _vertices.size(), sf::TriangleFan, states);
}
