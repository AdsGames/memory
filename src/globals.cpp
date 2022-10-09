#include "globals.h"

#include <sstream>

int numberSelected = 0;
int cardSelected1 = 0;
int cardSelected2 = 0;
std::string scores[10][2];

// extreme = 10, hard = 8, medium = 6, easy = 4
int difficulty = 4;

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
