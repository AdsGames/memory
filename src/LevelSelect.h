#pragma once

#include <asw/asw.h>
#include <map>

#include "GameDifficulty.h"
#include "State.h"
#include "ui/Button.h"

// Intro screen of game
class LevelSelect : public asw::scene::Scene<States> {
 public:
  using asw::scene::Scene<States>::Scene;

  void init() override;

  void update(float deltaTime) override;

  void draw() override;

 private:
  asw::Texture background;
  std::map<GameDifficulty, asw::Texture> difficultyImages;

  asw::Font font;

  asw::Sample click;

  GameDifficulty difficulty{GameDifficulty::EASY};

  Button levelSelectLeft;
  Button levelSelectRight;
};
