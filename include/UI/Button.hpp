#pragma once

#include <functional>
#include "engine/drawables/Sprite.hpp"
#include "engine/Assets.hpp"


namespace UI {

    class Button : public engine::Sprite {
    public:
        Button(const sf::Texture* texture, const sf::Texture* hoverTexture, std::function<void()> callback = std::function<void()>());

        /**
         * @brief sets the callback function of the button
         */
        void setCallback(std::function<void()> callback);

        /**
         * @brief returns true if the button is pressed / held down
         */
        bool isPressed() const;

        /**
         * @brief updates the button's internal state, calls the callback function if valid button press occurs
         */
        void update() override;


    private:
        bool _pressed = false;
        bool _wasButtonPressedLastFrame = false;
        std::function<void()> _callback;
        const sf::Texture* _texture;
        const sf::Texture* _hoverTexture;
        using engine::Sprite::setTexture;
    };

}