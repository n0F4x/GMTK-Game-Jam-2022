#pragma once

#include "engine/components/Animation.hpp"
#include "engine/components/Bezier.hpp"


namespace animations {

	/**
	 * @brief	Animation class for Cubic-Bezier transitions.
	 *			Visit https://cubic-bezier.com to visually pick your type of Bezier.
	*/
	class BezierColor : public engine::Animation {
	public:
		BezierColor(const sf::Vector2f& point1, const sf::Vector2f& point2);

		void update(sf::Time deltaTime) override;
		void on_start() override;

	private:
		BezierEasing _bezier;
		const BezierEasing _bezierCopy;

		sf::Time _timePassed;

		sf::Color _colored;
	};


	//////////////////
	// Most Commons //
	//////////////////

	class EaseColor : public BezierColor {
	public:
		EaseColor() : BezierColor{ { 0.25f, 0.1f }, { 0.25f, 1.f } } {}
	};
	class LinearColor : public BezierColor {
	public:
		LinearColor() : BezierColor{ { 0.f, 0.f }, { 1.f, 1.f } } {}
	};
	class Ease_InColor : public BezierColor {
	public:
		Ease_InColor() : BezierColor{ { 0.42f, 0.f }, { 1.f, 1.f } } {}
	};
	class Ease_OutColor : public BezierColor {
	public:
		Ease_OutColor() : BezierColor{ { 0.f, 0.f }, { 0.58f, 1.f } } {}
	};
	class Ease_In_OutColor : public BezierColor {
	public:
		Ease_In_OutColor() : BezierColor{ { 0.42f, 0.f }, { 0.58f, 1.f } } {}
	};
}
