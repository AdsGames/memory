#ifndef GLOBALS_H
#define GLOBALS_H

#include <allegro.h>
#include <string>
#include <time.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "fmod/fmod.h"
#include "fmod/fmod_errors.h" 

using namespace std;

extern int numberSelected;
extern int cardSelected1;
extern int cardSelected2;

//Resolution X
extern int resDiv;

// Function to check for collision
bool collision(float xMin1, float xMax1, float xMin2, float xMax2, float yMin1, float yMax1, float yMin2, float yMax2);

//Random number generator. Use int random(lowest,highest);
int random(int newLowest, int newHighest);

//Convert int to string 
string convertInt(int number);

//Convert bool to string
string convertBool(bool boolean);

//Convert string to int 
int convertString(string newString);

//Fade in
void fade_in(BITMAP* bmp_orig, int speed);

//Fade out
void fade_out(int speed);

#endif
