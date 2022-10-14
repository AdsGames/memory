#ifndef LEVEL_SELECT_H
#define LEVEL_SELECT_H

#include <asw/asw.h>

#include "GameDifficulty.h"
#include "State.h"
#include "ui/Button.h"

// Intro screen of game
class LevelSelect : public State {
 public:
  using State::State;

  void init() override;
  void update() override;
  void draw() override;
  void cleanup() override{};

 private:
  asw::Texture background;
  asw::Texture difficultyImages[4];

  asw::Font font;

  asw::Sample click;

  GameDifficulty difficulty{GameDifficulty::EASY};

  Button levelSelectLeft;
  Button levelSelectRight;
};

#endif  // LEVEL_SELECT_H
