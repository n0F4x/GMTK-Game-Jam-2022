#pragma once

#include "engine/State.hpp"


class GameOverState : public engine::State {
protected:
	void on_draw() override;
};
