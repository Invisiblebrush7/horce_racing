#include "horse.h"
#include <stdio.h>

// clang-7 main.c horse.c -o my_bin -lm -pthread

int main(){
  Race * myRace = newRace();
  printf("newHorse [%p]\n", myRace->head);
  printHorses(myRace);
  return TRUE;
}