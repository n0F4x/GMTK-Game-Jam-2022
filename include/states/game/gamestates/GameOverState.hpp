#pragma once

#include "engine/State.hpp"


class GameOverState : public engine::State {
private:
	void on_draw() override;
};
