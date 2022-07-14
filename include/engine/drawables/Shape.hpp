////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2022 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
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

#include <SFML/Graphics.hpp>
#include "engine/Object.hpp"


namespace engine {

	/**
	 * @brief	Rewriting sf::Shape to inherit from engine::Object instead of sf::Transformable
	*/
	class Shape : public sf::Drawable, public Object {
	public:
		void setTexture(const sf::Texture* texture, bool resetRect = false) override;
		void setTextureRect(const sf::IntRect& rect);
		void setFillColor(const sf::Color& color);
		void setOutlineColor(const sf::Color& color);
		void setOutlineThickness(float thickness);

		const sf::Texture* getTexture() const override;
		const sf::IntRect& getTextureRect() const;
		const sf::Color& getFillColor() const;
		const sf::Color& getOutlineColor() const;
		float getOutlineThickness() const;
		virtual std::size_t getPointCount() const = 0;
		virtual sf::Vector2f getPoint(std::size_t index) const = 0;
		sf::FloatRect getLocalBounds() const;
		sf::FloatRect getGlobalBounds() const;

	protected:
		Shape() = default;

		void updateVertices();

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void updateFillColors();
		void updateTexCoords();
		void updateOutline();
		void updateOutlineColors();


		///////////////
		// Variables //
		///////////////
		const sf::Texture*	m_texture = nullptr;					///< Texture of the shape
		sf::IntRect			m_textureRect;							///< Rectangle defining the area of the source texture to display
		sf::Color			m_fillColor{ 255, 255, 255 };			///< Fill color
		sf::Color			m_outlineColor{ 255, 255, 255 };		///< Outline color
		float				m_outlineThickness = 0;					///< Thickness of the shape's outline
		sf::VertexArray		m_vertices{ sf::TriangleFan };			///< Vertex array containing the fill geometry
		sf::VertexArray		m_outlineVertices{ sf::TriangleStrip };	///< Vertex array containing the outline geometry
		sf::FloatRect		m_insideBounds;							///< Bounding rectangle of the inside (fill)
		sf::FloatRect		m_bounds;								///< Bounding rectangle of the whole shape (outline + fill)
	};

}
