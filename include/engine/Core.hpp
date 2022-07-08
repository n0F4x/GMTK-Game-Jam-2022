#pragma once

#include "StateMachine.hpp"


namespace engine {

	class Core : public StateMachine {
	public:
		int load_global_assets() const;
		void run();
	};

}