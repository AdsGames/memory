#include "card.h"

#include <asw/util/MouseListener.h>

// Constructor
card::card(int newX, int newY, int newType, int newSize) {
  x = newX;
  y = newY;

  type = newType;

  selected = false;
  matched = false;
  animationDone = true;
  flipped = false;

  width = newSize;
  height = newSize;

  image[0] = asw::load::texture("assets/img/cards/card_large.png");
  std::string fileName =
      "assets/img/cards/card_large_flip_" + convertInt(type) + ".png";
  image[1] = asw::load::texture(fileName.c_str());

  card_flip = asw::load::sample("assets/sfx/card_flip.wav");
  whoosh = asw::load::sample("assets/sfx/whoosh.wav");
}

// Deconstructor
card::~card() {}

// Set selected
void card::deselect() {
  time_clicked = clock();
  selected = false;
  asw::sound::play(card_flip);
  flipped = true;
  animationDone = false;
}

// Set matched
void card::match() {
  if (!matched) {
    matched = true;
    asw::sound::play(whoosh);
  }
}

// Set card to new type
void card::setType(int newType) {
  type = newType;
  std::string fileName =
      "assets/img/cards/card_large_flip_" + convertInt(type) + ".png";
  image[1] = asw::load::texture(fileName);
}

// If selected
bool card::getSelected() {
  return selected;
}

// Return matched
bool card::getMatched() {
  return matched;
}

// Return type
int card::getType() {
  return type;
}

// Return animationDone
bool card::getAnimationDone() {
  return animationDone;
}

// Return if off the screen
bool card::getOffScreen() {
  auto size = asw::util::getTextureSize(image[0]);
  if (x < 0 - size.x || x > 1280 + size.x || y < 0 - size.y ||
      y > 960 + size.y) {
    return true;
  }
  return false;
}

// Logic
void card::logic() {
  if (MouseListener::mouse_pressed & 1 && numberSelected < 2) {
    if (collision(MouseListener::x, MouseListener::x, x, x + width,
                  MouseListener::y, MouseListener::y, y, y + height) &&
        !selected) {
      time_clicked = clock();
      asw::sound::play(card_flip);
      selected = true;
      flipped = false;
      animationDone = false;
    }
  }

  if (matched) {
    if (x < 1280 / 2)
      x -= 15;
    else
      x += 15;
    if (y < 960 / 2)
      y -= 15;
    else
      y += 15;
  }
}

// Draw
void card::draw() {
  clock_t timeElapsed = (clock() - time_clicked);
  if (selected) {
    if (!animationDone) {
      if (!flipped) {
        asw::draw::stretchSprite(image[0], x + timeElapsed / 2, y,
                                 width - timeElapsed, height);
        if (timeElapsed > width) {
          flipped = true;
          time_clicked = clock();
        }
      } else {
        asw::draw::stretchSprite(image[1], x + width / 2 - timeElapsed / 2, y,
                                 timeElapsed, height);
        if (timeElapsed > width)
          animationDone = true;
      }
    } else {
      asw::draw::stretchSprite(image[1], x, y, width, height);
    }
  } else {
    if (!animationDone) {
      if (flipped) {
        asw::draw::stretchSprite(image[1], x + timeElapsed / 2, y,
                                 width - timeElapsed, height);
        if (timeElapsed > width) {
          flipped = false;
          time_clicked = clock();
        }
      } else {
        asw::draw::stretchSprite(image[0], x + width / 2 - timeElapsed / 2, y,
                                 timeElapsed, height);
        if (timeElapsed > width)
          animationDone = true;
      }
    } else {
      asw::draw::stretchSprite(image[0], x, y, width, height);
    }
  }
}
