#include "engine/components/Animation.hpp"

#include "engine/Object.hpp"

using namespace engine;


bool Animation::isActive() const {
	return _active;
}

bool Animation::isPaused() const {
	return _paused;
}

bool Animation::start() {
	if (_active) {
		return false;
	}
	on_start();
	_active = true;
	return true;
}

void Animation::stop() {
	_active = false;
	_paused = false;
}

void Animation::pause() {
	_paused = true;
}

void Animation::resume() {
	_paused = false;
}


void Animation::setTime(sf::Time duration) {
	_time = duration;
}

void Animation::setDistance(const sf::Vector2f& distance) {
	_distance = distance;
}

void Animation::setRotation(float rotation) {
	_rotation = rotation;
}

void Animation::setScale(const sf::Vector2f& scale) {
	_scale = scale;
}


void Animation::setTextures(const std::vector<const sf::Texture*>& textures) {
	_textures = textures;
}

void Animation::setTextureTime(sf::Time time) {
	_textureTime = time;
}

void Animation::setColor(const Color& color) {
	_color = color;
}


sf::Time Animation::getTime() const {
	return _time;
}

const sf::Vector2f& Animation::getDistance() const {
	return _distance;
}

float Animation::getRotation() const {
	return _rotation;
}

const sf::Vector2f& Animation::getScale() const {
	return _scale;
}

std::vector<const sf::Texture*>& Animation::getTextures() {
	return _textures;
}

sf::Time Animation::getTextureTime() const {
	return _textureTime;
}

const Color& Animation::getColor() const {
	return _color;
}


Object* Animation::object() {
	return _object;
}
