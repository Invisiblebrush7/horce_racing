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
#define MAX_LEN 10
#define MIN_HORSES 5
#define MAX_HORSES 12

typedef struct Horse{
  char name[MAX_LEN];
  struct Horse * nxt;
  struct Horse * prv;
}Horse;

typedef struct Race{
  Horse * head;
  int numOfHorses;
} Race;


Race * newRace();
void addHorse(Race *);
void deleteHorse(Race *);
void printHorses(Race *);
