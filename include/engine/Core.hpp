#pragma once

#include "StateMachine.hpp"


namespace engine {

	class Core : public StateMachine {
	public:
		Core();

		int load_global_assets() const;
		void run();

	private:
		Store _store;
	};

}