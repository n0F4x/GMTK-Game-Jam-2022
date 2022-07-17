#pragma once

#include "engine/components/Animation.hpp"
#include "engine/components/Bezier.hpp"


namespace animations {

	/**
	 * @brief	Animation class for Cubic-Bezier transitions.
	 *			Visit https://cubic-bezier.com to visually pick your type of Bezier.
	*/
	class BezierOutlineColor : public engine::Animation {
	public:
		BezierOutlineColor(const sf::Vector2f& point1, const sf::Vector2f& point2);

		void update(sf::Time deltaTime) override;
		void on_start() override;

	private:
		BezierEasing _bezier;
		const BezierEasing _bezierCopy;

		sf::Time _timePassed;

		engine::Color _colored;
	};


	//////////////////
	// Most Commons //
	//////////////////

	class EaseOutlineColor : public BezierOutlineColor {
	public:
		EaseOutlineColor() : BezierOutlineColor{ { 0.25f, 0.1f }, { 0.25f, 1.f } } {}
	};
	class LinearOutlineColor : public BezierOutlineColor {
	public:
		LinearOutlineColor() : BezierOutlineColor{ { 0.f, 0.f }, { 1.f, 1.f } } {}
	};
	class Ease_InOutlineColor : public BezierOutlineColor {
	public:
		Ease_InOutlineColor() : BezierOutlineColor{ { 0.42f, 0.f }, { 1.f, 1.f } } {}
	};
	class Ease_OutOutlineColor : public BezierOutlineColor {
	public:
		Ease_OutOutlineColor() : BezierOutlineColor{ { 0.f, 0.f }, { 0.58f, 1.f } } {}
	};
	class Ease_In_OutOutlineColor : public BezierOutlineColor {
	public:
		Ease_In_OutOutlineColor() : BezierOutlineColor{ { 0.42f, 0.f }, { 0.58f, 1.f } } {}
	};
}
