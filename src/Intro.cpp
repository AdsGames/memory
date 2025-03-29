#include "Intro.h"

#include <string>
#include <vector>

void Intro::init() {
  intro = asw::assets::loadTexture("assets/img/intro.png");
  timer.start();
}

void Intro::update(float deltaTime) {
  Scene::update(deltaTime);

  auto time = timer.getElapsedTime<std::chrono::milliseconds>();

  if (time >= 3000 || asw::input::keyboard.anyPressed) {
    sceneManager.setNextScene(States::Menu);
  }
}

void Intro::draw() {
  asw::draw::sprite(intro, asw::Vec2<float>(0, 0));
}
