#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "engine/Object.hpp"


namespace engine {

	/**
	 * @brief	Circle segment without outline.
	 *			Use this for simple circles too, as it is more lightweight than CircleShape.
	 *			!!! THE ORIGIN OF THE ARC IS ITS CENTER BY DEFAULT !!!
	*/
	class Arc : public sf::Drawable, public Object {
	public:
		/**
		 * @param spread	IN DEGREES, NOT RADIANS!!
		*/
		explicit Arc(float radius, float spread, size_t pointCount = 30);

		void setRadius(float radius);
		float getRadius() const;

		void setSpread(float degree);
		float getSpread() const;

		void setPointCount(size_t pointCount);
		size_t getPointCount() const;

		sf::Vertex& getPoint(size_t index);


		/////////////
		// Helpers //
		/////////////
		/**
		 * @brief	Sets the color of all vertices.
		*/
		void setColor(const sf::Color& color);

	private:
		void updateVertices();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


		///////////////
		// Variables //
		///////////////
		std::vector<sf::Vertex> _vertices;
		float _radius;						// The radius of the arc from the origin { 0, 0 }
		const float _angle = 0;				// The middle of the arc in radians
		float _spread;						// The width of the arc in radians
		size_t _pointCount;					// The maximum number of points constructing the arc
	};

}
