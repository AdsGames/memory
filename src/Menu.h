#ifndef MENU_H
#define MENU_H

#include <asw/asw.h>

#include "State.h"
#include "button.h"

// Intro screen of game
class Menu : public State {
 public:
  explicit Menu(StateEngine& engine) : State(engine) {}

  virtual void init() override;
  virtual void update() override;
  virtual void draw() override;
  virtual void cleanup() override{};

 private:
  asw::Texture background_menu;

  Button button_start;
  Button button_highscores;
  Button button_quit;
};

#endif  // MENU_H
