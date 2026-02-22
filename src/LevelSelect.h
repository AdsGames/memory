#pragma once

#include <asw/asw.h>
#include <map>

#include "GameDifficulty.h"
#include "State.h"

// Intro screen of game
class LevelSelect : public asw::scene::Scene<States> {
public:
    using asw::scene::Scene<States>::Scene;

    void init() override;

    void update(float dt) override;

    void draw() override;

private:
    std::map<GameDifficulty, asw::Texture> difficulty_images_;
    GameDifficulty difficulty_ { GameDifficulty::EASY };
    asw::ui::Root ui_;
    asw::Quad<float> start_quad { 250, 185, 800, 600 };
};
