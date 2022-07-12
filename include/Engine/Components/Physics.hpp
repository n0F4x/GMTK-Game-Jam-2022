#pragma once

#include "Component.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "Timer.hpp"

namespace engine {

	class Physics : public Component {
	public:
		void update() override;

		void apply_force(sf::Vector2f force);
		void setForce(sf::Vector2f force);
		void setVelocity(sf::Vector2f velocity);
		void setMass(float mass);
		void setFriction(float friction);

	private:
		sf::Vector2f _sumF, _acceleration, _velocity;
		float _mass, _friction, _bounciness;

		void calc_acceleration();
		void calc_velocity();
		void apply_movement();
	};

}
