#include "catch-and-run.h"

#include <cstdlib>
#include <ctime>

CatchAndRun::CatchAndRun() {
  // initialize random generatoren
  srand(time(NULL));
}

int CatchAndRun::roll() {
  return (rand() % 6) + 1;
}