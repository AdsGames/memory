#include "Game.h"

#include <algorithm>
#include <chrono>
#include <format>
#include <map>
#include <random>
#include <ranges>

#include "globals.h"

GameDifficulty Game::difficulty = GameDifficulty::EASY;

std::map<GameDifficulty, DifficultyConfig> Game::DIFFICULTY_CONFIG {
    { GameDifficulty::EASY,
        DifficultyConfig { .highscore_file = "assets/data/highscores_easy.dat", .dimension = 4 } },
    { GameDifficulty::MEDIUM,
        DifficultyConfig {
            .highscore_file = "assets/data/highscores_medium.dat", .dimension = 6 } },
    { GameDifficulty::HARD,
        DifficultyConfig { .highscore_file = "assets/data/highscores_hard.dat", .dimension = 8 } },
    { GameDifficulty::EXTREME,
        DifficultyConfig {
            .highscore_file = "assets/data/highscores_extreme.dat", .dimension = 10 } }
};

void Game::init()
{
    auto screen_size = asw::display::get_logical_size();

    const auto font = asw::assets::load_font("assets/fonts/jersey-10.ttf", 48);

    ui_ = asw::ui::Root();
    ui_.root.transform.set_size(screen_size.x, screen_size.y);
    ui_.root.bg_image = asw::assets::load_texture("assets/img/backgrounds/background.png");

    // Moves panel
    auto& pnl_moves = ui_.root.add_child<asw::ui::Panel>();
    pnl_moves.transform.set_position(15, 15);
    pnl_moves.transform.set_size(200, 60);
    pnl_moves.bg = asw::Color(255, 255, 255);

    auto& lbl_moves = pnl_moves.add_child<asw::ui::Label>();
    lbl_moves.transform.set_position(20, 20);
    lbl_moves.font = font;
    lbl_moves_ = &lbl_moves;

    // Level end panel
    auto& end_panel = ui_.root.add_child<asw::ui::Panel>();
    end_panel.transform.set_position(screen_size.x / 2 - 300, screen_size.y / 2 - 150);
    end_panel.transform.set_size(600, 300);
    end_panel.bg = asw::Color(255, 255, 255);
    end_panel.visible = false;
    end_panel_ = &end_panel;

    auto& in_name = end_panel.add_child<asw::ui::InputBox>();
    in_name.transform.set_position(screen_size.x / 2 - 200, screen_size.y / 2 - 50);
    in_name.transform.set_size(400, 80);
    in_name.font = font;
    in_name.value = "Player";
    in_name_ = &in_name;

    auto& lbl_complete = end_panel.add_child<asw::ui::Label>();
    lbl_complete.transform.set_position(screen_size.x / 2, screen_size.y / 2 - 100);
    lbl_complete.font = font;
    lbl_complete.text = "Congratulations! Enter Your Name";
    lbl_complete.justify = asw::TextJustify::Center;

    // Init
    const auto& config = DIFFICULTY_CONFIG[difficulty];
    this->init_cards(config);
    score_manager_.load(config.highscore_file);
}

void Game::init_cards(const DifficultyConfig& config)
{
    // Clear cards
    cards_.clear();

    // Creates 10 blank cards
    for (int i = 0; i < config.dimension; i++) {
        for (int t = 0; t < config.dimension; t++) {
            cards_.emplace_back(-1, 700 / config.dimension);
        }
    }

    // Adds types in sets of 2
    for (unsigned int i = 0; i < cards_.size() - 1; i += 2) {
        const auto cardType = asw::random::between(0, 5);
        cards_.at(i).set_type(cardType);
        cards_.at(i + 1).set_type(cardType);
    }

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::ranges::shuffle(cards_, std::default_random_engine(seed));

    // Sets positions
    for (unsigned int i = 0; i < cards_.size(); i++) {
        const auto card_x = 250 + ((i % config.dimension) * (800 / config.dimension));
        const auto card_y = 80 + ((i / config.dimension) * (800 / config.dimension));
        cards_.at(i).set_position(card_x, card_y);
    }
}

void Game::update(float dt)
{
    Scene::update(dt);
    ui_.update();

    lbl_moves_->text = std::format("Moves: {}", moves_);

    // End game
    if (cards_.empty()) {
        endgame_update();
    }
    // Go to menu
    else if (asw::input::get_key_down(asw::input::Key::Escape)) {
        manager.set_next_scene(States::Menu);
    }

    erase_off_screen_cards();
    calculate_selected_cards();

    // Do card logic
    for (auto& card : cards_) {
        card.update(dt);
    }

    if (number_selected == 2) {
        match_cards();
    }
}

void Game::endgame_update()
{
    end_panel_->visible = true;

    if (asw::input::get_key_down(asw::input::Key::Return)) {
        const auto& config = DIFFICULTY_CONFIG[difficulty];
        score_manager_.add(in_name_->value, moves_);
        score_manager_.save(config.highscore_file);
        manager.set_next_scene(States::Menu);
    }
}

void Game::erase_off_screen_cards()
{
    // Erase off screen
    std::erase_if(cards_, [](const auto& card) { return card.is_off_screen(); });
}

void Game::calculate_selected_cards()
{
    // Count number of flipped cards
    card_selected_1_ = 0;
    card_selected_2_ = 0;
    number_selected = 0;

    for (unsigned int i = 0; i < cards_.size(); i++) {
        const auto& card = cards_.at(i);

        if (card.is_selected()) {
            if (number_selected == 0) {
                card_selected_1_ = i;
                number_selected = 1;
            } else if (number_selected == 1) {
                card_selected_2_ = i;
                number_selected = 2;
            }
        }
    }
}

void Game::match_cards()
{
    if (card_selected_1_ == card_selected_2_) {
        return;
    }

    auto& card1 = cards_.at(card_selected_1_);
    auto& card2 = cards_.at(card_selected_2_);

    if (!card1.is_animation_done() || !card2.is_animation_done()) {
        return;
    }

    if (card1.get_type() == card2.get_type()) {
        card1.match();
        card2.match();
    }

    card1.deselect();
    card2.deselect();
    moves_++;
}

void Game::draw()
{
    Scene::draw();
    ui_.draw();

    // Draw cards
    for (const auto& card : cards_) {
        card.draw();
    }
}
