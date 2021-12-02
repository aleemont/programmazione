#include "snake.h" 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct snake *snake_create(unsigned int rows, unsigned int cols) {
    srand(time(NULL));
    struct snake *head=(struct snake*) malloc(sizeof(struct snake));
    struct position p;
    p.i = random() % rows;
    p.j = random() % cols;
    head->body->pos.i = p.i;
    head->body->pos.j = p.j;
    return head;
} 

void snake_kill(struct snake *s) {
    if(s != NULL)
        free(s);
    return;
}

struct position snake_head(struct snake *s) {
	struct position p;
	return p;

}

struct position snake_body(struct snake *s, unsigned int i) {
	struct position p;
    unsigned int k = 0;
    while(k < i){
        p = s->body->next->pos;
        ++k;
    }
	return p;
}

int snake_knotted(struct snake *s) {
	return 0;
}

void snake_move(struct snake *s, enum direction dir) {
}

void snake_reverse(struct snake *s) {
}

void snake_increase(struct snake *s, enum direction dir) {
}

void snake_decrease(struct snake *s, unsigned int decrease_len) {
}


/* Saves the snake into the filename. */
void snake_save(struct snake *s, char *filename) {
    
}

/* Loads the snake from filename */
struct snake *snake_read(char *filename) {
    return NULL;    
}
