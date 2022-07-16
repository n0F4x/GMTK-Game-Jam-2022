#pragma once

#include "engine/State.hpp"
#include "engine/StateMachine.hpp"

class DescriptionState : public engine::State {
public:
    DescriptionState();

private:
    void on_draw() override;

};