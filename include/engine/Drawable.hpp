#pragma once

#include <memory>
#include <SFML/Graphics/Drawable.hpp>
#include "Component.hpp"


namespace engine {

	class Drawable : public Component {
	public:
		void update() override { /*TODO*/ };

	private:
		std::unique_ptr<sf::Drawable> _drawable;
	};

}
