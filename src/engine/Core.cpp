#include "Core.hpp"

#include "Assets.hpp"
#include "Window.hpp"

// include States here:
#include "Sample.hpp"


using namespace engine;


StateMachine Core::_stateMachine;


int Core::initialize() {
	if (Assets::load_global() != 0) {
		return 1;
	}

	Window::open();

	// Add states here:
	_stateMachine.addState("Sample", std::make_unique<SampleState>());

	_stateMachine.setInitialState("<name of the first state>");

	if (_stateMachine.initialize() != 0) {
		return 1;
	}

	return 0;
}

void Core::game_loop() {
	sf::Event event;
	while (Window::isOpen()) {
		// Poll and handle events
		while (Window::poll_event(event)) {
			if (event.type == sf::Event::Closed) {
				Window::close();
			}
			_stateMachine->handle_event(event);
		}

		// Run general updates
		_stateMachine->update();

		// Draw to the window
		Window::clear();
		_stateMachine->draw();
		Window::display();

		// Set FPS (amount specified withing window)
		Window::lock_FPS();
	}
}


void Core::run() {
	if (initialize() != 0) {
		return;
	}

	game_loop();
}
