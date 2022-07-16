#include "engine/Renderer.hpp"

#include "engine/Window.hpp"

using namespace engine;


void Renderer::render() {
	for (auto drawable : _static) {
		Window::draw(*drawable);
	}

	for (auto drawable : _basic) {
		Window::draw(*drawable);
	}

	for (auto drawable : _priority) {
		Window::draw(*drawable);
	}
}


void Renderer::push_background(const sf::Drawable* drawable) {
	_static.push_back(drawable);
}

void Renderer::remove_background(const sf::Drawable* drawable) {
	if (auto searched = std::ranges::find(_static.begin(), _static.end(), drawable); searched != _static.end()) {
		_static.erase(searched);
	}
}

void Renderer::flush_background() {
	_static.clear();
}


void Renderer::push_basic(const sf::Drawable* drawable) {
	_basic.push_back(drawable);
}

void Renderer::remove_basic(const sf::Drawable* drawable) {
	if (auto searched = std::ranges::find(_basic.begin(), _basic.end(), drawable); searched != _basic.end()) {
		_basic.erase(searched);
	}
}

void Renderer::flush_basic() {
	_basic.clear();
}


void Renderer::push_priority(const sf::Drawable* drawable) {
	_priority.push_back(drawable);
}

void Renderer::remove_priority(const sf::Drawable* drawable) {
	if (auto searched = std::ranges::find(_priority.begin(), _priority.end(), drawable); searched != _priority.end()) {
		_priority.erase(searched);
	}
}

void Renderer::flush_priority() {
	_priority.clear();
}
