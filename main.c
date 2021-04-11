#include "horse.h"
#include <stdio.h>
#include <unistd.h>

// clang-7 main.c horse.c -o my_bin -lm -pthread

int main(){
  printf("\e[1;1H\e[2J");
  printf("Welcome to the best horse racing game!\n");
  printf("Let's start with some horses...\n");
  sleep(1);
  Race * myRace = newRace();
  User * myUser = newUser();
  myRace->myUser = myUser;
  
  int userOption = 0;
  while(userOption != 5 && myUser->credits > 0){
    sleep(1);
    printf("These are our options:\n");
    printf("\n");
    printf("1. PLAY\n");
    printf("2. VIEW ALL HORSES\n");
    printf("3. ADD A HORSE\n");
    printf("4. DELETE  A HORSE\n");
    printf("5. EXIT\n");
    printf("\n");
    printf("Your info:\n");
    printf("Credits: $%d\n", myRace->myUser->credits);
    printf("Personal Horse: %d\n", myRace->myUser->personalHorseId);
    printf("\n");
    printf("---------------------------\n");
    printf("Select the option you want: ");
    scanf("%d", &userOption);

    switch(userOption){
      case 1:
      startRace(myRace);
      break;
      
      case 2:
      sleep(1);
      printHorses(myRace);
      break;

      case 3:
      sleep(1);
      addHorse(myRace);
      break;

      case 4:
      sleep(1);
      deleteHorse(myRace);
      break;
    }
  }
  if(myUser->credits <= 0){
    printf("\e[1;1H\e[2J");
    printf("You ran out of credits! :( \n");
    printf("Thanks for playing tho\n");
  } else {
    printf("Thanks for playing!\n");
  }
  return TRUE;
}