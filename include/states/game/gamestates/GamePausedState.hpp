#pragma once

#include "engine/State.hpp"


class GamePausedState : public engine::State {
private:
	void on_draw() override;
};
