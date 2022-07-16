#pragma once

#include "engine/State.hpp"


class GamePlayLookaroundState : public engine::State {
private:
	void on_draw() override;
};
