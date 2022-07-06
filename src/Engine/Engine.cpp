#include "Engine.hpp"

using namespace engine;


void Engine::run() {
	_window.open();

	sf::Event event;
	while (_window.isOpen()/* && _controller.isActive()*/) {
		// Poll events
		while (_window.poll_event(event)) {
			if (event.type == sf::Event::Closed) {
				_window.close();
			}
			//_controller->handleEvent(event);
		}

		//_controller->update();
		//_controller->render();

		_window.lock_FPS();
	}
}
