#include "engine/StateMachine.hpp"
#include "engine/Core.hpp"

// including numbers will fail if your C++ version is older than c++20
#include <numbers>


//////////////////////////////////
// 		INCLUDE MAIN STATES		//
//////////////////////////////////
#include "Sample.hpp"



int main() {
	engine::Core machine;


	if (machine.setup() != 0) {
		return 1;
	}


//////////////////////////////////
// 		EDIT THIS REGION		//
//////////////////////////////////

	// ADD MAIN STATES HERE:
	machine.addState("Sample", std::make_unique<SampleState>());
	machine.addState("Physics", std::make_unique<PhysicsSampleState>());
	machine.addState("Animations", std::make_unique<AnimationsSampleState>());
    machine.addState("Minimap", std::make_unique<MinimapSampleState>());


	// SET INITIAL STATE
	machine.setInitialState("Sample");

//////////////////////////////////
//		  END OF REGION			//
//////////////////////////////////


	if (machine.initialize() != 0) {
		return 1;
	}
	

	machine.run();

	return 0;
}
