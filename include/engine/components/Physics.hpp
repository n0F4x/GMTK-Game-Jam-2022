#pragma once

#include <SFML/System/Vector2.hpp>
#include "engine/Component.hpp"


namespace engine {

	class Object;

	class Physics : public Component {
	public:
		/*  If a physics object has negative or 0 mass, won't be updated */
		Physics(
			float mass = 1.f,
			float friction = 0.f,
			float bounciness = 0.f,
			sf::Vector2f initialVelocity = { 0.f,0.f }
		);

		void setMass(float mass);
		float getMass() const;

		void setFriction(float friction);
		float getFriction() const;

		void setBounciness(float bounciness);
		float getBounciness() const;

		void setVelocity(sf::Vector2f velocity);
		sf::Vector2f getVelocity() const;

		void apply_force(sf::Vector2f force);
		void setForce(sf::Vector2f force);
		sf::Vector2f getForce() const;

	private:
		friend Object;
		void update();


		///////////////
		// Variables //
		///////////////
		float _mass;
		float _friction;
		float _bounciness;	// coefficient of restitution

		sf::Vector2f _velocity;
		sf::Vector2f _acceleration;
		sf::Vector2f _sumF;

		void calc_acceleration();
		void calc_velocity();
		void apply_movement();
	};

}
