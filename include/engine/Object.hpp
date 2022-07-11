#pragma once


class Object {
public:
	void virtual update() = 0;

	virtual ~Object() = default;
};
