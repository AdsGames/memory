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

void LevelSelect::update() {
  // Go to menu
  if (asw::input::keyboard.down[SDL_SCANCODE_M]) {
    setNextState(ProgramState::STATE_MENU);
  }

  levelSelectLeft.update();
  levelSelectRight.update();

  // Click buttons
  if ((asw::input::mouse.pressed[1] &&
       collision(asw::input::mouse.x, asw::input::mouse.x, 250, 1050,
                 asw::input::mouse.y, asw::input::mouse.y, 185, 785)) ||
      asw::input::keyboard.down[SDL_SCANCODE_RETURN]) {
    Game::difficulty = difficulty;
    setNextState(ProgramState::STATE_GAME);
  }
}

void LevelSelect::draw() {
  // Background
  asw::draw::sprite(background, 0, 0);

  // Buttons
  levelSelectLeft.draw();
  levelSelectRight.draw();

  // Draw difficulty demos
  asw::draw::sprite(difficultyImages[difficulty], 250, 185);
}
