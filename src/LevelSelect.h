#ifndef LEVEL_SELECT_H
#define LEVEL_SELECT_H

#include <asw/asw.h>
#include <map>

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
  void cleanup() override{
      // Nothing to do
  };

 private:
  asw::Texture background;
  std::map<GameDifficulty, asw::Texture> difficultyImages;

  asw::Font font;

  asw::Sample click;

  GameDifficulty difficulty{GameDifficulty::EASY};

  Button levelSelectLeft;
  Button levelSelectRight;
};

#endif  // LEVEL_SELECT_H
