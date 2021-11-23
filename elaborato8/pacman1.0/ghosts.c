#define GHOSTS_STUD
#ifdef GHOSTS_STUD


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "ghosts.h"
#include "pacman.h"
#include "matrix.h"
#include "global.h"

struct ghost{
    struct position pos; 
    unsigned int dir;
    unsigned int STATE;
    unsigned int id;
};

struct ghosts{
    unsigned int n;
    char **arena;
    unsigned int nrows;
    unsigned int ncols;
    struct ghost *fantasma;
};

/* Create the ghosts data structure */
struct ghosts *ghosts_setup(unsigned int num_ghosts) {
    srand(time(NULL));
    unsigned int k = (unsigned int) (rand()*1 + 10) % 2 == 0 ? 1 : -1;
    unsigned int l = (unsigned int) (rand()*1 + 10) % 2 == 0 ? 1 : -1;
    struct position UNK_POSITION = {k,l};
    register int i;
    struct ghosts *G=(struct ghosts*) malloc(sizeof(struct ghosts*));
    if(G != NULL){
        G->n = num_ghosts;
        G->fantasma = (struct ghost*) malloc(sizeof(struct ghost*));
        for(i = 0; i < num_ghosts; ++i){
            G->fantasma->pos = UNK_POSITION;
            G->fantasma->dir = UNK_DIRECTION;
        }
    }
    return G;
}

/* Destroy the ghost data structure */
void ghosts_destroy(struct ghosts *G) {
    if(G != NULL)
        free(G);
    return;
    
}

/* Set the arena (A) matrix */
void ghosts_set_arena(struct ghosts *G, char **A, unsigned int nrow, 
                                                      unsigned int ncol) {
    if(G != NULL){
        G->arena = A;
        G->nrows = nrow;
        G->ncols = ncol;
    }
    return;                                                      
}

/* Set the position of the ghost id. */
void ghosts_set_position(struct ghosts *G, unsigned int id, struct position pos) {
    if(G != NULL && G->fantasma->id >= 0 && G->fantasma->id < G->n){
        G->fantasma[id].pos = pos;
    }
    return;
}

/* Set the status of the ghost id. */
void ghosts_set_status(struct ghosts *G, unsigned int id, enum ghost_status status) {
    if(G != NULL && G->fantasma->id >= 0 && G->fantasma->id < G->n){
        G->fantasma[id].STATE = status;   
    }
    return;
}

/* Return the number of ghosts */
unsigned int ghosts_get_number(struct ghosts *G) {
    if(G != NULL)
        return G->n;
    return 0;
}

/* Return the position of the ghost id. */
struct position ghosts_get_position(struct ghosts *G, unsigned int id) {
    struct position p;
    if(G != NULL && G->fantasma->id >= 0 && G->fantasma->id < G->n){
        p = G->fantasma[id].pos;
    }
    return p;

}

/* Return the status of the ghost id. */
enum ghost_status ghosts_get_status(struct ghosts *G, unsigned int id) {
    return G->fantasma[id].STATE;
}

/* Move the ghost id (according to its status). Returns the new position */
struct position ghosts_move(struct ghosts *G, struct pacman *P, unsigned int id) {
    struct position p;
    switch(G->fantasma[id].STATE){
        case NORMAL:
            
            break;
        case SCARED_NORMAL:
            
            break;
        case SCARED_BLINKING:
            
            break;
        case EYES:
        
            break;
        default:
            break;
    }
    return p;
}

#endif


