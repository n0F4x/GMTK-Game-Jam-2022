#pragma once

#include "engine/State.hpp"


class GameState : public engine::State {
private:
	void on_draw() override;
};
