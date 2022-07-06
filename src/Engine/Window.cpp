#include "Window.hpp"

#include <SFML/System.hpp>

using namespace engine;


sf::RenderWindow Window::_window;
std::function<sf::VideoMode()> Window::_getVideoMode = sf::VideoMode::getDesktopMode;


Window::Window() {
	_settings.depthBits = 24;
	_settings.stencilBits = 8;
	_settings.sRgbCapable = true;
}


const sf::RenderWindow& engine::Window::window() {
	return _window;
}

sf::Vector2f Window::getSize() {
	return sf::Vector2f{ sf::Vector2u{ _getVideoMode().width, _getVideoMode().height } };
}

sf::FloatRect Window::getBounds() {
	return sf::FloatRect{ 0.f, 0.f, getSize().x, getSize().y };
}


void Window::display() { _window.display(); }

void Window::clear() { _window.clear(); }

void Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states) {
	_window.draw(drawable, states);
}


void Window::open() const {
	if (!_window.isOpen()) {
		_window.create(_getVideoMode(), _title, _style, _settings);

		_window.setVerticalSyncEnabled(true);
		_window.setKeyRepeatEnabled(false);
	}
}

void Window::close() const { _window.close(); }

bool Window::isOpen() {
	_FPSClock.restart();
	return _window.isOpen();
}

bool Window::poll_event(sf::Event& event) const {
	return _window.pollEvent(event);
}

void Window::lock_FPS() const {
	float elapsedTime = _FPSClock.getElapsedTime().asSeconds();

	if (elapsedTime < 1.f / _FPS) {
		sf::sleep(sf::seconds(1.f / _FPS - elapsedTime));
	}
}
