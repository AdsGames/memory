#ifndef INTRO_H
#define INTRO_H

#include <asw/asw.h>
#include <asw/util/Timer.h>

#include "State.h"

#define INTRO_FRAMES 84

// Intro screen of game
class Intro : public State {
 public:
  using State::State;

  void init() override;
  void update() override;
  void draw() override;
  void cleanup() override{
      // Nothing to do
  };

 private:
  asw::Texture intro;

  Timer timer;
};

#endif  // INTRO_H
