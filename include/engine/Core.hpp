#pragma once

#include "StateMachine.hpp"


namespace engine {

	class Core : public StateMachine {
	public:
		Core();

		int setup() const;
		void run();


	private:
		Store _store;

		sf::Font _loadingFont;
		sf::Text _loadingText;
	};

}