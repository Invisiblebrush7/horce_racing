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
int numHorsesGlobal = 5;

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
    sleep(2);
    if(winningCondition(myHorse->myPosition) && info.start != 0){
      info.start = 0;
      printf("\n");
      printf("%s has made it to the end!\n", myHorse->myName);
      printf("\n");
      info.finalPositions[myHorse->id] = 15;
    } else {
      info.finalPositions[myHorse->id] = myHorse->myPosition;
    }
  }
  return NULL;
}


int main(void) {
  // Important Vars

  Horse horses[numHorsesGlobal];
  info.credits = 500;
  info.start = 0;
  pthread_t myThreads[numHorsesGlobal];

  // How many horses are there in the race
  printf("--------------------------------\n");
  printf("Horse Racing\n");
  printf("How many horses are allowed? (Min: 5): ");
  scanf("%d", &numHorsesGlobal);
  fflush(stdin);
  printf("--------------------------------\n");

  // Naming the Horses
  Horse *ptr = horses;

  printf("The Max Length for each name should be %d\n", MAX_LEN);
  for(int i = 0; i < numHorsesGlobal; i++){
    printf("Enter the name for horse [%d]\n", i + 1);
    scanf("%s", ptr->myName);
    ptr->id = i;
    ptr->myPosition = 0;
    fflush(stdin);
    strcpy(info.names[i], ptr->myName);
    ptr++;
  }
  printf("\e[1;1H\e[2J");
  // Assigning the user's horse and bet
  printf("--------------------------------\n");
  printf("Now, lets assign your bet\n");
  ptr = horses;

  for(int i = 0; i < numHorsesGlobal; i++){
    printf("[%d].- %s\n", ptr->id, ptr->myName);
    ptr++;
  }
  printf("Which horse do you want to bet on? (Number): ");
  scanf("%d", &info.personalHorse);
  fflush(stdin);
  printf("You have: $%d\n", info.credits);
  printf("How much do you want to use?: ");
  scanf("%d", &info.bet);
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
  int *ptrPositions = info.finalPositions;
  for(int i = 0; i < numHorsesGlobal; i++){
    printf("Final position for Horse [%d] -> %d\n", i, *ptrPositions);
    ptrPositions++;
  }

  return TRUE;
}