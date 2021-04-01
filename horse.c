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

  /* Deberia user malloc aqui pero idk como */

  strcpy(myHorse->name, "");
  return myHorse;
}

void namingHorses(Race * myRace){
  Horse * ptr = myRace->head;
}

Race * newRace(){
  int numOfHorses = MIN_HORSES;

  Race * myRace = (Race *)malloc(sizeof(Race));
  myRace->head = createHorse();

  printf("How many horses are allowed?\n");
  scanf("%d", &numOfHorses);
  myRace->numOfHorses = numOfHorses;
  Horse * ptr = myRace->head;
  for(int i = 1; i < numOfHorses; i++){
    Horse * newHorse = createHorse();
    ptr->nxt = newHorse;
    newHorse->prv = ptr;
    ptr = ptr->nxt;
  }
  return myRace;
}

void printHorses(Race * myRace){
  Horse * ptr = myRace->head;
  
  int ctr = 1;
  while(ptr){
    printf("Horse %d [%p] - [%p] - [%p] \n", ctr, ptr->prv, ptr, ptr->nxt);
    ptr = ptr->nxt;
    ctr++;
  }


}

void addHorse(Race * myRace){

}


