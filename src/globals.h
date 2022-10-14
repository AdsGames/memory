#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>

extern int numberSelected;
extern int cardSelected1;
extern int cardSelected2;

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
int random(int low, int high);

// Convert int to string
std::string convertInt(int number);

#endif
