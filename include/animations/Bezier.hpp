#pragma once

#include "engine/components/Animation.hpp"
#include "engine/components/Bezier.hpp"


namespace animations {

	/**
	 * @brief	Animation class for Cubic-Bezier transitions.
	 *			Visit https://cubic-bezier.com to visually pick your type of Bezier.
	*/
	class Bezier : public engine::Animation {
	public:
		Bezier(const sf::Vector2f& point1, const sf::Vector2f& point2);

		void update(sf::Time deltaTime) override;
		void on_start() override;

	private:
		BezierEasing _bezier;
		const BezierEasing _bezierCopy;

		sf::Time _timePassed;
		
		sf::Vector2f _distanceTraveled;
	};


	//////////////////
	// Most Commons //
	//////////////////

	class Ease : public Bezier {
	public:
		Ease() : Bezier{ { 0.25f, 0.1f }, { 0.25f, 1.f } } {}
	};
	class Linear : public Bezier {
	public:
		Linear() : Bezier{ { 0.f, 0.f }, { 1.f, 1.f } } {}
	};
	class Ease_In : public Bezier {
	public:
		Ease_In() : Bezier{ { 0.42f, 0.f }, { 1.f, 1.f } } {}
	};
	class Ease_Out: public Bezier {
	public:
		Ease_Out() : Bezier{ { 0.f, 0.f }, { 0.58f, 1.f } } {}
	};
	class Ease_In_Out : public Bezier {
	public:
		Ease_In_Out() : Bezier{ { 0.42f, 0.f }, { 0.58f, 1.f } } {}
	};
}