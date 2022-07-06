#include "engine/Engine.hpp"

#include <numbers>
#include <iostream>


int main() {
	// testing c++20
	std::cout << "pi = " << std::numbers::pi << std::endl;

	engine::Engine engine;

	engine.run();

	return 0;
}
