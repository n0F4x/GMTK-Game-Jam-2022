#include "Engine.hpp"

#include "Sample.hpp"

using namespace engine;


void Engine::initialize() {
	Window::open();

	// Add states here:
	_stateMachine.addState("Sample", std::make_unique<SampleState>());

	_stateMachine.initialize("<name of the first state>");
}

void Engine::game_loop() {
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


void Engine::run() {
	initialize();

	game_loop();
}
