#include "globals.h"

int numberSelected = 0;
int cardSelected1 = 0;
int cardSelected2 = 0;

// Resolution X
int resDiv;

// Function to check for collision
bool collision(float xMin1,
               float xMax1,
               float xMin2,
               float xMax2,
               float yMin1,
               float yMax1,
               float yMin2,
               float yMax2) {
  if (xMin1 < xMax2 && yMin1 < yMax2 && xMin2 < xMax1 && yMin2 < yMax1) {
    return true;
  }
  return false;
}

// Random number generator. Use int random(lowest,highest);
int random(int newLowest, int newHighest) {
  int lowest = newLowest, highest = newHighest;
  int range = (highest - lowest) + 1;
  int randomNumber = lowest + int(range * rand() / (RAND_MAX + 1.0));
  return randomNumber;
}

// Convert int to string
std::string convertInt(int number) {
  std::stringstream ss;
  ss << number;
  return ss.str();
}

// Convert bool to string
std::string convertBool(bool boolean) {
  std::stringstream ss;
  ss << boolean;
  return ss.str();
}

// Convert string to int
int convertString(std::string newString) {
  int result;
  std::stringstream(newString) >> result;
  return result;
}

// Fade in
void fade_in(BITMAP* bmp_orig, int speed) {
  BITMAP* bmp_buff;

  if ((bmp_buff = create_bitmap(SCREEN_W, SCREEN_H))) {
    int a;
    if (speed <= 0)
      speed = 16;

    for (a = 0; a < 256; a += speed) {
      clear(bmp_buff);
      set_trans_blender(0, 0, 0, a);
      draw_trans_sprite(bmp_buff, bmp_orig, 0, 0);
      vsync();
      blit(bmp_buff, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    destroy_bitmap(bmp_buff);
  }
  blit(bmp_orig, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}

// Fade out
void fade_out(int speed) {
  BITMAP *bmp_orig, *bmp_buff;

  if ((bmp_orig = create_bitmap(SCREEN_W, SCREEN_H))) {
    if ((bmp_buff = create_bitmap(SCREEN_W, SCREEN_H))) {
      int a;
      blit(screen, bmp_orig, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
      if (speed <= 0)
        speed = 16;

      for (a = 255 - speed; a > 0; a -= speed) {
        clear(bmp_buff);
        set_trans_blender(0, 0, 0, a);
        draw_trans_sprite(bmp_buff, bmp_orig, 0, 0);
        vsync();
        blit(bmp_buff, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
      }
      destroy_bitmap(bmp_buff);
    }
    destroy_bitmap(bmp_orig);
  }
  rectfill(screen, 0, 0, SCREEN_W, SCREEN_H, makecol(0, 0, 0));
}
