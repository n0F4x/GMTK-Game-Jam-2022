#include "UI/Button.hpp"

#include <utility>
#include "engine/Window.hpp"

using namespace UI;


Button::Button(std::function<void()> callback) : _callback(std::move(callback)) {}


void Button::setCallback(std::function<void()> callback) {
    _callback = std::move(callback);
}

bool Button::isPressed() const { 
    return _pressed;
}


void Button::update() {
    bool isAboveButton = getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(engine::Window::get())));
    bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    // if mouse is above the button and left-click was just clicked
    if (isAboveButton && !_wasButtonPressedLastFrame && isMousePressed) {
        _pressed = true;
        setTexture(_pressedTexture);
    }
    // if mouse is above the button and button was pressed and left-click is released
    else if (isAboveButton && _pressed && !isMousePressed) {
        _pressed = false;
        setTexture(_texture);
        _callback();
    }
    // otherwise if left-click is released
    else if (!isMousePressed) {
        _pressed = false;
        setTexture(_texture);
    }

    _wasButtonPressedLastFrame = isMousePressed;
}
