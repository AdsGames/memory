#pragma once

#include <asw/asw.h>
#include <asw/util/Timer.h>

#include "State.h"

// Intro screen of game
class Intro : public asw::scene::Scene<States> {
 public:
  using asw::scene::Scene<States>::Scene;

  void init() override;

  void update(float deltaTime) override;

  void draw() override;

 private:
  asw::Texture intro;

  Timer timer;
};
