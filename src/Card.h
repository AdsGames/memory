#ifndef CARD_H
#define CARD_H

#include <asw/asw.h>
#include <asw/util/Timer.h>
#include <time.h>
#include <map>
#include <string>

#include "globals.h"

const double CARD_FLIP_TIME_MS = 250.0;

class Card {
 public:
  Card(int type, int size);

  void logic();
  void draw() const;

  void setPosition(int x, int y);
  void deselect();
  void match();
  void setType(int type);

  bool isSelected() const;
  bool getMatched() const;
  int getType() const;
  bool isAnimationDone() const;
  bool isOffScreen() const;

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

  // Animation timer
  Timer animationTime{};
};

#endif
