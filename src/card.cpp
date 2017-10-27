#include "card.h"

// Constructor
card::card(int newX, int newY, int newType, int newSize){
  x = newX;
  y = newY;

  type = newType;

  selected = false;
  matched = false;
  animationDone = true;
  flipped = false;

  width = newSize;
  height = newSize;

  image[0] = load_bitmap("img/cards/card_large.png", NULL);
  std::string fileName = "img/cards/card_large_flip_" + convertInt(type) + ".png";
  image[1] = load_bitmap(fileName.c_str(), NULL);

  card_flip = load_sample("sfx/card_flip.wav");
  whoosh = load_sample("sfx/whoosh.wav");
}

// Deconstructor
card::~card(){

}

// Set selected
void card::deselect(){
  time_clicked = clock();
  selected = false;
  play_sample( card_flip, 255, 125, 1000, 0);
  flipped = true;
  animationDone = false;
}

// Set matched
void card::match(){
  if( !matched){
    matched = true;
    play_sample( whoosh, 255, 125, 1000, 0);
  }
}

// Set card to new type
void card::setType(int newType){
  type = newType;
  std::string fileName = "img/cards/card_large_flip_" + convertInt(type) + ".png";
  image[1] = load_bitmap(fileName.c_str(), NULL);
}

// If selected
bool card::getSelected(){
  return selected;
}

// Return matched
bool card::getMatched(){
  return matched;
}

// Return type
int card::getType(){
  return type;
}

// Return animationDone
bool card::getAnimationDone(){
  return animationDone;
}

// Return if off the screen
bool card::getOffScreen(){
  if(x < 0 - image[0] -> w || x > 1280 + image[0] -> w || y < 0 - image[0] -> h || y > 960 + image[0] -> h){
    return true;
  }
  return false;
}

// Logic
void card::logic(){
  if( mouse_b & 1 && numberSelected < 2){
    if( collision(mouse_x * resDiv, mouse_x * resDiv, x, x + width, mouse_y * resDiv, mouse_y * resDiv, y , y + height) && !selected){
      time_clicked = clock();
      play_sample( card_flip, 255, 125, 1000, 0);
      selected = true;
      flipped = false;
      animationDone = false;
    }
  }

  if( matched){
    if(x < 1280 / 2)
      x -= 15;
    else
      x += 15;
    if(y < 960 / 2)
      y -= 15;
    else
      y += 15;
  }
}

// Draw
void card::draw( BITMAP* tempBitmap){
  clock_t timeElapsed = (clock() - time_clicked);
  if(selected){
    if( !animationDone){
      if(!flipped){
        stretch_sprite( tempBitmap, image[0], x + timeElapsed/2, y, width - timeElapsed, height);
        if(timeElapsed > width){
          flipped = true;
          time_clicked = clock();
        }
      }
      else{
        stretch_sprite( tempBitmap, image[1], x + width/2 - timeElapsed/2, y, timeElapsed, height);
        if(timeElapsed > width)
          animationDone = true;
      }
    }
    else{
      stretch_sprite( tempBitmap, image[1], x, y, width, height);
    }
  }
  else{
    if( !animationDone){
      if( flipped){
        stretch_sprite( tempBitmap, image[1], x + timeElapsed/2, y, width - timeElapsed, height);
        if(timeElapsed > width){
          flipped = false;
          time_clicked = clock();
        }
      }
      else{
        stretch_sprite( tempBitmap, image[0], x + width/2 - timeElapsed/2, y, timeElapsed, height);
        if(timeElapsed > width)
          animationDone = true;
      }
    }
    else{
      stretch_sprite( tempBitmap, image[0], x, y, width, height);
    }
  }
}
