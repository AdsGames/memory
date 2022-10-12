#ifndef INIT_H
#define INIT_H

#include "State.h"

class Init : public State {
 public:
  explicit Init(StateEngine& engine) : State(engine) {}

  virtual void init() override;
  virtual void update() override;
  virtual void draw() override;
  virtual void cleanup() override;
};

#endif  // INIT_H
