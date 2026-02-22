#pragma once

#include <asw/asw.h>
#include <map>
#include <string>
#include <vector>

#include "Card.h"
#include "GameDifficulty.h"
#include "State.h"
#include "ui/InputBox.h"
#include "util/ScoreManager.h"

struct DifficultyConfig {
    std::string highscore_file;
    int dimension { 0 };
};

// Intro screen of game
class Game : public asw::scene::Scene<States> {
public:
    using asw::scene::Scene<States>::Scene;

    void init() override;

    void update(float dt) override;

    void draw() override;

    static GameDifficulty difficulty;

private:
    static std::map<GameDifficulty, DifficultyConfig> DIFFICULTY_CONFIG;

    void init_cards(const DifficultyConfig& config);
    void erase_off_screen_cards();
    void match_cards();
    void calculate_selected_cards();
    void endgame_update();

    int moves_ { 0 };

    std::vector<Card> cards_;

    asw::ui::Root ui_;
    asw::ui::InputBox* in_name_ { nullptr };
    asw::ui::Label* lbl_moves_ { nullptr };
    asw::ui::Panel* end_panel_ { nullptr };

    ScoreManager score_manager_;

    unsigned int card_selected_1_ { 0 };
    unsigned int card_selected_2_ { 0 };
};
