#pragma once

#include "engine/State.hpp"


class MenuState : public engine::State {
private:
	void on_draw() override;
};
