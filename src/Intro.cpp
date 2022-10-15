#include "Intro.h"

#include <string>
#include <vector>

void Intro::init() {
  intro = asw::assets::loadTexture("assets/img/intro.png");
  timer.Start();
}

void Intro::update() {
  auto time = timer.GetElapsedTime<milliseconds>();

  if (time >= 3000 || asw::input::keyboard.anyPressed) {
    setNextState(ProgramState::STATE_MENU);
  }
}

void Intro::draw() {
  asw::draw::sprite(intro, 0, 0);
}
