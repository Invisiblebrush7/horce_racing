/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

/* Constants */
#define TRUE 1
#define FALSE 0
#define MAX_LEN 20 // Max length for names
#define MAX_NUM 10 // Max number of horses
#define MIN_NUM 2 // Min number of horses
int numHorsesGlobal = MIN_NUM;

typedef struct globalInfo{
  char names[MAX_NUM][MAX_LEN];
  int personalHorse;
  int bet;
  int credits;
  int finalPositions[MAX_NUM];
  int start; // If start == 0, race hasnt started;
} globalInfo;

typedef struct Horse{
  int myPosition;
  char myName[MAX_LEN];
  int id;
} Horse;



globalInfo info;

int winningCondition(int horsePosition){
  
  if(horsePosition >= 15){
    return TRUE;
  }
  return FALSE;
}

void* horseThread( void* args ){
  Horse *myHorse = (Horse *)args;
  while(info.start == 0){}

  printf("-----%s starts to run!----\n", myHorse->myName);
  while(info.start == 1){
    myHorse->myPosition += rand() % 6;
    if(winningCondition(myHorse->myPosition) && info.start != 0){
      info.start = 0;
      printf("\n");
      printf("%s has made it to the end!\n", myHorse->myName);
      printf("\n");
      info.finalPositions[myHorse->id] = 15;
    } else {
      info.finalPositions[myHorse->id] = myHorse->myPosition;
    }
    sleep(2);
  }
  return NULL;
}


int main(void) {
  // How many horses are there in the race
  printf("--------------------------------\n");
  printf("Horse Racing\n");
  printf("How many horses are allowed? (Min: %d): ", MIN_NUM);
  scanf("%d", &numHorsesGlobal);
  while(numHorsesGlobal > MAX_NUM || numHorsesGlobal < MIN_NUM){
    printf("Should be between %d and %d: ", MIN_NUM, MAX_NUM);
    scanf("%d", &numHorsesGlobal);
  }
  fflush(stdin);
  
  printf("--------------------------------\n");



  // Important Vars

  Horse horses[numHorsesGlobal];
  info.credits = 500;
  info.start = 0;
  pthread_t myThreads[numHorsesGlobal];


  // Naming the Horses
  Horse *ptr = horses;

  printf("The Max Length for each name should be %d\n", MAX_LEN);
  for(int i = 0; i < numHorsesGlobal; i++){
    printf("Enter the name for horse [%d]\n", i + 1);
    scanf("%s", ptr->myName);
    while(strlen(ptr->myName) > MAX_LEN){
      printf("Max: %d: ", MAX_LEN);
      scanf("%s", ptr->myName);
    }
    ptr->id = i;
    ptr->myPosition = 0;
    fflush(stdin);
    strcpy(info.names[i], ptr->myName);
    ptr++;
  }

  //Start Game
  while(info.credits > 0){
    printf("\e[1;1H\e[2J");
    // Cleaning old data
    int *ptrPos = info.finalPositions;
    ptr = horses;
    for(int i = 0; i < numHorsesGlobal; i++){
      *ptrPos = 0;
      ptr->myPosition = 0;
      ptr++;
      ptrPos++;
    }

    // Assigning the user's horse and bet
    printf("--------------------------------\n");
    printf("Lets assign your bet\n");
    ptr = horses;

    for(int i = 0; i < numHorsesGlobal; i++){
      printf("[%d].- %s\n", ptr->id, ptr->myName);
      ptr++;
    }
    printf("Which horse do you want to bet on? (Number): ");
    scanf("%d", &info.personalHorse);
    while(info.personalHorse > numHorsesGlobal || info.personalHorse < 0){
      printf("Range should be [ 0, %d ] ", numHorsesGlobal);
      scanf("%d", &info.personalHorse);
    }
    fflush(stdin);
    printf("You have: $%d\n", info.credits);
    printf("How much do you want to use?: ");
    scanf("%d", &info.bet);
    while(info.credits - info.bet < 0 || info.bet < 0){
      printf("You dont have enough money for that! Try again: ");
      scanf("%d", &info.bet);
    }
    info.credits -= info.bet;
    fflush(stdin);
    printf("\e[1;1H\e[2J");

    // Nice printing of user's horse
    printf("------------------------------------\n");
    printf("              My Horse\n");
    printf("Name: %s\n", info.names[info.personalHorse]);
    printf("Id: %d\n", info.personalHorse);
    printf("Bet: $%d\n", info.bet);
    printf("------------------------------------\n");



    printf("\n");
    printf("\n");
    printf("Start Race\n");
    printf("3...\n");
    sleep(1);
    printf("2...\n");
    sleep(1);
    printf("1...\n");
    sleep(1);

    for(int i = 0; i < numHorsesGlobal; i++){
      /*pthread_create(mythread, NULL, myFunction, args); */
      pthread_create(&myThreads[i], NULL, horseThread, &horses[i]);
    }
    info.start = 1;
    for(int i = 0; i < numHorsesGlobal; i++){
      pthread_join(myThreads[i], NULL);
    }

    // Priting final positions
    ptrPos = info.finalPositions;
    printf("-----------Scoreboard-----------\n");
    for(int i = 0; i < numHorsesGlobal; i++){
      printf("Final position for Horse [%d] -> %d\n", i, *ptrPos);
      ptrPos++;
    }
    ptr = horses;
    for(int i = 0; i < numHorsesGlobal; i++){
      if(ptr->id == info.personalHorse && ptr->myPosition >=15){
        info.credits += (info.bet * 2);
      }
      ptr++;
    }

    sleep(5);
  }
  printf("\e[1;1H\e[2J");
  printf("Thanks for playing!\n");

  return TRUE;
}