#include "Core.hpp"

#include "Assets.hpp"
#include "Window.hpp"

using namespace engine;


Core::Core() {
	addStore(&_store);

	_loadingText.setString("Loading");
	_loadingFont.loadFromFile(Assets::ASSETS_PATH + "fonts/Canterbury.ttf");
	_loadingText.setFont(_loadingFont);
	_loadingText.setCharacterSize(100);
	sf::FloatRect textRect = _loadingText.getLocalBounds();
	_loadingText.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
	_loadingText.setPosition(Window::getSize() / 2.f);
	_loadingText.setFillColor(sf::Color::White);
}


int Core::setup() const {
	// Open window before loading assets duo to SFML bug: https://en.sfml-dev.org/forums/index.php?topic=25907.0
	Window::open();

	// Show a "Loading" sign until assets are being loaded
	Window::clear();
	Window::draw(_loadingText);
	Window::display();

	// Load assets
	if (Assets::load() != 0) {
		return 1;
	}

	return 0;
}


void Core::run() {
	// Game loop
	sf::Event event;
	while (Window::isOpen()) {
		// Switch between states
		processChanges();

		// Poll and handle events
		while (Window::poll_event(event)) {
			if (event.type == sf::Event::Closed) {
				Window::close();
			}
			operator->()->handle_event(event);
		}

		// Run general updates
		operator->()->update();

		// Draw to the window
		Window::clear();
		operator->()->draw();
		Window::display();

		// Set FPS (amount specified within window)
		Window::lock_FPS();
	}
}
