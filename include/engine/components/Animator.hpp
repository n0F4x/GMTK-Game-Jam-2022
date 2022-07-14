#pragma once

#include <map>
#include <string>
#include <memory>
#include <SFML/System/Time.hpp>
#include "engine/Component.hpp"
#include "engine/components/Animation.hpp"


namespace engine {

	class State;
	class Animation;

	/**
	 * @brief	Animator component for Object. It supports multiple animations at the same time (as long as they have the same origin).
	*/
	class Animator : public Component {
	public:
		/**
		 * @return	True if inseriton is successful, false if there is already an animation with the same name.
		*/
		bool addAnimation(const std::string& name, std::unique_ptr<Animation> animation);
		/**
		 * @return	!!! nullptr if not found !!!
		*/
		Animation* findAnimation(const std::string_view& name);
		void deleteAnimation(const std::string& name);


	private:
		friend State;
		void animate(sf::Time deltaTime) const;


		///////////////
		// Variables //
		///////////////
		std::map<const std::string, std::unique_ptr<Animation>, std::less<>> _animations;
	};

}
