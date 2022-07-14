#include "Window.hpp"

#include <SFML/System.hpp>

using namespace engine;


//////////////
// Settings //
//////////////
sf::RenderWindow Window::_window;
sf::VideoMode Window::_videoMode = sf::VideoMode(1600, 900);
sf::String Window::_title = "Title";
sf::ContextSettings Window::_settings{
	/*depthBits*/			24,
	/*stencilBits*/			8,
	/*antialiasingLevel*/	0,
	/*majorVersion*/		1,
	/*minorVersion*/		1,
	/*attributeFlags*/		sf::ContextSettings::Attribute::Default,
	/*sRgbCapable*/			true
};
sf::Uint32 Window::_style = sf::Style::Default;
std::stack<sf::View> Window::_prevViews;
int Window::_FPSLimit = 120;
bool Window::_vSyncEnabled = true;
static const bool keyRepeatEnabled = false;


Window::Window() {
    _prevViews.push(_window.getDefaultView());
}


const sf::RenderWindow& Window::get() {
	return _window;
}

sf::Vector2f Window::getSize() {
	return sf::Vector2f{ sf::Vector2u{ _videoMode.width, _videoMode.height } };
}

sf::FloatRect Window::getBounds() {
	return sf::FloatRect{ { 0, 0 }, getSize() };
}

void Window::setView(sf::View view) {
    _prevViews.push(_window.getView());
    _window.setView(view);
}

void Window::resetToPreviousView() {
    _window.setView(_prevViews.top());
    _prevViews.pop();
}


void Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states) {
	_window.draw(drawable, states);
}


bool Window::getVSyncEnabled() {
    return _vSyncEnabled;
}

void Window::setVSyncEnabled(bool enabled) {
    if (_vSyncEnabled == enabled) return;

    _vSyncEnabled = enabled;

    if (_vSyncEnabled) {
        // disable framerate limit, vsync will limit it instead
        _window.setFramerateLimit(0);
    } else {
        _window.setFramerateLimit(_FPSLimit);
    }

    _window.setVerticalSyncEnabled(enabled);
}

int Window::getFPSLimit() {
    return _FPSLimit;
}

void Window::setFPSLimit(int limit) {
    _FPSLimit = limit;

    if (!_vSyncEnabled) {
        _window.setFramerateLimit(_FPSLimit);
    }
}


void Window::close() { _window.close(); }


void Window::open() {
	if (!_window.isOpen()) {
		_window.create(_videoMode, _title, _style, _settings);

		_window.setVerticalSyncEnabled(_vSyncEnabled);
		_window.setKeyRepeatEnabled(keyRepeatEnabled);
	}
}

bool Window::isOpen() {
	return _window.isOpen();
}

bool Window::poll_event(sf::Event& event) {
	return _window.pollEvent(event);
}

void Window::clear() { _window.clear(); }


void Window::display() {
    _window.display();
}
