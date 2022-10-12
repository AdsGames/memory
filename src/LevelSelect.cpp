#include "LevelSelect.h"

#include <asw/util/KeyListener.h>
#include <asw/util/MouseListener.h>
#include <string>

#include "globals.h"

void LevelSelect::init() {
  background_menu =
      asw::load::texture("assets/img/backgrounds/background_menu.png");

  levelSelect = asw::load::texture("assets/img/selector/levelSelect.png");
  levelSelectLeft =
      asw::load::texture("assets/img/selector/levelSelectLeft.png");
  levelSelectRight =
      asw::load::texture("assets/img/selector/levelSelectRight.png");

  difficultyImages[0] = asw::load::texture("assets/img/selector/easy.png");
  difficultyImages[1] = asw::load::texture("assets/img/selector/medium.png");
  difficultyImages[2] = asw::load::texture("assets/img/selector/hard.png");
  difficultyImages[3] = asw::load::texture("assets/img/selector/extreme.png");

  font = asw::load::font("assets/fonts/ariblk.ttf", 24);

  click = asw::load::sample("assets/sfx/click.wav");
}

void LevelSelect::update() {
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
      }
    }
  } else if (collision(MouseListener::x, MouseListener::x, 250, 1050,
                       MouseListener::y, MouseListener::y, 185, 785) ||
             KeyListener::keyDown[SDL_SCANCODE_RETURN]) {
    if (MouseListener::mouse_pressed & 1 ||
        KeyListener::keyDown[SDL_SCANCODE_RETURN]) {
      setNextState(StateEngine::STATE_GAME);
    }
  }
}

void LevelSelect::draw() {
  // Background
  asw::draw::sprite(levelSelect, 0, 0);

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

  // Draw difficulty demos
  if (difficulty == 4) {
    asw::draw::sprite(difficultyImages[0], 250, 185);
  } else if (difficulty == 6) {
    asw::draw::sprite(difficultyImages[1], 250, 185);
  } else if (difficulty == 8) {
    asw::draw::sprite(difficultyImages[2], 250, 185);
  } else if (difficulty == 10) {
    asw::draw::sprite(difficultyImages[3], 250, 185);
  }
}
