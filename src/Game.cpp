#include "Game.h"

#include <algorithm>
#include <chrono>
#include <map>
#include <random>

#include "globals.h"

GameDifficulty Game::difficulty = GameDifficulty::EASY;

std::map<GameDifficulty, DifficultyConfig> Game::DIFFICULTY_CONFIG{
    {GameDifficulty::EASY,
     DifficultyConfig{.highscoresFile = "assets/data/highscores_easy.dat",
                      .dimension = 4}},
    {GameDifficulty::MEDIUM,
     DifficultyConfig{.highscoresFile = "assets/data/highscores_medium.dat",
                      .dimension = 6}},
    {GameDifficulty::HARD,
     DifficultyConfig{.highscoresFile = "assets/data/highscores_hard.dat",
                      .dimension = 8}},
    {GameDifficulty::EXTREME,
     DifficultyConfig{.highscoresFile = "assets/data/highscores_extreme.dat",
                      .dimension = 10}}};

void Game::init() {
  auto screenSize = asw::display::getLogicalSize();

  background =
      asw::assets::loadTexture("assets/img/backgrounds/background.png");

  font = asw::assets::loadFont("assets/fonts/ariblk.ttf", 24);

  nameBox =
      InputBox(screenSize.x / 2 - 100, screenSize.y / 2 - 50, 200, 100, font);

  auto& config = DIFFICULTY_CONFIG[difficulty];

  this->initCards(config);

  scoreManager.loadScores(config.highscoresFile);
}

void Game::initCards(const DifficultyConfig& config) {
  // Creates 10 blank cards
  for (int i = 0; i < config.dimension; i++) {
    for (int t = 0; t < config.dimension; t++) {
      cards.emplace_back(-1, 700 / config.dimension);
    }
  }

  // Adds types in sets of 2
  for (unsigned int i = 0; i < cards.size() - 1; i += 2) {
    int cardType = random(0, 5);
    cards.at(i).setType(cardType);
    cards.at(i + 1).setType(cardType);
  }

  auto seed = std::chrono::system_clock::now().time_since_epoch().count();

  std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));

  // Sets positions
  for (unsigned int i = 0; i < cards.size(); i++) {
    cards.at(i).setPosition(
        250 + (i % config.dimension) * 800 / config.dimension,
        80 + (i / config.dimension) * 800 / config.dimension);
  }
}

void Game::update(float deltaTime) {
  Scene::update(deltaTime);

  // End game
  if (cards.empty()) {
    this->endgameUpdate();
  }
  // Go to menu
  else if (asw::input::wasKeyPressed(asw::input::Key::ESCAPE)) {
    sceneManager.setNextScene(States::Menu);
  }

  this->eraseOffScreenCards();
  this->calculateSelectedCards();

  // Do card logic
  for (auto& card : cards) {
    card.update();
  }

  if (numberSelected == 2) {
    this->matchCards();
  }
}

void Game::endgameUpdate() {
  nameBox.update();

  if (asw::input::wasKeyPressed(asw::input::Key::RETURN)) {
    auto& config = DIFFICULTY_CONFIG[difficulty];
    scoreManager.addScore(nameBox.getValue(), moves);
    scoreManager.saveScores(config.highscoresFile);
    sceneManager.setNextScene(States::Menu);
  }
}

void Game::eraseOffScreenCards() {
  // Erase off screen
  cards.erase(
      std::remove_if(cards.begin(), cards.end(),
                     [](const auto& card) { return card.isOffScreen(); }),
      cards.end());
}

void Game::calculateSelectedCards() {
  // Count number of flipped cards
  cardSelected1 = 0;
  cardSelected2 = 0;
  numberSelected = 0;

  for (unsigned int i = 0; i < cards.size(); i++) {
    const auto& card = cards.at(i);

    if (card.isSelected()) {
      if (numberSelected == 0) {
        cardSelected1 = i;
        numberSelected = 1;
      } else if (numberSelected == 1) {
        cardSelected2 = i;
        numberSelected = 2;
      }
    }
  }
}

void Game::matchCards() {
  if (cardSelected1 == cardSelected2) {
    return;
  }

  auto& card1 = cards.at(cardSelected1);
  auto& card2 = cards.at(cardSelected2);

  if (!card1.isAnimationDone() || !card2.isAnimationDone()) {
    return;
  }

  if (card1.getType() == card2.getType()) {
    card1.match();
    card2.match();
  }

  card1.deselect();
  card2.deselect();
  moves++;
}

void Game::draw() {
  // Background
  asw::draw::sprite(background, asw::Vec2<float>(0, 0));

  // Show Moves
  asw::draw::rectFill(asw::Quad<float>(15, 15, 200, 70),
                      asw::util::makeColor(255, 255, 255));
  asw::draw::text(font, "Moves:" + std::to_string(moves),
                  asw::Vec2<float>(20, 20), asw::util::makeColor(0, 0, 0));

  // Draw cards
  for (const auto& card : cards) {
    card.draw();
  }

  if (cards.empty()) {
    // Create gui
    asw::draw::textCenter(font, "Congratulations! Enter Your Name",
                          asw::Vec2<float>(640, 310),
                          asw::util::makeColor(0, 0, 0));

    nameBox.draw();
  }
}
