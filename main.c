#include "horse.h"
#include <stdio.h>
#include <unistd.h>

// clang-7 main.c horse.c -o my_bin -lm -pthread

int main(){
  Race * myRace = newRace();
  /*
  addHorse(myRace);
  printHorses(myRace);
  sleep(2);
  */
  deleteHorse(myRace);
  printHorses(myRace);
  return TRUE;
}