#ifndef CARD_H
#define CARD_H

#include "globals.h"

class card{
  public:
    card(int newX, int newY, int newType, int newSize);
    ~card();
    
    void logic();
    void draw(BITMAP* tempBitmap);
    
    void setSelected(bool newSelected);
    void setMatched(bool newMatched);
    void setType(int newType);
    
    bool getSelected();
    bool getMatched();
    int getType();
    bool getAnimationDone();
    bool getOffScreen();
    
    static volatile long speed_counter;
  private:
    BITMAP* image[2];
    SAMPLE* card_flip;
    SAMPLE* whoosh;
    
    int x;
    int y;
    
    int width;
    int height;
    
    int type;
    int size;
    
    //If selected or not
    bool selected;
    
    //The turning animation is done
    bool animationDone;
    
    //True when picture side up
    bool flipped;
    
    //True when a match is made
    bool matched;
    
    //First one around on the animation back
    static bool first;
    static int resetValue;
    static void increment_speed_counter();
};

#endif

