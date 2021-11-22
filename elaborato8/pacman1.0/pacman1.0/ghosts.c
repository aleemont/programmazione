#define GHOSTS_STUD
#ifdef GHOSTS_STUD


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "ghosts.h"
#include "pacman.h"
#include "matrix.h"

#define UP -1
#define DOWN 1
#define LEFT -1
#define RIGHT 1

struct ghosts{
    struct position pos; 
    unsigned int dir;
    unsigned int STATE;
    unsigned int id;
};

/* Create the ghosts data structure */
struct ghosts *ghosts_setup(unsigned int num_ghosts) {
    struct ghosts *g=(struct ghosts*) malloc(sizeof(g) * num_ghosts);
    return g;
}

/* Destroy the ghost data structure */
void ghosts_destroy(struct ghosts *G) {
    return;
    
}

/* Set the arena (A) matrix */
void ghosts_set_arena(struct ghosts *G, char **A, unsigned int nrow, 
                                                      unsigned int ncol) {
    return;                                                      
}

/* Set the position of the ghost id. */
void ghosts_set_position(struct ghosts *G, unsigned int id, struct position pos) {
    return;
}

/* Set the status of the ghost id. */
void ghosts_set_status(struct ghosts *G, unsigned int id, enum ghost_status status) {
    return;
}

/* Return the number of ghosts */
unsigned int ghosts_get_number(struct ghosts *G) {
    unsigned int num_ghosts = ;
    return num_ghosts;
}

/* Return the position of the ghost id. */
struct position ghosts_get_position(struct ghosts *G, unsigned int id) {
    struct position p; 
    return p;

}

/* Return the status of the ghost id. */
enum ghost_status ghosts_get_status(struct ghosts *G, unsigned int id) {
    return 0;
}

/* Move the ghost id (according to its status). Returns the new position */
struct position ghosts_move(struct ghosts *G, struct pacman *P, unsigned int id) {
    struct position p; 
    return p;
}

#endif


