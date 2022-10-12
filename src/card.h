#ifndef CARD_H
#define CARD_H

#include <asw/asw.h>
#include <time.h>

#include "globals.h"

class card {
 public:
  card(int newX, int newY, int newType, int newSize);
  ~card();

  void logic();
  void draw();

  void deselect();
  void match();
  void setType(int newType);

  bool getSelected();
  bool getMatched();
  int getType();
  bool getAnimationDone();
  bool getOffScreen();

 private:
  asw::Texture image[2];

  asw::Sample card_flip;
  asw::Sample whoosh;

  int x;
  int y;

  int width;
  int height;

  int type;

  // If selected or not
  bool selected;

  // The turning animation is done
  bool animationDone;

  // True when picture side up
  bool flipped;

  // True when a match is made
  bool matched;

  // First one around on the animation back
  clock_t time_clicked;
};

#endif
