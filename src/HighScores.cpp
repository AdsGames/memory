#include "HighScores.h"

#include <map>
#include <string>
#include <vector>

std::map<GameDifficulty, std::string> HighScores::SCORE_FILES{
    {GameDifficulty::EASY, "assets/data/highscores_easy.dat"},
    {GameDifficulty::MEDIUM, "assets/data/highscores_medium.dat"},
    {GameDifficulty::HARD, "assets/data/highscores_hard.dat"},
    {GameDifficulty::EXTREME, "assets/data/highscores_extreme.dat"}};

void HighScores::init() {
  background =
      asw::assets::loadTexture("assets/img/backgrounds/background.png");

  levelSelectLeft = Button(0, 0);
  levelSelectRight = Button(1080, 0);

  levelSelectLeft.setImages("assets/img/selector/level_select_left.png",
                            "assets/img/selector/level_select_left_hover.png");
  levelSelectRight.setImages(
      "assets/img/selector/level_select_right.png",
      "assets/img/selector/level_select_right_hover.png");

  levelSelectLeft.setOnClick([this]() {
    if (difficulty != GameDifficulty::EASY) {
      difficulty =
          static_cast<GameDifficulty>(static_cast<int>(difficulty) - 1);
      asw::sound::play(click);
      updateScores();
    }
  });

  levelSelectRight.setOnClick([this]() {
    if (difficulty != GameDifficulty::EXTREME) {
      difficulty =
          static_cast<GameDifficulty>(static_cast<int>(difficulty) + 1);
      asw::sound::play(click);
      updateScores();
    }
  });

  font = asw::assets::loadFont("assets/fonts/ariblk.ttf", 24);

  click = asw::assets::loadSample("assets/sfx/click.wav");

  updateScores();
}

void HighScores::update() {
  // Go to menu
  if (asw::input::keyboard.down[SDL_SCANCODE_M]) {
    setNextState(ProgramState::STATE_MENU);
  }

  // Click buttons
  levelSelectLeft.update();
  levelSelectRight.update();
}

void HighScores::draw() {
  // Background
  asw::draw::sprite(background, 0, 0);

  // Titles
  if (difficulty == GameDifficulty::EASY) {
    asw::draw::textCenter(font, "Easy", 640, 100,
                          asw::util::makeColor(0, 0, 0));
  } else if (difficulty == GameDifficulty::MEDIUM) {
    asw::draw::textCenter(font, "Medium", 640, 100,
                          asw::util::makeColor(0, 0, 0));
  } else if (difficulty == GameDifficulty::HARD) {
    asw::draw::textCenter(font, "Hard", 640, 100,
                          asw::util::makeColor(0, 0, 0));
  } else if (difficulty == GameDifficulty::EXTREME) {
    asw::draw::textCenter(font, "EXTREME", 640, 100,
                          asw::util::makeColor(0, 0, 0));
  }

  // Click buttons
  levelSelectLeft.draw();
  levelSelectRight.draw();

  // Draw scores
  auto& scores = scoreManager.getScores();

  int drawY = 200;
  for (const auto& [name, score] : scores) {
    asw::draw::text(font, name, 400, drawY, asw::util::makeColor(0, 0, 0));

    asw::draw::text(font, std::to_string(score), 860, drawY,
                    asw::util::makeColor(0, 0, 0));

    drawY += 50;
  }
}

void HighScores::updateScores() {
  auto fileName = SCORE_FILES[difficulty];
  scoreManager.loadScores(fileName);
}