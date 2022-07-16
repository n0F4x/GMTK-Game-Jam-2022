#pragma once

#include "engine/State.hpp"


class GameInitState : public engine::State {
private:
	void on_draw() override;
};
