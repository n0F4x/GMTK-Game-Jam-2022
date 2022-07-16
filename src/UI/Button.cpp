#include "UI/Button.hpp"

#include <utility>
#include "engine/Window.hpp"

using namespace UI;


Button::Button(const sf::Texture* texture, const sf::Texture* hoverTexture, std::function<void()> callback)
    : Sprite{texture}, _callback(std::move(callback)), _texture(texture), _hoverTexture(hoverTexture) {}


void Button::setCallback(std::function<void()> callback) {
    _callback = std::move(callback);
}

bool Button::isPressed() const {
    return _pressed;
}

void Button::update() {
    bool isAboveButton = getGlobalBounds().contains(engine::Window::getMousePosition());
    bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    // if mouse is above the button
    if (isAboveButton) {
        setTexture(_hoverTexture);
        // left-click was just clicked
        if (!_wasButtonPressedLastFrame && isMousePressed) {
            _pressed = true;
        }
        // button was pressed and left-click is released
        else if (_pressed && !isMousePressed) {
            _pressed = false;
            _callback();
        }
    }
    // otherwise
    else {
        setTexture(_texture);
        // if left-click is released
        if (!isMousePressed) {
            _pressed = false;
        }
    }

    _wasButtonPressedLastFrame = isMousePressed;
}
