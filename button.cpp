#include "button.h"

using namespace std;

Button::Button( int newX, int newY, int newWidth, int newHeight){
  x = newX;
  y = newY;
  width = newWidth;
  height = newHeight;
}

Button::~Button(){
  delete [] image[0], image[1];
}

void Button::setImages( char newImage1[], char newImage2[]){  
  image[0]= load_bitmap(newImage1, NULL);
  image[1]= load_bitmap(newImage2, NULL);
}

void Button::setHover(bool newHover){
  hover = newHover;
}

bool Button::getHover(){
  hover = checkHover();
  return hover;
}

bool Button::checkHover(){
  if(collision(mouse_x * resDiv, mouse_x * resDiv, x, x + width, mouse_y * resDiv, mouse_y * resDiv, y , y + height)){
    return true;
  }
  else{
    return false;
  }
}

void Button::setPosition(int newX, int newY){
  x = newX;
  y = newY;
}

int Button::getX(){
  return x;
}
       
int Button::getY(){
  return y;
}

void Button::draw(BITMAP* tempBitmap){  
  if(getHover()){
    stretch_sprite( tempBitmap, image[1], x, y, width, height);
  }
  else{
    stretch_sprite( tempBitmap, image[0], x, y, width, height);
  }                              
}
