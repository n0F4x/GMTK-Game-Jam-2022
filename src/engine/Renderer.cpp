#include "Renderer.hpp"

#include "Window.hpp"

using namespace engine;


void Renderer::render() {
	for (auto object : _static) {
		Window::draw(*object);
	}

	for (auto object : _basic) {
		Window::draw(*object);
	}
	_basic.clear();

	for (auto object : _priority) {
		Window::draw(*object);
	}
	_priority.clear();
}


void Renderer::add_static(const Object* object) {
	_static.push_back(object);
}

void Renderer::remove_static(const Object* object) {
	if (auto searched = std::ranges::find(_static.begin(), _static.end(), object); searched != _static.end()) {
		_static.erase(searched);
	}
}

void Renderer::flush_static() {
	_static.clear();
}


void engine::Renderer::push_basic(const Object* object) {
	_basic.push_back(object);
}


void engine::Renderer::push_priority(const Object* object) {
	_priority.push_back(object);
}
