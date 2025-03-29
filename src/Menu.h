#pragma once

#include <asw/asw.h>

#include "State.h"
#include "ui/Button.h"

// Intro screen of game
class Menu : public asw::scene::Scene<States> {
 public:
  using asw::scene::Scene<States>::Scene;

  void init() override;

  void update(float deltaTime) override;

  void draw() override;

 private:
  asw::Texture background;

  Button buttonStart;
  Button buttonHighscores;
  Button buttonQuit;
};
