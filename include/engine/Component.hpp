#pragma once


namespace engine {

	class Object;

	enum class ComponentType {
		ANIMATOR,
		COLLIDER,
		DRAWABLE,
		PHYSICS
	};

	/**
	 * @brief	Abstract class (interface) used by Object
	*/
	class Component {
	public:
		void enable();
		void disable();

		virtual void update() = 0;

		virtual ~Component() = default;

	private:
		friend Object;
		Object* _object = nullptr;

		bool _enabled = true;
	};

}
