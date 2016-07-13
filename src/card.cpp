#include "card.h"

volatile long card::speed_counter = 0;
bool card::first = false;
int card::resetValue = 1;

// Constructor
card::card(int newX, int newY, int newType, int newSize){    
  x = newX;
  y = newY;
  
  type = newType;
  size = newSize;
  
  selected = false;
  matched = false;
  animationDone = true;
  first = true;
  
  width = newSize;
  height = newSize;
  
  resetValue = width+10;
  
  image[0] = load_bitmap("img/cards/card_large.bmp", NULL);
  string fileName = "img/cards/card_large_flip_" + convertInt(type) + ".bmp";
  image[1] = load_bitmap(fileName.c_str(), NULL);
  
  card_flip = load_sample("sfx/card_flip.wav");
  whoosh = load_sample("sfx/whoosh.wav");
  
  LOCK_VARIABLE(speed_counter);
	LOCK_FUNCTION(increment_speed_counter);
	install_int_ex(increment_speed_counter, BPS_TO_TIMER(width * 4));
}

// Deconstructor
card::~card(){

}

// Animation ticker
void card::increment_speed_counter(){
  speed_counter++;
  if(speed_counter > resetValue){
    speed_counter = -10;
  }
  if(speed_counter < 0){
    speed_counter = -10;
  }
}END_OF_FUNCTION(increment_speed_counter);

// Set selected
void card::setSelected(bool newSelected){
  selected = newSelected;
  play_sample( card_flip, 255, 125, 1000, 0);
  if(!selected){
    flipped = true;
    animationDone = false;
    speed_counter = 0;
    first = true;
  }
}

// Set matched
void card::setMatched(bool newMatched){
  matched = newMatched;
  play_sample( whoosh, 255, 125, 1000, 0);
}

// Set card to new type
void card::setType(int newType){
  type = newType;
  string fileName = "img/cards/card_large_flip_" + convertInt(type) + ".bmp";
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
  if(mouse_b & 1 && numberSelected < 2 && speed_counter < 0){
    if(collision(mouse_x * resDiv, mouse_x * resDiv, x, x + size, mouse_y * resDiv, mouse_y * resDiv, y , y + size) && !selected){
      play_sample( card_flip, 255, 125, 1000, 0);
      selected = true;
      flipped = false;
      animationDone = false;
      speed_counter = 0;
    }
  }
  
  if(matched){
    if(x < 1280/2){
      x-=15;
    }
    else{
      x+=15;
    }
    if(y < 960/2){
      y-=15; 
    }
    else{
      y+=15; 
    }
  }
}

// Draw
void card::draw( BITMAP* tempBitmap){  
  if(selected){
    if(!animationDone && !flipped){
      stretch_sprite( tempBitmap, image[0], x + speed_counter/2, y, width - speed_counter, height);
      if(speed_counter > width){
        flipped = true;
        speed_counter = 0;
      }
    }
    else if(!animationDone && flipped){
      stretch_sprite( tempBitmap, image[1], x + width/2 - speed_counter/2, y, speed_counter, height);  
      if(speed_counter > width){
        animationDone = true;
      }
    }
    else{
      stretch_sprite( tempBitmap, image[1], x, y, width, height);
    }
  }
  else{
    if(!animationDone && flipped){
      stretch_sprite( tempBitmap, image[1], x + speed_counter/2, y, width - speed_counter, height);
      if(speed_counter > width){
        flipped = false;
        if(first == true){
          first = false; 
        }
        else{
          speed_counter = 0;
        }
      }
    }
    else if(!animationDone && !flipped){
      stretch_sprite( tempBitmap, image[0], x + width/2 - speed_counter/2, y, speed_counter, height);
      if(speed_counter > width){
        animationDone = true;
      }
    }
    else{
      stretch_sprite( tempBitmap, image[0], x, y, width, height);
    }
  }  
}
