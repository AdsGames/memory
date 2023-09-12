#include "Init.h"

#include <asw/asw.h>

void Init::init() {
  asw::display::setTitle("Setting up");
  asw::display::setIcon("assets/img/icon.png");
  asw::display::setTitle("Memory");
}

void Init::update() {
  setNextState(ProgramState::STATE_INTRO);
}

void Init::draw() {
  asw::draw::clearColor(asw::util::makeColor(0, 0, 0));
}
