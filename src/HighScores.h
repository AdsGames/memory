#ifndef HIGH_SCORES_H
#define HIGH_SCORES_H

#include <asw/asw.h>

#include "State.h"
#include "button.h"

// Intro screen of game
class HighScores : public State {
 public:
  explicit HighScores(StateEngine& engine) : State(engine) {}

  virtual void init() override;
  virtual void update() override;
  virtual void draw() override;
  virtual void cleanup() override{};

  void updateScores();

 private:
  asw::Texture background_menu;
  asw::Texture levelSelect;
  asw::Texture levelSelectLeft;
  asw::Texture levelSelectRight;

  asw::Font font;

  asw::Sample click;

  int difficulty{4};
};

#endif  // HIGH_SCORES_H
