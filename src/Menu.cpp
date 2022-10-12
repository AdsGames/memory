#include "Menu.h"

#include <asw/util/KeyListener.h>
#include <asw/util/MouseListener.h>
#include <string>
#include <vector>

#include "globals.h"

void Menu::init() {
  background_menu =
      asw::load::texture("assets/img/backgrounds/background_menu.png");

  button_start = Button(320, 275, 640, 120);
  button_highscores = Button(320, 405, 640, 120);
  button_quit = Button(320, 535, 640, 120);

  // Button images
  button_start.setImages("assets/img/buttons/button_start.png",
                         "assets/img/buttons/button_start_hover.png");
  button_highscores.setImages("assets/img/buttons/button_scores.png",
                              "assets/img/buttons/button_scores_hover.png");
  button_quit.setImages("assets/img/buttons/button_quit.png",
                        "assets/img/buttons/button_quit_hover.png");
}

void Menu::update() {
  if (MouseListener::mouse_pressed & 1) {
    if (button_start.getHover()) {
      setNextState(StateEngine::STATE_LEVEL_SELECT);
    } else if (button_highscores.getHover()) {
      setNextState(StateEngine::STATE_HIGH_SCORES);
    } else if (button_quit.getHover()) {
      setNextState(StateEngine::STATE_EXIT);
    }
  }
}

void Menu::draw() {
  asw::draw::sprite(background_menu, 0, 0);
  button_start.draw();
  button_highscores.draw();
  button_quit.draw();
}
