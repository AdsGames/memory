#include "globals.h"

#include <sstream>

int numberSelected = 0;
int cardSelected1 = 0;
int cardSelected2 = 0;

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
int random(int lowest, int highest) {
  int range = (highest - lowest) + 1;
  return lowest + int(range * rand() / (RAND_MAX + 1.0));
}

// Convert int to string
std::string convertInt(int number) {
  std::stringstream ss;
  ss << number;
  return ss.str();
}
