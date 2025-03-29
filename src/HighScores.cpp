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

void HighScores::update(float deltaTime) {
  Scene::update(deltaTime);

  // Go to menu
  if (asw::input::wasKeyPressed(asw::input::Key::ESCAPE)) {
    sceneManager.setNextScene(States::Menu);
  }

  // Click buttons
  levelSelectLeft.update();
  levelSelectRight.update();
}

void HighScores::draw() {
  // Background
  asw::draw::sprite(background, asw::Vec2<float>(0, 0));

  // Titles
  if (difficulty == GameDifficulty::EASY) {
    asw::draw::textCenter(font, "Easy", asw::Vec2<float>(640, 100),
                          asw::util::makeColor(0, 0, 0));
  } else if (difficulty == GameDifficulty::MEDIUM) {
    asw::draw::textCenter(font, "Medium", asw::Vec2<float>(640, 100),
                          asw::util::makeColor(0, 0, 0));
  } else if (difficulty == GameDifficulty::HARD) {
    asw::draw::textCenter(font, "Hard", asw::Vec2<float>(640, 100),
                          asw::util::makeColor(0, 0, 0));
  } else if (difficulty == GameDifficulty::EXTREME) {
    asw::draw::textCenter(font, "EXTREME", asw::Vec2<float>(640, 100),
                          asw::util::makeColor(0, 0, 0));
  }

  // Click buttons
  levelSelectLeft.draw();
  levelSelectRight.draw();

  // Draw scores
  auto& scores = scoreManager.getScores();

  int drawY = 200;
  for (const auto& [name, score] : scores) {
    asw::draw::text(font, name, asw::Vec2<float>(400, drawY),
                    asw::util::makeColor(0, 0, 0));

    asw::draw::text(font, std::to_string(score), asw::Vec2<float>(860, drawY),
                    asw::util::makeColor(0, 0, 0));

    drawY += 50;
  }
}

void HighScores::updateScores() {
  scoreManager.loadScores(SCORE_FILES[difficulty]);
}