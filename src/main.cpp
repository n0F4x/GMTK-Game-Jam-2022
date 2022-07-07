#include "engine/Core.hpp"

#include <numbers>
#include <iostream>


int main() {
	// testing c++20
	std::cout << "pi = " << std::numbers::pi << std::endl;

	engine::Core::run();

	return 0;
}
