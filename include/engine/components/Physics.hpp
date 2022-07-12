#pragma once

#include <SFML/System/Vector2.hpp>
#include "Component.hpp"


namespace engine {

	class Object;

	class Physics : public Component {
	public:

		void apply_force(sf::Vector2f force);
		void setForce(sf::Vector2f force);
		void setVelocity(sf::Vector2f velocity);
		void setMass(float mass);
		void setFriction(float friction);

	private:
		friend Object;
		void update();


		///////////////
		// Variables //
		///////////////
		sf::Vector2f _sumF;
		sf::Vector2f _acceleration;
		sf::Vector2f _velocity;
		float _mass;
		float _friction;
		float _bounciness;	// coefficient of restitution

		void calc_acceleration();
		void calc_velocity();
		void apply_movement();
	};

}
