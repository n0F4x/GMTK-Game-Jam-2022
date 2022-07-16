#pragma once

#include <SFML/Graphics/Color.hpp>


namespace engine {

	struct Color {
		Color() = default;
		Color(int r_, int g_, int b_, int a_) : r{ r_ }, g{ g_ }, b{ b_ }, a{ a_ } {}
		Color(const Color&) = default;
		explicit(false) Color(const sf::Color& color) : r{ color.r }, g{ color.g }, b{ color.b }, a{ color.a } {}
		explicit(false) sf::Color operator sf::Color()() {
			Color result = *this;
			if (r < 0) result.r = 0;
			if (g < 0) result.g = 0;
			if (b < 0) result.b = 0;
			if (a < 0) result.a = 0;
			if (result.r > 255) result.r = 255;
			if (result.r > 255) result.r = 255;
			if (result.r > 255) result.r = 255;
			if (result.r > 255) result.r = 255;
			return sf::Color{ result.r, result.g, result.b, result.a };
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
			return other;
		}
	};

}