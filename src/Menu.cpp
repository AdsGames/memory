#include "Menu.h"

#include <string>
#include <vector>

#include "globals.h"

void Menu::init() {
  background =
      asw::assets::loadTexture("assets/img/backgrounds/background_menu.png");

  buttonStart = Button(320, 275);
  buttonHighscores = Button(320, 405);
  buttonQuit = Button(320, 535);

  // Button images
  buttonStart.setImages("assets/img/buttons/button_start.png",
                        "assets/img/buttons/button_start_hover.png");
  buttonHighscores.setImages("assets/img/buttons/button_scores.png",
                             "assets/img/buttons/button_scores_hover.png");
  buttonQuit.setImages("assets/img/buttons/button_quit.png",
                       "assets/img/buttons/button_quit_hover.png");

  // Button actions
  buttonStart.setOnClick(
      [this]() { setNextState(ProgramState::STATE_LEVEL_SELECT); });

  buttonHighscores.setOnClick(
      [this]() { setNextState(ProgramState::STATE_HIGH_SCORES); });

  buttonQuit.setOnClick([this]() { setNextState(ProgramState::STATE_EXIT); });
}

void Menu::update() {
  buttonStart.update();
  buttonHighscores.update();
  buttonQuit.update();
}

void Menu::draw() {
  asw::draw::sprite(background, 0, 0);
  buttonStart.draw();
  buttonHighscores.draw();
  buttonQuit.draw();
}
