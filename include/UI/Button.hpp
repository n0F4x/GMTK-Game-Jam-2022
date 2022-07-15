#pragma once

#include "engine/drawables/Sprite.hpp"
#include "engine/Assets.hpp"

#include <functional>
#include <utility>

namespace UI {

    class Button : public engine::Sprite {
    public:
        Button() = default;
        explicit Button(std::function<void()> callback) : _callback(std::move(callback)) {}

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
        bool _isPressed = false;
        bool _wasMouseButtonPressedLastFrame = false;
        std::function<void()> _callback;
    };

}