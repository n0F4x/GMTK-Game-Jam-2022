#pragma once

#include "engine/components/Animation.hpp"
#include "engine/components/Bezier.hpp"


namespace animations {

	/**
	 * @brief	Animation class for Cubic-Bezier transitions.
	 *			Visit https://cubic-bezier.com to visually pick your type of Bezier.
	*/
	class BezierScale : public engine::Animation {
	public:
		BezierScale(const sf::Vector2f& point1, const sf::Vector2f& point2);

		void update(sf::Time deltaTime) override;
		void on_start() override;

	private:
		BezierEasing _bezier;
		const BezierEasing _bezierCopy;

		sf::Time _timePassed;

		sf::Vector2f _scaled;
	};


	//////////////////
	// Most Commons //
	//////////////////

	class EaseScale : public BezierScale {
	public:
		EaseScale() : BezierScale{ { 0.25f, 0.1f }, { 0.25f, 1.f } } {}
	};
	class LinearScale : public BezierScale {
	public:
		LinearScale() : BezierScale{ { 0.f, 0.f }, { 1.f, 1.f } } {}
	};
	class Ease_InScale : public BezierScale {
	public:
		Ease_InScale() : BezierScale{ { 0.42f, 0.f }, { 1.f, 1.f } } {}
	};
	class Ease_OutScale : public BezierScale {
	public:
		Ease_OutScale() : BezierScale{ { 0.f, 0.f }, { 0.58f, 1.f } } {}
	};
	class Ease_In_OutScale : public BezierScale {
	public:
		Ease_In_OutScale() : BezierScale{ { 0.42f, 0.f }, { 0.58f, 1.f } } {}
	};
}