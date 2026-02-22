#include "Menu.h"

#include <string>
#include <vector>

void Menu::init()
{
    const auto background_
        = asw::assets::load_texture("assets/img/backgrounds/background_menu.png");
    const auto font = asw::assets::load_font("assets/fonts/jersey-10.ttf", 48);

    ui_ = asw::ui::Root();
    ui_.root.transform.size = asw::Vec2<float>(1280, 960);
    ui_.root.bg_image = background_;

    // Add buttons
    auto& btn_start = ui_.root.add_child<asw::ui::Button>();
    btn_start.transform = { 320, 275, 640, 100 };
    btn_start.text = "Start";
    btn_start.font = font;
    btn_start.on_click = [this]() { manager.set_next_scene(States::LevelSelect); };

    auto& btn_highscores = ui_.root.add_child<asw::ui::Button>();
    btn_highscores.transform = { 320, 405, 640, 100 };
    btn_highscores.text = "High Scores";
    btn_highscores.font = font;
    btn_highscores.on_click = [this]() { manager.set_next_scene(States::HighScores); };

    auto& btn_quit = ui_.root.add_child<asw::ui::Button>();
    btn_quit.transform = { 320, 535, 640, 100 };
    btn_quit.text = "Quit";
    btn_quit.font = font;
    btn_quit.on_click = []() { asw::core::exit = true; };
}

void Menu::update(float dt)
{
    Scene::update(dt);
    ui_.update();
}

void Menu::draw()
{
    ui_.draw();
}
