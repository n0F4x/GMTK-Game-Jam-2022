#pragma once

#include "engine/components/Animation.hpp"
#include "engine/components/Bezier.hpp"


namespace animations {

	/**
	 * @brief	Animation class for Cubic-Bezier transitions.
	 *			Visit https://cubic-bezier.com to visually pick your type of Bezier.
	*/
	class BezierFillColor : public engine::Animation {
	public:
		BezierFillColor(const sf::Vector2f& point1, const sf::Vector2f& point2);

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

	class EaseFillColor : public BezierFillColor {
	public:
		EaseFillColor() : BezierFillColor{ { 0.25f, 0.1f }, { 0.25f, 1.f } } {}
	};
	class LinearFillColor : public BezierFillColor {
	public:
		LinearFillColor() : BezierFillColor{ { 0.f, 0.f }, { 1.f, 1.f } } {}
	};
	class Ease_InFillColor : public BezierFillColor {
	public:
		Ease_InFillColor() : BezierFillColor{ { 0.42f, 0.f }, { 1.f, 1.f } } {}
	};
	class Ease_OutFillColor : public BezierFillColor {
	public:
		Ease_OutFillColor() : BezierFillColor{ { 0.f, 0.f }, { 0.58f, 1.f } } {}
	};
	class Ease_In_OutFillColor : public BezierFillColor {
	public:
		Ease_In_OutFillColor() : BezierFillColor{ { 0.42f, 0.f }, { 0.58f, 1.f } } {}
	};
}
