#include "globals.h"

#include <time.h>
#include <random>

// Random device
std::mt19937 rng(time(nullptr));

int numberSelected = 0;

// Random number generator
int random(int low, int high) {
  std::uniform_int_distribution<int> dist6(low, high);
  return dist6(rng);
}
