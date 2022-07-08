#include "Core.hpp"

#include "Assets.hpp"
#include "Window.hpp"

using namespace engine;


int Core::load_global_assets() const {
	if (Assets::load_global() != 0) {
		return 1;
	}
	return 0;
}


void Core::run() {
	Window::open();

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

		// Set FPS (amount specified withing window)
		Window::lock_FPS();
	}
}
