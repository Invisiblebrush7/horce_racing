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

Horse * createHorse(){
  Horse * myHorse = (Horse *)malloc(sizeof(Horse));
  myHorse->prv = NULL;
  myHorse->nxt = NULL;
  myHorse->id = -1;

  /* Deberia user malloc aqui pero idk como */
  strcpy(myHorse->name, "");

  return myHorse;
}

void nameHorse(Horse * ptr){
    printf("Enter the name for the horse %d: ", ptr->id);
    scanf("%s", ptr->name);
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

Race * newRace(){
  printf("\e[1;1H\e[2J");
  int numOfHorses = MIN_HORSES;

  Race * myRace = (Race *)malloc(sizeof(Race));
  myRace->head = createHorse();
  myRace->numOfHorses = 1;

  printf("How many horses are allowed?\n");
  scanf("%d", &numOfHorses);

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
  return myRace;
}

void printHorses(Race * myRace){
  Horse * ptr = myRace->head;
  
  while(ptr){
    printf("******************************\n");
    printf("%s. Id: %d\n[%p] - [%p] - [%p] \n", ptr->name , ptr->id, ptr->prv, ptr, ptr->nxt);
    printf("\n");
    printf("******************************\n");

    printf("\n");
    ptr = ptr->nxt;
  }
  printf("Number of Horses: %d\n", myRace->numOfHorses);
  printf("Last Id: %d\n", myRace->lastId);    
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


