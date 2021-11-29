#define GHOSTS_STUD
#ifdef GHOSTS_STUD


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "ghosts.h"
#include "pacman.h"
#include "matrix.h"

#define IS_WALL(A,pos) (A[pos.i][pos.j] == URCORN_SYM || A[pos.i][pos.j] == ULCORN_SYM || \
                        A[pos.i][pos.j] == VWALL_SYM  || A[pos.i][pos.j] == HWALL_SYM  || \
                        A[pos.i][pos.j] == XWALL_SYM)
#define ARENA (G->arena)
#define MAX_ROW ((G->nrows) - 1)
#define MAX_COL ((G->ncols) - 1)
#define POS_I(id) (G->fantasma[id].pos.i)
#define POS_J(id) (G->fantasma[id].pos.j)

/*moves ghost in a direction*/
#define MOVE_UP(id) ((G->fantasma[id].pos.i == 0) ?  (G->fantasma[id].pos.i = MAX_ROW)  : (G->fantasma[id].pos.i -= 1))
#define MOVE_DOWN(id) ((G->fantasma[id].pos.i == MAX_ROW) ? (G->fantasma[id].pos.i = 0) : (G->fantasma[id].pos.i += 1))
#define MOVE_LEFT(id) ((G->fantasma[id].pos.j == 0) ? (G->fantasma[id].pos.j = MAX_COL) : (G->fantasma[id].pos.j -= 1))
#define MOVE_RIGHT(id) ((G->fantasma[id].pos.j == MAX_COL)? (G->fantasma[id].pos.j = 0) : (G->fantasma[id].pos.j += 1))
/*position x or position y of a cell in a direction from ghost*/
#define SHOW_UP(a) ((G->fantasma[a].pos.i == 0) ? (MAX_ROW) : (G->fantasma[a].pos.i - 1))
#define SHOW_DOWN(a) ((G->fantasma[a].pos.i == MAX_ROW)? (0) : (G->fantasma[a].pos.i + 1))
#define SHOW_LEFT(a) ((G->fantasma[a].pos.j == 0) ? (MAX_COL) : (G->fantasma[a].pos.j - 1))
#define SHOW_RIGHT(a) ((G->fantasma[a].pos.j == MAX_COL)? (0) : (G->fantasma[a].pos.j + 1))
/*show cell in a direction*/
#define A(a) ARENA[G->fantasma[a].pos.i][G->fantasma[a].pos.j]
#define A_UP(a) ARENA[SHOW_UP(a)][G->fantasma[a].pos.j] 
#define A_DOWN(a) ARENA[SHOW_DOWN(a)][G->fantasma[a].pos.j]
#define A_LEFT(a) ARENA[G->fantasma[a].pos.i][SHOW_LEFT(a)]
#define A_RIGHT(a) ARENA[G->fantasma[a].pos.i][SHOW_RIGHT(a)]

#define IS_NORMAL G->fantasma[id].status == NORMAL

struct ghost{
    struct position pos; 
    unsigned int dir;
    unsigned int status;
    unsigned int id;
};

struct ghosts{
    unsigned int n;
    char **arena;
    unsigned int nrows;
    unsigned int ncols;
    struct ghost *fantasma;
};

static int a, b, c;

