#include "button.h"

#include <asw/util/MouseListener.h>

Button::Button() : Button(0, 0, 0, 0) {}

Button::Button(int newX, int newY, int newWidth, int newHeight) {
  x = newX;
  y = newY;
  width = newWidth;
  height = newHeight;
}

void Button::setImages(const std::string& path1, const std::string& path2) {
  image[0] = asw::load::texture(path1);
  image[1] = asw::load::texture(path2);
}

void Button::setHover(bool newHover) {
  hover = newHover;
}

bool Button::getHover() {
  hover = checkHover();
  return hover;
}

bool Button::checkHover() {
  if (collision(MouseListener::x, MouseListener::x, x, x + width,
                MouseListener::y, MouseListener::y, y, y + height)) {
    return true;
  } else {
    return false;
  }
}

void Button::setPosition(int newX, int newY) {
  x = newX;
  y = newY;
}

int Button::getX() {
  return x;
}

int Button::getY() {
  return y;
}

void Button::draw() {
  if (getHover()) {
    asw::draw::stretchSprite(image[1], x, y, width, height);
  } else {
    asw::draw::stretchSprite(image[0], x, y, width, height);
  }
}
