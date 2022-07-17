#pragma once

#include <SFML/Graphics/Color.hpp>


namespace engine {

	struct Color {
		Color() = default;
		Color(float r_, float g_, float b_, float a_) : r{ r_ }, g{ g_ }, b{ b_ }, a{ a_ } {}
		Color(const Color&) = default;
		explicit(false) Color(const sf::Color& color) : r{ (float)color.r }, g{ (float)color.g }, b{ (float)color.b }, a{ (float)color.a } {}
		explicit(false) operator sf::Color() const {
			Color result = *this;
			if (r < 0) result.r = 0;
			if (g < 0) result.g = 0;
			if (b < 0) result.b = 0;
			if (a < 0) result.a = 0;
			if (result.r > 255) result.r = 255;
			if (result.g > 255) result.g = 255;
			if (result.b > 255) result.b = 255;
			if (result.a > 255) result.a = 255;
			return sf::Color{
				static_cast<sf::Uint8>(result.r),
				static_cast<sf::Uint8>(result.g),
				static_cast<sf::Uint8>(result.b),
				static_cast<sf::Uint8>(result.a)
			};
		}

		float r = 255;
		float g = 255;
		float b = 255;
		float a = 255;

		Color operator+(Color other) const {
			other.r += r;
			other.g += g;
			other.b += b;
			other.a += a;
			return other;
		}
		Color operator-(Color other) const {
			other.r -= r;
			other.g -= g;
			other.b -= b;
			other.a -= a;
			return other;
		}
		Color operator*(float factor) const {
			Color result = *this;
			result.r *= factor;
			result.g *= factor;
			result.b *= factor;
			result.a *= factor;
			return result;
		}
	};

}