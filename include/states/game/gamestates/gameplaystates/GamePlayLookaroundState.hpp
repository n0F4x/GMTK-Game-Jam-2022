#pragma once

#include "engine/State.hpp"


class GamePlayLookAroundState : public engine::State {
private:
	void on_draw() override;
};
