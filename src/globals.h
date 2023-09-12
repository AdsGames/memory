#ifndef GLOBALS_H
#define GLOBALS_H

extern int numberSelected;

// Function to check for collision
template <typename T>
bool collision(T xMin1,
               T xMax1,
               T xMin2,
               T xMax2,
               T yMin1,
               T yMax1,
               T yMin2,
               T yMax2) {
  if (xMin1 < xMax2 && yMin1 < yMax2 && xMin2 < xMax1 && yMin2 < yMax1) {
    return true;
  }
  return false;
}

// Random number generator.
int random(int low, int high);

#endif
