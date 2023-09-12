#include "Game.h"

#include <algorithm>
#include <chrono>
#include <map>
#include <random>

#include "globals.h"

GameDifficulty Game::difficulty = GameDifficulty::EASY;

std::map<GameDifficulty, std::string> Game::SCORE_FILES{
    {GameDifficulty::EASY, "assets/data/highscores_easy.dat"},
    {GameDifficulty::MEDIUM, "assets/data/highscores_medium.dat"},
    {GameDifficulty::HARD, "assets/data/highscores_hard.dat"},
    {GameDifficulty::EXTREME, "assets/data/highscores_extreme.dat"}};

void Game::init() {
  auto screenSize = asw::display::getLogicalSize();

  background =
      asw::assets::loadTexture("assets/img/backgrounds/background.png");

  font = asw::assets::loadFont("assets/fonts/ariblk.ttf", 24);

  nameBox =
      InputBox(screenSize.x / 2 - 100, screenSize.y / 2 - 50, 200, 100, font);

  int dimension = 0;
  switch (difficulty) {
    case GameDifficulty::EASY:
      dimension = 4;
      break;
    case GameDifficulty::MEDIUM:
      dimension = 6;
      break;
    case GameDifficulty::HARD:
      dimension = 8;
      break;
    case GameDifficulty::EXTREME:
      dimension = 10;
      break;
  }

  // Creates 10 blank cards
  for (int i = 0; i < dimension; i++) {
    for (int t = 0; t < dimension; t++) {
      cards.emplace_back(-1, 700 / dimension);
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
    cards.at(i).setPosition(250 + (i % dimension) * 800 / dimension,
                            80 + (i / dimension) * 800 / dimension);
  }

  scoreManager.loadScores(SCORE_FILES[difficulty]);
}

void Game::update() {
  // End game
  if (cards.empty()) {
    nameBox.update();

    if (asw::input::keyboard.pressed[SDL_SCANCODE_RETURN]) {
      scoreManager.addScore(nameBox.getValue(), moves);
      scoreManager.saveScores(SCORE_FILES[difficulty]);
      setNextState(ProgramState::STATE_MENU);
    }
  }
  // Go to menu
  else if (asw::input::keyboard.pressed[SDL_SCANCODE_M]) {
    setNextState(ProgramState::STATE_MENU);
  }

  // Card logic
  // Count number of flipped cards
  cardSelected1 = 0;
  cardSelected2 = 0;
  numberSelected = 0;

  // Erase off screen
  cards.erase(
      std::remove_if(cards.begin(), cards.end(),
                     [](const auto& card) { return card.isOffScreen(); }),
      cards.end());

  // Do card logic
  for (unsigned int i = 0; i < cards.size(); i++) {
    auto& card = cards.at(i);

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

  for (auto& card : cards) {
    card.update();
  }

  if (numberSelected == 2) {
    auto& card1 = cards.at(cardSelected1);
    auto& card2 = cards.at(cardSelected2);

    if (card1.isAnimationDone() && card2.isAnimationDone()) {
      if (card1.getType() == card2.getType()) {
        card1.match();
        card2.match();
      }

      card1.deselect();
      card2.deselect();
      moves++;
    }
  }
}

void Game::draw() {
  // Background
  asw::draw::sprite(background, 0, 0);

  // Show Moves
  asw::draw::rectFill(15, 15, 200, 70, asw::util::makeColor(255, 255, 255));
  asw::draw::text(font, "Moves:" + std::to_string(moves), 20, 20,
                  asw::util::makeColor(0, 0, 0));

  // Draw cards
  for (const auto& card : cards) {
    card.draw();
  }

  if (cards.empty()) {
    // Create gui
    asw::draw::textCenter(font, "Congratulations! Enter Your Name", 640, 310,
                          asw::util::makeColor(0, 0, 0));

    nameBox.draw();
  }
}
