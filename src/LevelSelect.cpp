#include "LevelSelect.h"

#include <string>

#include "Game.h"

void LevelSelect::init()
{
    const auto background = asw::assets::load_texture("assets/img/backgrounds/background.png");

    difficulty_images_[GameDifficulty::EASY]
        = asw::assets::load_texture("assets/img/selector/easy.png");
    difficulty_images_[GameDifficulty::MEDIUM]
        = asw::assets::load_texture("assets/img/selector/medium.png");
    difficulty_images_[GameDifficulty::HARD]
        = asw::assets::load_texture("assets/img/selector/hard.png");
    difficulty_images_[GameDifficulty::EXTREME]
        = asw::assets::load_texture("assets/img/selector/extreme.png");

    const auto font = asw::assets::load_font("assets/fonts/jersey-10.ttf", 48);

    const auto click = asw::assets::load_sample("assets/sfx/click.wav");

    ui_ = asw::ui::Root();
    ui_.root.transform.size = asw::Vec2<float>(1280, 960);
    ui_.root.bg_image = background;

    // Add buttons
    auto& btn_left = ui_.root.add_child<asw::ui::Button>();
    btn_left.transform = { 0, 0, 64, 960 };
    btn_left.text = "<";
    btn_left.font = font;
    btn_left.on_click = [this, click]() {
        if (difficulty_ != GameDifficulty::EASY) {
            difficulty_ = static_cast<GameDifficulty>(static_cast<int>(difficulty_) - 1);
            asw::sound::play(click);
        }
    };

    auto& btn_start = ui_.root.add_child<asw::ui::Button>();
    btn_start.transform = start_quad;
    btn_start.text = "";
    btn_start.on_click = [this]() {
        Game::difficulty = difficulty_;
        manager.set_next_scene(States::Game);
    };

    auto& btn_right = ui_.root.add_child<asw::ui::Button>();
    btn_right.transform = { 1216, 0, 64, 960 };
    btn_right.text = ">";
    btn_right.font = font;
    btn_right.on_click = [this, click]() {
        if (difficulty_ != GameDifficulty::EXTREME) {
            difficulty_ = static_cast<GameDifficulty>(static_cast<int>(difficulty_) + 1);
            asw::sound::play(click);
        }
    };
}

void LevelSelect::update(float dt)
{
    Scene::update(dt);
    ui_.update();

    // Go to menu
    if (asw::input::get_key_down(asw::input::Key::Escape)) {
        manager.set_next_scene(States::Menu);
    }
}

void LevelSelect::draw()
{

    // Buttons
    ui_.draw();

    // Draw difficulty demos
    asw::draw::stretch_sprite(difficulty_images_[difficulty_], start_quad);
}
