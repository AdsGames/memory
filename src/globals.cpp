#include "globals.h"

#include <time.h>
#include <random>

// Random device
std::mt19937 rng(time(nullptr));

int numberSelected = 0;

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

// Random number generator
int random(int low, int high) {
  std::uniform_int_distribution<int> dist6(low, high);
  return dist6(rng);
}
