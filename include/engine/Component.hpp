#pragma once


namespace engine {

	class Object;

	/**
	 * @brief	Base class used by Object
	*/
	class Component {
	public:
		void enable();
		void disable();
		bool isEnabled() const;

		virtual ~Component() = default;

	protected:
		Object* object();


	private:
		friend Object;
		Object* _object = nullptr;

		bool _enabled = true;
	};

}
