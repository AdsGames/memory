#pragma once

#include <asw/asw.h>

#include "State.h"

// Intro screen of game
class Menu : public asw::scene::Scene<States> {
public:
    using asw::scene::Scene<States>::Scene;

    void init() override;

    void update(float dt) override;

    void draw() override;

private:
    asw::ui::Root ui_;
};
