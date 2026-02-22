#include "HighScores.h"

#include <map>
#include <string>
#include <vector>

std::map<GameDifficulty, std::string> HighScores::SCORE_FILES {
    { GameDifficulty::EASY, "assets/data/highscores_easy.dat" },
    { GameDifficulty::MEDIUM, "assets/data/highscores_medium.dat" },
    { GameDifficulty::HARD, "assets/data/highscores_hard.dat" },
    { GameDifficulty::EXTREME, "assets/data/highscores_extreme.dat" }
};

void HighScores::init()
{
    const auto background = asw::assets::load_texture("assets/img/backgrounds/background.png");
    const auto click = asw::assets::load_sample("assets/sfx/click.wav");
    font_ = asw::assets::load_font("assets/fonts/jersey-10.ttf", 48);

    ui_ = asw::ui::Root();
    ui_.root.transform.size = asw::Vec2<float>(1280, 960);
    ui_.root.bg_image = background;

    auto& pnl_scores = ui_.root.add_child<asw::ui::Panel>();
    pnl_scores.transform.set_position(320, 130);
    pnl_scores.transform.set_size(640, 600);
    pnl_scores.bg = asw::Color(255, 255, 255);

    auto& btn_left = ui_.root.add_child<asw::ui::Button>();
    btn_left.transform = { 0, 0, 64, 960 };
    btn_left.text = "<";
    btn_left.font = font_;
    btn_left.on_click = [this, click]() {
        if (difficulty_ != GameDifficulty::EASY) {
            difficulty_ = static_cast<GameDifficulty>(static_cast<int>(difficulty_) - 1);
            asw::sound::play(click);
            score_manager_.load(SCORE_FILES[difficulty_]);
        }
    };

    auto& btn_right = ui_.root.add_child<asw::ui::Button>();
    btn_right.transform = { 1216, 0, 64, 960 };
    btn_right.text = ">";
    btn_right.font = font_;
    btn_right.on_click = [this, click]() {
        if (difficulty_ != GameDifficulty::EXTREME) {
            difficulty_ = static_cast<GameDifficulty>(static_cast<int>(difficulty_) + 1);
            asw::sound::play(click);
            score_manager_.load(SCORE_FILES[difficulty_]);
        }
    };

    auto& lbl_title = ui_.root.add_child<asw::ui::Label>();
    lbl_title.transform = { 640, 50, 0, 0 };
    lbl_title.font = font_;
    lbl_title.text = "High Scores";
    lbl_title.justify = asw::TextJustify::Center;

    auto& lbl_mode = ui_.root.add_child<asw::ui::Label>();
    lbl_mode.transform = { 640, 150, 0, 0 };
    lbl_mode.font = font_;
    lbl_mode.text = "";
    lbl_mode.justify = asw::TextJustify::Center;
    lbl_mode_ = &lbl_mode;

    score_manager_.load(SCORE_FILES[difficulty_]);
}

void HighScores::update(float dt)
{
    Scene::update(dt);
    ui_.update();

    if (difficulty_ == GameDifficulty::EASY) {
        lbl_mode_->text = "Easy";
    } else if (difficulty_ == GameDifficulty::MEDIUM) {
        lbl_mode_->text = "Medium";
    } else if (difficulty_ == GameDifficulty::HARD) {
        lbl_mode_->text = "Hard";
    } else if (difficulty_ == GameDifficulty::EXTREME) {
        lbl_mode_->text = "Extreme";
    }

    // Go to menu
    if (asw::input::get_key_down(asw::input::Key::Escape)) {
        manager.set_next_scene(States::Menu);
    }
}

void HighScores::draw()
{
    ui_.draw();

    // Draw scores
    float draw_y = 200;
    for (const auto& [name, score] : score_manager_.get()) {
        asw::draw::text(font_, name, asw::Vec2<float>(400, draw_y), asw::Color(0, 0, 0));
        asw::draw::text(font_, std::to_string(score), asw::Vec2<float>(840, draw_y),
            asw::Color(0, 0, 0), asw::TextJustify::Right);
        draw_y += 50;
    }
}
