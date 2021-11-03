#include <math.h>

#define DELTA(a,b,c) (pow((b),2) - 4 * (a) * (c))       /*Calcolo del discriminante*/
#define NUM_OF_ROOTS(a,b,c) ((DELTA(a,b,c) > 0 ? 2 : DELTA(a,b,c) == 0 ? 1 : 0)) /*Controllo sul valore del delta per trovare il nummero delle radici*/
#define X1(a,b,c) ((-(b) + sqrt(DELTA(a,b,c))) / (2 * (a))) /*Calcolo di x1*/
#define X2(a,b,c) ((-(b) - sqrt(DELTA(a,b,c))) / (2 * (a))) /*Calcolo di x2*/
#define ROOT1(a,b,c) (X1(a,b,c) >= X2(a,b,c) ? X1(a,b,c) : X2(a,b,c)) /*Stampa radice maggiore*/
#define ROOT2(a,b,c) (X1(a,b,c) <= X2(a,b,c) ? X1(a,b,c) : X2(a,b,c)) /*Stampa radice minore*/
#define EXTREME_POINT(a,b,c) (-(b) / (2 * (a))) /*Calcolo punto di massimo o di minimo*/
#define MAXIMUM_POINT(a,b,c) (2 * (a) > 0 ? 0 : 1) /*Controllo se è di massimo o di minimo*/
#define IMMAGINARY_PART(a,b,c) (sqrt(-DELTA(a,b,c)) / (2 * (a))) /*Calcolo della parte immaginaria della radice complessa*/
