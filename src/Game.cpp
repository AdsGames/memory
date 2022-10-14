#include "Game.h"

#include <algorithm>
#include <chrono>
#include <random>

#include "globals.h"

GameDifficulty Game::difficulty = GameDifficulty::EASY;

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

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

  std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));

  // Sets positions
  for (unsigned int i = 0; i < cards.size(); i++) {
    cards.at(i).setPosition(250 + (i % dimension) * 800 / dimension,
                            80 + (i / dimension) * 800 / dimension);
  }

  auto scoreFile = getScoresFile();
  scoreManager.loadScores(scoreFile);
}

void Game::update() {
  // End game
  if (cards.empty()) {
    nameBox.update();

    if (asw::input::keyboard.pressed[SDL_SCANCODE_RETURN]) {
      auto scoreFile = getScoresFile();
      scoreManager.addScore(nameBox.getValue(), moves);
      scoreManager.saveScores(scoreFile);
      setNextState(ProgramState::STATE_MENU);
    }
  }
  // Go to menu
  else if (asw::input::keyboard.pressed[SDL_SCANCODE_M]) {
    setNextState(ProgramState::STATE_MENU);
  }

  // Card logic
  // Count number of flipped cards
  numberSelected = 0;
  for (const auto& card : cards) {
    if (card.getSelected()) {
      numberSelected++;
    }
  }

  // Do card logic
  for (auto& card : cards) {
    card.logic();
  }

  // Find the placing of the two flipped cards
  if (numberSelected > 0) {
    for (unsigned int i = 0; i < cards.size(); i++) {
      if (cards.at(i).getSelected()) {
        cardSelected1 = i;
        break;
      }
    }
    for (unsigned int i = 0; i < cards.size(); i++) {
      if (cards.at(i).getSelected() && cardSelected1 != i) {
        cardSelected2 = i;
        break;
      }
    }
  }

  if (numberSelected == 2 && cards.at(cardSelected1).getAnimationDone() &&
      cards.at(cardSelected2).getAnimationDone() &&
      cards.at(cardSelected1).getSelected() &&
      cards.at(cardSelected2).getSelected()) {
    if (cards.at(cardSelected1).getType() ==
        cards.at(cardSelected2).getType()) {
      cards.at(cardSelected1).match();
      cards.at(cardSelected2).match();
      if (cards.at(cardSelected1).getOffScreen() &&
          cards.at(cardSelected2).getOffScreen()) {
        cards.erase(cards.begin() + cardSelected1);
        cards.erase(cards.begin() + cardSelected2 - 1);
        moves++;
      }
    } else {
      cards.at(cardSelected1).deselect();
      cards.at(cardSelected2).deselect();
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

std::string Game::getScoresFile() const {
  std::string fileName = "";

  if (difficulty == GameDifficulty::EASY) {
    fileName = "assets/data/highscores_easy.dat";
  } else if (difficulty == GameDifficulty::MEDIUM) {
    fileName = "assets/data/highscores_medium.dat";
  } else if (difficulty == GameDifficulty::HARD) {
    fileName = "assets/data/highscores_hard.dat";
  } else if (difficulty == GameDifficulty::EXTREME) {
    fileName = "assets/data/highscores_extreme.dat";
  }

  return fileName;
}