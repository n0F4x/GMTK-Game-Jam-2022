#pragma once

#include <vector>
#include <SFML/Graphics.hpp>


namespace engine {

	class Animator;
	class Object;

	/**
	 * @brief	Component class to apply special animations onto your object using transforms and/or alternating textures.
	*/
	class Animation {
	public:
		virtual ~Animation() = default;

		virtual void update(sf::Time deltaTime) = 0;
		bool isActive() const;
		bool isPaused() const;

		/**
		 * @brief	Animation won't start if it is already active.
		 * @return	True if animation is currently inactive.
		*/
		bool start();
		void stop();
		void pause();
		void resume();


		/////////////
		// Setters //
		/////////////

		/**
		 * @brief	Set the duration of the animation.
		*/
		void setTime(sf::Time duration);
		/**
		 * @brief	Set the distance that the object will travel during animation from finish to end.
		*/
		void setDistance(const sf::Vector2f& distance);

		/**
		 * @brief	Set the origin of the animation (usually best if you set it to match the center point).
		 * @param origin	This will be the origin for all the transforms.
		*/
		void setOrigin(const sf::Vector2f& origin);
		/**
		 * @brief	Set the amount of rotation applied during animation. (For most cases this option is not supported, so nothing will happen).
		 * @param rotation	IN DEGREES!!!
		*/
		void setRotation(float rotation);
		/**
		 * @brief	Set the amount of scaling applied during animation. (For most cases this option is not supported, so nothing will happen).
		*/
		void setScale(float scale);

		/**
		 * @brief	Set the textures to be shown (in order) during animation.
		*/
		void setTextures(const std::vector<const sf::Texture*>& textures);
		/**
		 * @brief	Set the amount of time for the next texture to be shown.
		*/
		void setTextureTime(sf::Time time);


		/////////////
		// Getters //
		/////////////

		sf::Time getTime() const;
		const sf::Vector2f& getDistance() const;
		const sf::Vector2f& getOrigin() const;
		float getRotation() const;
		float getScale() const;
		std::vector<const sf::Texture*>& textures();
		sf::Time getTextureTime() const;


	protected:
		Object* object();
		virtual void on_start() = 0;



	private:
		friend Animator;
		Object* _object;
		bool _active = false;
		bool _paused = false;

		sf::Time _time;
		sf::Vector2f _distance;
		sf::Vector2f _origin;
		float _rotation = 0;
		float _scale = 0;
		std::vector<const sf::Texture*> _textures;
		sf::Time _textureTime;
	};

}