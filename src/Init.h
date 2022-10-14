#ifndef INIT_H
#define INIT_H

#include "State.h"

class Init : public State {
 public:
  using State::State;

  void init() override;
  void update() override;
  void draw() override;
  void cleanup() override;
};

#endif  // INIT_H
