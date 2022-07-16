#include "states/menu/MenuState.hpp"

#include "engine/Window.hpp"


MenuState::MenuState() {
	_startButton.setCallback([this]() { changeState("Game"); });
	_startButton.setOrigin(_startButton.getSize() / 2.f);
	_startButton.scale(5);
	_startButton.setPosition(engine::Window::getSize() / 2.f);
	addObject(&_startButton);
	renderer().push_basic(&_startButton);
}


void MenuState::on_draw() {
	renderer().render();
}
