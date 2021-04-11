/* Aqui van las funciones para crear el caballo y todo. 
  Requiere la "libreria" de horse.h ya que ahi esta
  definido el nodo, funciones y constantes.


  Race -> [Horse1 -> Horse2 -> HorseN]
  Race -> [Horse1 <- Horse2 <- HorseN]


*/

/* Local Library */
#include "horse.h"

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


int goodOutcome1(Horse myHorse){
  int randomNumber = rand() % 6;
  printf("++ %s has wings now!\n", myHorse.name);
  return randomNumber;
}
int goodOutcome2(Horse myHorse){
  int randomNumber = rand() % 5;
  printf("++ %s has one more leg now!\n", myHorse.name);
  return randomNumber;
}
int goodOutcome3(Horse myHorse){
  int randomNumber = rand() % 4;
  printf("++ %s got more will to live!\n", myHorse.name);
  return randomNumber;
}
int badOutcome1(Horse myHorse){
  int randomNumber = rand() % 3;
  printf("-- %s has encountered a snake! It has to wait now!\n", myHorse.name);
  sleep(randomNumber);
  return 0;
}
int badOutcome2(Horse myHorse){
  int randomNumber = rand() % 3;
  printf("-- %s heard some music! It has to dance now!\n", myHorse.name);
  sleep(randomNumber);
  return 0;
}

User * newUser(){
  User * myUser = (User*)malloc(sizeof(User));
  myUser->bet = 0;
  myUser->credits = 1000;
  myUser->personalHorseId = 0;
  return myUser;
}

Horse * createHorse(){
  Horse * myHorse = (Horse *)malloc(sizeof(Horse));
  myHorse->prv = NULL;
  myHorse->nxt = NULL;
  myHorse->id = -1;
  myHorse->position = 0;

  /* Deberia user malloc aqui pero idk como */
  strcpy(myHorse->name, "");
  return myHorse;
}

int winningCondition(int horsePosition){
  
  if(horsePosition >= LEN_OF_RACE){
    return TRUE;
  }
  return FALSE;
}

void nameHorse(Horse * ptr){
  printf("Enter the name for the horse %d: ", ptr->id);
  scanf("%s", ptr->name);
  while(strlen(ptr->name) > MAX_LEN){
    printf("Max Length %d: ", MAX_LEN);
    scanf("%s", ptr->name);
  }  
  printf("\n");  
  fflush(stdin);    
}

void namingHorses(Race * myRace){
  /* Deberia user malloc aqui pero idk como */
  Horse * ptr = myRace->head;
  while(ptr){
    nameHorse(ptr);   
    ptr = ptr->nxt;
  }
}

void * thread(void * _myArgs){
  
  Thread_Args myArgs = *((Thread_Args *)_myArgs);
  Horse * horse = myArgs.horse;
  Race * myRace = myArgs.race;

  while(myRace->start == 0){}

  printf("-----%s starts to run!----\n", horse->name);
  while(myRace->start == 1){
    sleep(1);
    horse->position += myRace->functions[rand() % 5](*horse);
    if(winningCondition(horse->position) && myRace->start != 0){
      myRace->start = 0;
      printf("\n");
      printf("Horse Id: %d\n", horse->id);
      printf("%s has made it to the end!\n", horse->name);
      if(horse->id == myRace->myUser->personalHorseId){
        myRace->myUser->credits += myRace->myUser->bet; 
      } else {
        myRace->myUser->credits -= myRace->myUser->bet; 
      }
      printf("\n");
    }
    sleep(2);
  } 
  return NULL;
}

Race * newRace(){
  int numOfHorses = MIN_HORSES;

  Race * myRace = (Race *)malloc(sizeof(Race));
  myRace->head = createHorse();
  myRace->numOfHorses = 1;
  myRace->myUser = NULL;

  printf("How many horses are allowed?\n>");
  scanf("%d", &numOfHorses);
  while(numOfHorses < MIN_HORSES || numOfHorses>MAX_HORSES){
    printf("Min %d\n", MIN_HORSES);
    printf("Max %d\n", MAX_HORSES);
    printf("How many horses are allowed?\n>");
    scanf("%d", &numOfHorses);    
  }

  Horse * ptr = myRace->head;
  ptr->id = myRace->numOfHorses;

  for(int i = 1; i < numOfHorses; i++){
    myRace->numOfHorses++;

    Horse * newHorse = createHorse();
    newHorse->id = myRace->numOfHorses;
    ptr->nxt = newHorse;
    newHorse->prv = ptr;
    ptr = ptr->nxt;
  }
  myRace->lastId = myRace->numOfHorses;
  namingHorses(myRace);

  myFunc functions[NUM_OF_FUNC] = {goodOutcome1, goodOutcome2, goodOutcome3, badOutcome1, badOutcome2};

  myFunc *ptrFunction = myRace->functions;
  myFunc *ptrFunction2 = functions;
  for(int i = 0; i < NUM_OF_FUNC; i++){
    *ptrFunction = *ptrFunction2;
    ptrFunction++;
    ptrFunction2++;
    /* info.functions[i] = functions[i]; */
  }

  return myRace;  
}

