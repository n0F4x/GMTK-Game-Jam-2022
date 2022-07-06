#include "Engine.hpp"

#include "Sample.hpp"

using namespace engine;


void Engine::init() {
	_window.open();

	// Add states here:
	_stateMachine.addState("Sample", std::make_unique<SampleState>());

	_stateMachine.init("<name of the first state>");
}

void Engine::game_loop() {
	sf::Event event;
	while (_window.isOpen()) {
		// Poll and handle events
		while (_window.poll_event(event)) {
			if (event.type == sf::Event::Closed) {
				_window.close();
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
		_window.lock_FPS();
	}
}

void Engine::run() {
	init();

	game_loop();
}
