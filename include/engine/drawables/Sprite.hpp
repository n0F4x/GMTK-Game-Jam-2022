////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented,
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include "engine/Object.hpp"


namespace engine {

	/**
	 * @brief   Rewriting sf::Sprite to inherit from engine::Object instead of sf::Transformable
	*/
	class Sprite : public sf::Drawable, public Object {
	public:
		Sprite() = default;
		explicit Sprite(const sf::Texture* texture);
		Sprite(const sf::Texture* texture, const sf::IntRect& rectangle);

		void setTexture(const sf::Texture* texture, bool resetRect = false) override;
		void setTextureRect(const sf::IntRect& rectangle);
		void setColor(const sf::Color& color);
		void setFillColor(const sf::Color& color) override;
        void scaleToSize(float sizeX, float sizeY);
        void scaleToSize(const sf::Vector2f& size);
        void scaleToSizeX(float sizeX);
        void scaleToSizeY(float sizeY);
		const sf::Texture* getTexture() const override;
		const sf::IntRect& getTextureRect() const;
		const sf::Color* getColor() const;
		const sf::Color* getFillColor() const override;
		sf::Vector2f getSize() const;
		sf::FloatRect getLocalBounds() const;
		sf::FloatRect getGlobalBounds() const;

    protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
		void updatePositions();
		void updateTexCoords();


		///////////////
		// Variables //
		///////////////
		std::array<sf::Vertex, 4>	m_vertices;				///< Vertices defining the sprite's geometry
		const sf::Texture*			m_texture = nullptr;	///< Texture of the sprite
		sf::IntRect                 m_textureRect;			///< Rectangle defining the area of the source texture to display
	};

}
