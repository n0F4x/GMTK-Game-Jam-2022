#pragma once

#include "engine/Object.hpp"


namespace engine {

	class Text : public Object {
	public:
        Text() = default;
        Text(const sf::String& string, const sf::Font& font, unsigned int characterSize = 30);

        void setString(const sf::String& string);
        void setFont(const sf::Font& font);
        void setCharacterSize(unsigned int size);
        void setLineSpacing(float spacingFactor);
        void setLetterSpacing(float spacingFactor);
        void setStyle(sf::Uint32 style);
        void setFillColor(const sf::Color& color);
        void setOutlineColor(const sf::Color& color);
        void setOutlineThickness(float thickness);

        const sf::String& getString() const;
        const sf::Font* getFont() const;
        unsigned int getCharacterSize() const;
        float getLetterSpacing() const;
        float getLineSpacing() const;
        sf::Uint32 getStyle() const;
        const sf::Color& getFillColor() const;
        const sf::Color& getOutlineColor() const;
        float getOutlineThickness() const;

        sf::Vector2f findCharacterPos(std::size_t index) const;

        sf::FloatRect getLocalBounds() const;
        sf::FloatRect getGlobalBounds() const;

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        sf::Text _text;
	};

}