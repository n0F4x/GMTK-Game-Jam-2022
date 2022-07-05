#include "Engine/Engine.hpp"

#include <numbers>
#include <iostream>


int main() {
	// testing c++20
	std::cout << "pi = " << std::numbers::pi << std::endl;

	Engine engine;

	engine.run();

	return 0;
}
