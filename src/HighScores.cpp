#include "HighScores.h"

#include <asw/util/KeyListener.h>
#include <asw/util/MouseListener.h>
#include <fstream>
#include <string>
#include <vector>

#include "globals.h"

void HighScores::init() {
  background_menu =
      asw::load::texture("assets/img/backgrounds/background_menu.png");

  levelSelect = asw::load::texture("assets/img/selector/levelSelect.png");
  levelSelectLeft =
      asw::load::texture("assets/img/selector/levelSelectLeft.png");
  levelSelectRight =
      asw::load::texture("assets/img/selector/levelSelectRight.png");

  font = asw::load::font("assets/fonts/ariblk.ttf", 24);

  click = asw::load::sample("assets/sfx/click.wav");

  updateScores();
}

void HighScores::update() {
  // Go to menu
  if (KeyListener::keyDown[SDL_SCANCODE_M]) {
    setNextState(StateEngine::STATE_MENU);
  }

  // Click buttons
  if (collision(MouseListener::x, MouseListener::x, -1, 200, MouseListener::y,
                MouseListener::y, 0, 920) ||
      KeyListener::keyDown[SDL_SCANCODE_LEFT]) {
    if (MouseListener::mouse_pressed & 1 ||
        KeyListener::keyDown[SDL_SCANCODE_LEFT]) {
      if (difficulty > 4) {
        difficulty -= 2;
        asw::sound::play(click);
        updateScores();
      }
    }
  } else if (collision(MouseListener::x, MouseListener::x, 1080, 1280,
                       MouseListener::y, MouseListener::y, 0, 920) ||
             KeyListener::keyDown[SDL_SCANCODE_RIGHT]) {
    if (MouseListener::mouse_pressed & 1 ||
        KeyListener::keyDown[SDL_SCANCODE_RIGHT]) {
      if (difficulty < 10) {
        difficulty += 2;
        asw::sound::play(click);
        updateScores();
      }
    }
  }
}

void HighScores::draw() {
  // Background
  asw::draw::sprite(levelSelect, 0, 0);

  // Titles
  if (difficulty == 4) {
    asw::draw::textCenter(font, "Easy", 640, 100,
                          asw::util::makeColor(0, 0, 0));
  } else if (difficulty == 6) {
    asw::draw::textCenter(font, "Medium", 640, 100,
                          asw::util::makeColor(0, 0, 0));
  } else if (difficulty == 8) {
    asw::draw::textCenter(font, "Hard", 640, 100,
                          asw::util::makeColor(0, 0, 0));
  } else if (difficulty == 10) {
    asw::draw::textCenter(font, "EXTREME", 640, 100,
                          asw::util::makeColor(0, 0, 0));
  }

  // Click buttons
  if (collision(MouseListener::x, MouseListener::x, -1, 200, MouseListener::y,
                MouseListener::y, 0, 920) ||
      KeyListener::keyDown[SDL_SCANCODE_LEFT]) {
    asw::draw::sprite(levelSelectLeft, 0, 0);
  } else if (collision(MouseListener::x, MouseListener::x, 1080, 1280,
                       MouseListener::y, MouseListener::y, 0, 920) ||
             KeyListener::keyDown[SDL_SCANCODE_RIGHT]) {
    asw::draw::sprite(levelSelectRight, 1080, 0);
  }

  // Draw scores
  for (int i = 0; i < 10; i++) {
    std::string name = scores[i][0];
    asw::draw::text(font, name.c_str(), 400, (i * 50) + 200,
                    asw::util::makeColor(0, 0, 0));

    name = scores[i][1];

    // TODO: Impl text right
    asw::draw::text(font, name.c_str(), 860, (i * 50) + 200,
                    asw::util::makeColor(0, 0, 0));
  }
}

void HighScores::updateScores() {
  std::string fileName = "";

  if (difficulty == 4) {
    fileName = "assets/data/highscores_easy.dat";
  } else if (difficulty == 6) {
    fileName = "assets/data/highscores_medium.dat";
  } else if (difficulty == 8) {
    fileName = "assets/data/highscores_hard.dat";
  } else if (difficulty == 10) {
    fileName = "assets/data/highscores_extreme.dat";
  }

  std::ifstream read(fileName.c_str());

  if (!read.is_open()) {
    asw::util::abortOnError("Could not open file: " + fileName);
  }

  for (int i = 0; i < 10; i++) {
    for (int t = 0; t < 2; t++) {
      read >> scores[i][t];
    }
  }

  read.close();
}