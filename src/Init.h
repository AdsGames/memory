#pragma once

#include <asw/asw.h>

#include "State.h"

class Init : public asw::scene::Scene<States> {
 public:
  using asw::scene::Scene<States>::Scene;

  void init() override;

  void update(float deltaTime) override;

  void draw() override;
};
