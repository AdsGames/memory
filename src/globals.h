#ifndef GLOBALS_H
#define GLOBALS_H

#include <allegro.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

extern int numberSelected;
extern int cardSelected1;
extern int cardSelected2;

// Resolution X
extern int resDiv;

// Function to check for collision
bool collision(float xMin1,
               float xMax1,
               float xMin2,
               float xMax2,
               float yMin1,
               float yMax1,
               float yMin2,
               float yMax2);

// Random number generator. Use int random(lowest,highest);
int random(int newLowest, int newHighest);

// Convert int to string
std::string convertInt(int number);

// Convert bool to string
std::string convertBool(bool boolean);

// Convert string to int
int convertString(std::string newString);

// Fade in
void fade_in(BITMAP* bmp_orig, int speed);

// Fade out
void fade_out(int speed);

#endif
