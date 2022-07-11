#include "Renderer.hpp"

#include "Window.hpp"

using namespace engine;


void Renderer::render() {
	for (auto drawable : _static) {
		Window::draw(*drawable);
	}

	for (auto drawable : _basic) {
		Window::draw(*drawable);
	}
	_basic.clear();

	for (auto drawable : _priority) {
		Window::draw(*drawable);
	}
	_priority.clear();
}


void Renderer::add_static(const sf::Drawable* drawable) {
	_static.push_back(drawable);
}

void Renderer::remove_static(const sf::Drawable* drawable) {
	if (auto searched = std::ranges::find(_static.begin(), _static.end(), drawable); searched != _static.end()) {
		_static.erase(searched);
	}
}

void Renderer::flush_static() {
	_static.clear();
}


void engine::Renderer::push_basic(const sf::Drawable* drawable) {
	_basic.push_back(drawable);
}


void engine::Renderer::push_priority(const sf::Drawable* drawable) {
	_priority.push_back(drawable);
}
