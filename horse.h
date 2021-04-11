/* Libreria stack 
Aqui van las funciones sin body, constantes y estructuras.
Solo necesitas poner las funciones que quieres usar fuera de la libreria. Aka, si usas una funcion foo1() solamente dentro de la libreria, sin estar en el main, puedes no ponerla en el .h

Race tendra un apuntador al primer caballo.

Race -> [Horse1 -> Horse2 -> HorseN]
Race -> [Horse1 <- Horse2 <- HorseN]

Horse1->nxt = Horse2
Horse1->prv = NULL

Todas las funciones recibiran la carrera como argumento.

Ej:
initRace(myRace)

*/

/* Constants */
#define TRUE 1
#define FALSE 0
#define MAX_LEN 20
#define MIN_HORSES 5
#define MAX_HORSES 12
#define LEN_OF_RACE 10
#define NUM_OF_FUNC 5



typedef struct Horse{
  char name[MAX_LEN];
  struct Horse * nxt;
  struct Horse * prv;
  int id;
  int position;
}Horse;

typedef int (*myFunc)(Horse);

typedef struct User{
  int bet;
  int credits;
  int personalHorseId;
} User;

typedef struct Race{
  Horse * head;
  int numOfHorses;
  int lastId;
  User * myUser;
  // globalInfo
  int start;
  myFunc functions[NUM_OF_FUNC];
} Race;

typedef struct Thread_Args{
  Horse * horse;
  Race * race;
} Thread_Args;




Race * newRace();
User * newUser();
void addHorse(Race *);
void deleteHorse(Race *);
void printHorses(Race *);
void startRace(Race *);