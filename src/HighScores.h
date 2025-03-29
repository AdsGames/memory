#pragma once

#include <asw/asw.h>
#include <map>

#include "GameDifficulty.h"
#include "State.h"
#include "ui/Button.h"
#include "util/ScoreManager.h"

// Intro screen of game
class HighScores : public asw::scene::Scene<States> {
 public:
  using asw::scene::Scene<States>::Scene;

  void init() override;

  void update(float deltaTime) override;

  void draw() override;

 private:
  static std::map<GameDifficulty, std::string> SCORE_FILES;

  void updateScores();

  asw::Texture background;

  asw::Font font;

  asw::Sample click;

  GameDifficulty difficulty{GameDifficulty::EASY};

  ScoreManager scoreManager;

  Button levelSelectLeft;
  Button levelSelectRight;
};
