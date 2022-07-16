#pragma once

#include "engine/drawables/RectangleShape.hpp"

namespace UI {

    class ProgressBar : public engine::Object, public sf::Drawable {
    public:
        explicit ProgressBar(const sf::Vector2f& size);

        /**
         * @brief set the progress of the progressbar between 0.0f and 1.0f
         */
        void setProgress(const float amount);

        /**
         * @brief get the progress of the progressbar between 0.0f and 1.0f
         */
        float getProgress() const;

        /**
         * @brief add to the progress of the progressbar between 0.0f and 1.0f
         */
        void addToProgress(const float amount);

        /**
         * @brief set primary color of the progressbar (color of the whole bar above 20% progress)
         */
        void setPrimaryColor(const sf::Color color);

        /**
         * @brief set secondary color of the progressbar (color of the whole bar below 20% progress)
         */
        void setSecondaryColor(const sf::Color color);

        void setSize(const sf::Vector2f& size);

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    private:
        engine::RectangleShape _bar;
        sf::Vector2f _originalSize;
        float _progress = 1.0f;
        sf::Color _primaryColor = sf::Color::White;
        sf::Color _secondaryColor = sf::Color::White;
        void updateBar();
    };

}