#ifndef BUTTON_H
#define BUTTON_H

#include "globals.h"

#include <asw/asw.h>

class Button {
 public:
  Button();
  Button(int newX, int newY, int newWidth, int newHeight);

  void setImages(const std::string& path1, const std::string& path2);

  void setHover(bool newHover);
  bool getHover();

  void draw();

  void setPosition(int newX, int newY);

  bool checkHover();

  int getX();
  int getY();

 private:
  int height;
  int width;

  int x;
  int y;

  bool hover;

  asw::Texture image[2];
};

#endif