void printHorses(Race * myRace){
  printf("\e[1;1H\e[2J");
  Horse * ptr = myRace->head;
  
  while(ptr){
    printf("------------------------------\n");
    printf("%s. Id: %d\n[%p] - [%p] - [%p] \n", ptr->name , ptr->id, ptr->prv, ptr, ptr->nxt);
    printf("------------------------------\n");

    printf("\n");
    ptr = ptr->nxt;
  }
  printf("Number of Horses: %d\n", myRace->numOfHorses);
  printf("Last Id: %d\n", myRace->lastId);    
}

Horse * searchHorse(int id, Race * myRace){
  Horse * ptr = myRace->head;
  while(ptr){
    if(ptr->id == id){
      return ptr;
    }
    ptr = ptr->nxt;
  }
  return NULL;
}

void printUserHorse(Race * myRace){
  int id = myRace->myUser->personalHorseId;
  Horse * ptr = searchHorse(id, myRace);
  if(ptr){
    printf("------------------------------------\n");
    printf("              My Horse\n");
    printf("Name: %s\n", ptr->name);
    printf("Id: %d\n", ptr->id);
    printf("Bet: $%d\n", myRace->myUser->bet);
    printf("Credits: $%d\n", myRace->myUser->credits);
    printf("------------------------------------\n");
  }
}

void addHorse(Race * myRace){
  printf("\e[1;1H\e[2J");
  printf("--------------------------\n");
  printf("Adding a new horse\n");

  Horse * ptr = myRace->head;
  Horse * prv = myRace->head;
  while(ptr){
    prv = ptr;
    ptr = ptr->nxt;
  }
  ptr = createHorse();
  prv->nxt = ptr;
  ptr->prv = prv;

  myRace->lastId++;
  myRace->numOfHorses++;

  ptr->id = myRace->lastId;
  nameHorse(ptr);
  printf("--------------------------\n");  
}

void cleanHorse(Horse * horse){
  // Deletes all info
  horse->nxt = NULL;
  horse->prv = NULL;
  horse->id = 0;
  strcpy(horse->name, "");
  horse->position = 0;
}

void deleteHorse(Race * myRace){
  Horse * ptr = myRace->head;
  Horse * prv = myRace->head;
  int id;
  printf("\e[1;1H\e[2J");
  printf("--------------------------\n");
  printf("Deleting a horse\n");  
  
  printf("Enter horse id: ");
  scanf("%d", &id);

  while(ptr){
    if(ptr->id == id){
      printf("Found a match! Now deleting...\n");
      if(!ptr->nxt){ // Aka, the last horse
        prv->nxt = NULL;
      } else if(!ptr->prv){ // Aka, the first horse
        myRace->head = ptr->nxt;
        myRace->head->prv = NULL;
      } else { // Somewhere in the middle
        prv->nxt = ptr->nxt;
        ptr->nxt->prv = ptr->prv;
      }
      cleanHorse(ptr);
      free(ptr);
      myRace->numOfHorses--;
    }
    prv = ptr;
    ptr = ptr->nxt;
  }
  printf("--------------------------\n");  
  printf("\n");
  printf("\n");
}

void resetPositions(Race *myRace){
  Horse * ptr = myRace->head;
  while(ptr){
    ptr->position = 0;
    ptr = ptr->nxt;
  }
}

void assignUserSelection(Race *myRace){
  int bet = 0;
  int id = 0;
  printHorses(myRace);
  while(!searchHorse(id, myRace)){
    printf("\e[1;1H\e[2J");
    printHorses(myRace);
    printf("Select your Horse (Id):");
    scanf("%d", &id);    
  }
  printf("\n");
  while(bet > myRace->myUser->credits || bet <= 0){
    printf("Credits: $%d\n", myRace->myUser->credits);
    printf("Now, select your bet:");
    scanf("%d", &bet);
  }
  myRace->myUser->bet = bet;
  myRace->myUser->personalHorseId = id;
}

void startRace(Race * myRace){
  resetPositions(myRace);
  assignUserSelection(myRace);
  printf("\e[1;1H\e[2J");
  printUserHorse(myRace);
  sleep(1);
  printf("Starting the race with %d horses\n", myRace->numOfHorses);
  printf("\n");
  printf("\n");
  printf("Start Race\n");
  printf("3...\n");
  sleep(1);
  printf("2...\n");
  sleep(1);
  printf("1...\n");
  sleep(1);
  pthread_t myThreads[MAX_HORSES];
  
  Thread_Args * myArgs = (Thread_Args *)malloc(sizeof(Thread_Args));
  myArgs->race = myRace;
  Horse * ptr = myRace->head;
  
  for(int i = 0; i < myRace->numOfHorses; i++){
    if(ptr){
      myArgs->horse = ptr;
      pthread_create(&myThreads[i], NULL, thread, myArgs);
      sleep(1);
      ptr = ptr->nxt;
    }
  }
  
  myRace->start = 1;
  for(int i = 0; i < myRace->numOfHorses; i++){
    pthread_join(myThreads[i], NULL);
  }    

}