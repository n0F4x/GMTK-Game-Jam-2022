#pragma once

#include "engine/components/Animation.hpp"
#include "engine/components/Bezier.hpp"


namespace animations {

	class Ease : public engine::Animation {
	public:
		void update(sf::Time deltaTime) override;
		void on_start() override;

	private:
		sf::Time _timePassed;
		sf::Vector2f _distanceTraveled;
		BezierEasing _bezier{ { 0.25f, 0.1f }, { 0.25f, 1.f } };
	};

}