#include "Init.h"

#include <asw/asw.h>

void Init::init() {
  asw::display::setTitle("Setting up");
  asw::display::setIcon("assets/img/icon.png");
  asw::display::setTitle("Memory");
}

void Init::update(float deltaTime) {
  Scene::update(deltaTime);

  sceneManager.setNextScene(States::Intro);
}

void Init::draw() {
  asw::draw::clearColor(asw::util::makeColor(0, 0, 0));
}
