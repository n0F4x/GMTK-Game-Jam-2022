#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <Object.hpp>


namespace engine {

	class State;

	class Renderer {
	private:
		friend State;	// Intellinse won't recommend it this way
		void render();

	public:
		void add_static(const Object* object);
		void remove_static(const Object* object);
		void flush_static();

		void push_basic(const Object* object);

		void push_priority(const Object* object);


	private:
		std::vector<const Object*> _static;
		std::vector<const Object*> _basic;
		std::vector<const Object*> _priority;
	};

}
