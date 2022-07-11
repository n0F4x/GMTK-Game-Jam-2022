#pragma once


namespace engine {

	class Object {
	public:
		void virtual update() = 0;

		virtual ~Object() = default;
	};

}
