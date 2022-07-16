#include "Window.hpp"

#include <SFML/System.hpp>

using namespace engine;


//////////////
// Settings //
//////////////

sf::RenderWindow Window::_window;
sf::Vector2f Window::_renderResolution = { 1920, 1080 };
sf::VideoMode Window::_videoMode = sf::VideoMode::getFullscreenModes().at(0);
sf::String Window::_title = "Title";
sf::ContextSettings Window::_settings{
	/*depthBits*/			24,
	/*stencilBits*/			8,
	/*antialiasingLevel*/	8,
	/*majorVersion*/		1,
	/*minorVersion*/		1,
	/*attributeFlags*/		sf::ContextSettings::Attribute::Default,
	/*sRgbCapable*/			false
};
sf::Uint32 Window::_style = sf::Style::Fullscreen;
int Window::_FPSLimit = 120;
bool Window::_vSyncEnabled = true;
static const bool keyRepeatEnabled = false;


/////////
// API //
/////////
const sf::RenderWindow& Window::get() {
	return _window;
}

sf::Vector2f Window::getSize() {
	return _renderResolution;
}

sf::FloatRect Window::getBounds() {
	return sf::FloatRect{ { 0, 0 }, getSize() };
}


/////////////
// Drawing //
/////////////
void Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states) {
	_window.draw(drawable, states);
}


////////////////////
// Video settings //
////////////////////
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


/////////////
// EXITING //
/////////////
void Window::close() { _window.close(); }


//////////
// Core //
//////////
void Window::open() {
	if (!_window.isOpen()) {
		_window.create(_videoMode, _title, _style, _settings);

		_window.setVerticalSyncEnabled(_vSyncEnabled);
        if (!_vSyncEnabled) _window.setFramerateLimit(_FPSLimit);
		_window.setKeyRepeatEnabled(keyRepeatEnabled);
	}

    float scaleX = _renderResolution.x / _videoMode.width;
    float scaleY = _renderResolution.y / _videoMode.height;
    sf::View view { {_renderResolution.x / 2.f, _renderResolution.y / 2.f}, {_videoMode.width * std::max(scaleX, scaleY), _videoMode.height * std::max(scaleX, scaleY)} };
    _window.setView(view);
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
