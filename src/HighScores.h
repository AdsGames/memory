#pragma once

#include <asw/asw.h>
#include <map>

#include "GameDifficulty.h"
#include "State.h"
#include "util/ScoreManager.h"

// Intro screen of game
class HighScores : public asw::scene::Scene<States> {
public:
    using asw::scene::Scene<States>::Scene;

    void init() override;

    void update(float dt) override;

    void draw() override;

private:
    static std::map<GameDifficulty, std::string> SCORE_FILES;

    GameDifficulty difficulty_ { GameDifficulty::EASY };
    ScoreManager score_manager_;

    asw::ui::Root ui_;
    asw::Font font_;
    asw::ui::Label* lbl_mode_;
};
