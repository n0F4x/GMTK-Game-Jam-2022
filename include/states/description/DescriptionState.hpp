#pragma once

#include "engine/State.hpp"


class DescriptionState : public engine::State {
private:
    void on_draw() override;
};