/* Create the ghosts data structure */
struct ghosts *ghosts_setup(unsigned int num_ghosts) {
    srand(time(NULL));
    unsigned int k, l;
    register int i;
    struct ghosts *G=(struct ghosts*) malloc(sizeof(struct ghosts));
    k = (unsigned int) (rand()*1 + 10) % 2 == 0 ? 1 : -1;
    l = (unsigned int) (rand()*1 + 10) % 2 == 0 ? 1 : -1;
    struct position UNK_POSITION = {k,l};
    if(G != NULL){
        G->n = num_ghosts;
        G->nrows = 0;
        G->ncols = 0;
        G->arena = NULL;
        G->fantasma = (struct ghost*) calloc(num_ghosts,sizeof(struct ghost));
        if(G->fantasma != NULL){
            for(i = 0; i < num_ghosts; ++i){
                G->fantasma[i].pos = UNK_POSITION;
                G->fantasma[i].dir = LEFT;
            }
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
    for (a = 0; a < G->n; a++) {
            if (rand() % 4 == 0 && A_UP(c) != 'x') G->fantasma[c].dir = UP;
            else if (rand() % 4 == 0 && A_DOWN(c) != 'x') G->fantasma[c].dir = DOWN;
            else if (rand() % 4 == 0 && A_LEFT(c) != 'x') G->fantasma[c].dir = LEFT;
            else if (rand() % 4 == 0 && A_RIGHT(c) != 'x') G->fantasma[c].dir = RIGHT;
            else if (A_UP(c) != 'x') G->fantasma[c].dir = UP;
            else if (A_DOWN(c) != 'x') G->fantasma[c].dir = DOWN;
            else if (A_LEFT(c) != 'x') G->fantasma[c].dir = LEFT;
            else if (A_RIGHT(c) != 'x') G->fantasma[c].dir = RIGHT;
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
        G->fantasma[id].status = status;   
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
    return G->fantasma[id].status;
}

/* Move the ghost id (according to its status). Returns the new position */
struct position ghosts_move(struct ghosts* G, struct pacman* P, unsigned int id) {
    if (G != NULL && P != NULL) {
        struct position pacman_pos = pacman_get_position(P);
        int can_move[4] = { 1,1,1,1 };

        /*follow path in eyes status*/
        if (G->fantasma[id].status == EYES) {
            if (A(id) == 'U') G->fantasma[id].dir = UP;
            if (A(id) == 'D') G->fantasma[id].dir = DOWN;
            if (A(id) == 'L') G->fantasma[id].dir = LEFT;
            if (A(id) == 'R') G->fantasma[id].dir = RIGHT;
        }

        /*randomize direction*/
        if (rand() % 20 == 0) {
            G->fantasma[id].dir = rand() % 4;
        }

        /*wall*/
        if (A_UP(id) == 'x') can_move[0] = 0;
        /*pacman (if status isn't normal)*/
        if (IS_NORMAL && SHOW_UP(id) == pacman_pos.i && POS_J(id) == pacman_pos.j)
            can_move[0] = 0;
        /*ghosts*/
        for (a = 0; a < G->n; a++) {
            if (SHOW_UP(id) == POS_I(a) && POS_J(id) == POS_J(a)) can_move[0] = 0;
        }
        /*wall*/
        if (A_DOWN(id) == 'x') can_move[1] = 0;
        /*pacman (if status isn't normal)*/
        if (IS_NORMAL && SHOW_DOWN(id) == pacman_pos.i && POS_J(id) == pacman_pos.j)
            can_move[1] = 0;
        /*ghosts*/
        for (a = 0; a < G->n; a++) {
            if (SHOW_DOWN(id) == POS_I(a) && POS_J(id) == POS_J(a)) can_move[1] = 0;
        }
        /*wall*/
        if (A_LEFT(id) == 'x') can_move[2] = 0;
        /*pacman (if status isn't normal)*/
        if (IS_NORMAL && POS_I(id) == pacman_pos.i && SHOW_LEFT(id) == pacman_pos.j)
            can_move[2] = 0;
        /*ghosts*/
        for (a = 0; a < G->n; a++) {
            if (POS_I(id) == POS_I(a) && SHOW_LEFT(id) == POS_J(a)) can_move[2] = 0;
        }
        /*wall*/
        if (A_RIGHT(id) == 'x') can_move[3] = 0;
        /*pacman (if status isn't normal)*/
        if (IS_NORMAL && POS_I(id) == pacman_pos.i && SHOW_RIGHT(id) == pacman_pos.j)
            can_move[3] = 0;
        /*ghosts*/
        for (a = 0; a < G->n; a++) {
            if (POS_I(id) == POS_I(a) && SHOW_RIGHT(id) == POS_J(a)) can_move[3] = 0;
        }
    

        /*switch direction is original is already taken*/
        if ((G->fantasma[id].dir == UP && !can_move[0]) ||
            (G->fantasma[id].dir == DOWN && !can_move[1]) ||
            (G->fantasma[id].dir == LEFT && !can_move[2]) ||
            (G->fantasma[id].dir == RIGHT && !can_move[3])) {
            if (can_move[0]) G->fantasma[id].dir = UP;
            if (can_move[1]) G->fantasma[id].dir = DOWN;
            if (can_move[2]) G->fantasma[id].dir = LEFT;
            if (can_move[3]) G->fantasma[id].dir = RIGHT;
        }

        /*moves if can_move*/
        if (can_move[0] || can_move[1] || can_move[2] || can_move[3]) {
            if (G->fantasma[id].dir == UP) MOVE_UP(id);
            if (G->fantasma[id].dir == DOWN) MOVE_DOWN(id);
            if (G->fantasma[id].dir == LEFT) MOVE_LEFT(id);
            if (G->fantasma[id].dir == RIGHT) MOVE_RIGHT(id);
        }
        return G->fantasma[id].pos;
    }
    struct position p = { 0 }; return p;
}

#endif


