#include "Intro.h"

#include <asw/util/KeyListener.h>
#include <string>
#include <vector>

#include "globals.h"

void Intro::init() {
  intro = asw::load::texture("assets/img/intro.png");
  timer.Start();
}

void Intro::update() {
  auto time = timer.GetElapsedTime<milliseconds>();

  if (time >= 3000 || KeyListener::anyKeyPressed) {
    setNextState(StateEngine::STATE_MENU);
  }
}

void Intro::draw() {
  asw::draw::sprite(intro, 0, 0);
}
