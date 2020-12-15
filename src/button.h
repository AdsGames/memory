#ifndef BUTTON_H
#define BUTTON_H

#include "globals.h"

using namespace std;

class Button {
 public:
  Button(int newX, int newY, int newWidth, int newHeight);
  ~Button();

  void setImages(char newImage1[], char newImage2[]);

  void setHover(bool newHover);
  bool getHover();

  void draw(BITMAP* tempBitmap);
  void drawNewSprite(BITMAP* tempBitmap, BITMAP* spriteToDraw);

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

  BITMAP* image[2];
};

#endif
