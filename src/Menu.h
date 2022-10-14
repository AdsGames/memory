#ifndef MENU_H
#define MENU_H

#include <asw/asw.h>

#include "State.h"
#include "ui/Button.h"

// Intro screen of game
class Menu : public State {
 public:
  using State::State;

  void init() override;
  void update() override;
  void draw() override;
  void cleanup() override{};

 private:
  asw::Texture background;

  Button buttonStart;
  Button buttonHighscores;
  Button buttonQuit;
};

#endif  // MENU_H
