#include "Window.hpp"

#include <SFML/System.hpp>

using namespace engine;


//////////////
// Settings //
//////////////
sf::RenderWindow Window::_window;
std::function<sf::VideoMode()> Window::_getVideoMode = sf::VideoMode::getDesktopMode;
sf::String Window::_title = "Platforms";
sf::ContextSettings Window::_settings{
	/*depthBits*/			24,
	/*stencilBits*/			8,
	/*antialiasingLevel*/	0,
	/*majorVersion*/		1,
	/*minorVersion*/		1,
	/*attributeFlags*/		sf::ContextSettings::Attribute::Default,
	/*sRgbCapable*/			true
};
sf::Uint32 Window::_style = sf::Style::Fullscreen;
float Window::_FPS = 60.f;
sf::Clock Window::_FPSClock;
static const bool verticalSyncEnabled = true;
static const bool keyRepeatEnabled = false;



const sf::RenderWindow& engine::Window::window() {
	return _window;
}

sf::Vector2f Window::getSize() {
	return sf::Vector2f{ sf::Vector2u{ _getVideoMode().width, _getVideoMode().height } };
}

sf::FloatRect Window::getBounds() {
	return sf::FloatRect{ 0.f, 0.f, getSize().x, getSize().y };
}


void Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states) {
	_window.draw(drawable, states);
}


void Window::close() { _window.close(); }


void Window::open() {
	if (!_window.isOpen()) {
		_window.create(_getVideoMode(), _title, _style, _settings);

		_window.setVerticalSyncEnabled(verticalSyncEnabled);
		_window.setKeyRepeatEnabled(keyRepeatEnabled);
	}
}

bool Window::isOpen() {
	_FPSClock.restart();
	return _window.isOpen();
}

bool Window::poll_event(sf::Event& event) {
	return _window.pollEvent(event);
}

void Window::display() { _window.display(); }

void Window::clear() { _window.clear(); }

void Window::lock_FPS() {
	float elapsedTime = _FPSClock.getElapsedTime().asSeconds();

	if (elapsedTime < 1.f / _FPS) {
		sf::sleep(sf::seconds(1.f / _FPS - elapsedTime));
	}
}
