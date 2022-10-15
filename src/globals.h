#ifndef GLOBALS_H
#define GLOBALS_H

extern int numberSelected;

// Function to check for collision
bool collision(float xMin1,
               float xMax1,
               float xMin2,
               float xMax2,
               float yMin1,
               float yMax1,
               float yMin2,
               float yMax2);

// Random number generator.
int random(int low, int high);

#endif
