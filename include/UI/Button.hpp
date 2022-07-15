#pragma once

#include <functional>
#include "engine/drawables/Sprite.hpp"
#include "engine/Assets.hpp"


namespace UI {

    class Button : public engine::Sprite {
    public:
        Button() = default;
        explicit Button(std::function<void()> callback);

        /**
         * @brief sets the callback fuction of the button
         */
        void setCallback(std::function<void()> callback);

        /**
         * @brief returns true if the button is pressed / held down
         */
        bool isPressed() const;

        /**
         * @brief updates the button's internal state, calls the callback fuction if valid button press occurs
         */
        void update() override;


    private:
        bool _pressed = false;
        bool _wasButtonPressedLastFrame = false;
        std::function<void()> _callback;
        const sf::Texture* _texture = &engine::Assets::getTexture("UI/Button");
        const sf::Texture* _pressedTexture = &engine::Assets::getTexture("UI/ButtonPressed");
    };

}