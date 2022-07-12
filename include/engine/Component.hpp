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
		bool is_enabled() const;

		virtual void update() = 0;

		virtual ~Component() = default;

	protected:
		friend Object;
		Object* _object = nullptr;

		bool _enabled = true;
	};

}
