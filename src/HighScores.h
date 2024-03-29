#ifndef HIGH_SCORES_H
#define HIGH_SCORES_H

#include <asw/asw.h>
#include <map>

#include "GameDifficulty.h"
#include "State.h"
#include "ui/Button.h"
#include "util/ScoreManager.h"

// Intro screen of game
class HighScores : public State {
 public:
  using State::State;

  void init() override;
  void update() override;
  void draw() override;
  void cleanup() override{
      // Nothing to do
  };

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

#endif  // HIGH_SCORES_H
