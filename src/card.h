#ifndef CARD_H
#define CARD_H

#include <asw/asw.h>
#include <time.h>
#include <map>
#include <string>

#include "globals.h"

const clock_t CARD_FLIP_TIME_MS = 300;

class card {
 public:
  card(int type, int size);

  void logic();
  void draw() const;

  void setPosition(int x, int y);
  void deselect();
  void match();
  void setType(int type);

  bool getSelected() const;
  bool getMatched() const;
  int getType() const;
  bool getAnimationDone() const;
  bool getOffScreen() const;

 private:
  static std::map<int, std::string> cardAssets;
  static std::map<int, asw::Texture> faceImages;
  static asw::Texture backImage;

  asw::Sample cardFlip;
  asw::Sample whoosh;

  int x{0};
  int y{0};

  int width;
  int height;

  int animationWidth;

  int type;

  // If selected or not
  bool selected{false};

  // The turning animation is done
  bool animationDone{true};

  // True when picture side up
  bool flipped{false};

  // True when a match is made
  bool matched{false};

  // First one around on the animation back
  clock_t timeClicked{0};
};

#endif
