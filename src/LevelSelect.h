#ifndef LEVEL_SELECT_H
#define LEVEL_SELECT_H

#include <asw/asw.h>

#include "State.h"
#include "button.h"

// Intro screen of game
class LevelSelect : public State {
 public:
  explicit LevelSelect(StateEngine& engine) : State(engine) {}

  virtual void init() override;
  virtual void update() override;
  virtual void draw() override;
  virtual void cleanup() override{};

 private:
  asw::Texture background_menu;
  asw::Texture levelSelect;
  asw::Texture levelSelectLeft;
  asw::Texture levelSelectRight;
  asw::Texture difficultyImages[4];

  asw::Font font;

  asw::Sample click;
};

#endif  // LEVEL_SELECT_H
