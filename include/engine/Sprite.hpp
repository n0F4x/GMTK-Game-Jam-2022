#pragma once

#include "Object.hpp"


namespace engine {

	/**
	 * @brief   Implementing sprite based on sf::Sprite to support Object hierarchy.
	*/
	class Sprite : public Object {
	public:
		using Object::Object;
		explicit Sprite(const sf::Texture& texture);
		Sprite(const sf::Texture& texture, const sf::IntRect& rectangle);

		void setTexture(const sf::Texture& texture, bool resetRect = false);
		void setTextureRect(const sf::IntRect& rectangle);
		void setColor(const sf::Color& color);
		const sf::Texture* getTexture() const;
		const sf::IntRect& getTextureRect() const;
		const sf::Color& getColor() const;
		sf::FloatRect getLocalBounds() const;
		sf::FloatRect getGlobalBounds() const;

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

		sf::Sprite _sprite;
	};

}