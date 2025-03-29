#include "LevelSelect.h"

#include <string>

#include "Game.h"

void LevelSelect::init() {
  background =
      asw::assets::loadTexture("assets/img/backgrounds/background.png");

  difficultyImages[GameDifficulty::EASY] =
      asw::assets::loadTexture("assets/img/selector/easy.png");
  difficultyImages[GameDifficulty::MEDIUM] =
      asw::assets::loadTexture("assets/img/selector/medium.png");
  difficultyImages[GameDifficulty::HARD] =
      asw::assets::loadTexture("assets/img/selector/hard.png");
  difficultyImages[GameDifficulty::EXTREME] =
      asw::assets::loadTexture("assets/img/selector/extreme.png");

  font = asw::assets::loadFont("assets/fonts/ariblk.ttf", 24);

  click = asw::assets::loadSample("assets/sfx/click.wav");

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
    }
  });

  levelSelectRight.setOnClick([this]() {
    if (difficulty != GameDifficulty::EXTREME) {
      difficulty =
          static_cast<GameDifficulty>(static_cast<int>(difficulty) + 1);
      asw::sound::play(click);
    }
  });
}

void LevelSelect::update(float deltaTime) {
  Scene::update(deltaTime);

  // Go to menu
  if (asw::input::wasKeyPressed(asw::input::Key::ESCAPE)) {
    sceneManager.setNextScene(States::Menu);
  }

  levelSelectLeft.update();
  levelSelectRight.update();

  // Click buttons
  if ((asw::input::mouse.pressed[1] &&
       collision((int)asw::input::mouse.x, (int)asw::input::mouse.x, 250, 1050,
                 (int)asw::input::mouse.y, (int)asw::input::mouse.y, 185,
                 785)) ||
      asw::input::wasKeyPressed(asw::input::Key::RETURN)) {
    Game::difficulty = difficulty;
    sceneManager.setNextScene(States::Game);
  }
}

void LevelSelect::draw() {
  // Background
  asw::draw::sprite(background, asw::Vec2<float>(0, 0));

  // Buttons
  levelSelectLeft.draw();
  levelSelectRight.draw();

  // Draw difficulty demos
  asw::draw::sprite(difficultyImages[difficulty], asw::Vec2<float>(250, 185));
}
