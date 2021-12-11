#include "snake.h" 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static struct position new_pos(struct position p, enum direction d, unsigned int rows, unsigned int cols);


struct snake *snake_create(unsigned int rows, unsigned int cols) {
    struct body *b;
    struct position p;
    struct snake *head;
    b = (struct body *)malloc(sizeof(struct body));
    head = (struct snake*) malloc(sizeof(struct snake));
    if(head != NULL){
        p.i = rand() % rows;
        p.j = rand() % cols;
        b->next = NULL;
        b->prev = NULL;
        b->pos = p;

        head->body = b;
        head->cols = cols;
        head->rows = rows;
        head->length = 1;
    }else{
        free(b);
        head = NULL;
    }
    return head;
} 

void snake_kill(struct snake *s) {
    struct body *b;
    b = s->body;
    while(b->next != NULL){
        b = b->next;
        free(b->prev);
    }
    free(b);
    free(s);
    return;
}

struct position snake_head(struct snake *s) {
	struct body *b;
    b= s->body;
	while(b->prev != NULL)
	    b = b->prev;
	
	return b->pos;

}

struct position snake_body(struct snake *s, unsigned int i) {
	struct position p;
    struct body * b;
    register unsigned int k;
    if(s->length < i){
        p.i = -1;
        p.j = -1;
    }
    b = s->body;
    for(k = 0; k < i; ++k)
        b = b->next;
    p = b->pos;
	return p;
}

int snake_knotted(struct snake *s) {
    struct body *b;
    struct body *tmp;

    b = s->body; 
    tmp = b->next;

    
    while(tmp != NULL){
        if(b->pos.i == tmp->pos.i && b->pos.j == tmp->pos.j)
            return 1;
        tmp = tmp->next;
    }
	return 0;
}

void snake_move(struct snake *s, enum direction dir) {
    snake_increase(s, dir);
    snake_decrease(s,1);
}

void snake_reverse(struct snake *s) {
    struct body *tmp;
    struct body *b;

    tmp = NULL;
    b = s->body;
    while(b != NULL){
        tmp = b->prev;
        b->prev = b->next;
        b->next = tmp;
        b = b->prev;
    }
    if(tmp != NULL)
        s->body = tmp->prev;
    return;
}

void snake_increase(struct snake *s, enum direction dir) {
    struct body *b;
    b = (struct body*) malloc(sizeof(struct body));
    b->pos = new_pos(s->body->pos, dir, s->rows, s->cols);
    b->next = s->body;
    b->prev = NULL;
    s->body->prev = b;
    s->body = b;
    ++(s->length);
    
}

void snake_decrease(struct snake *s, unsigned int decrease_len) {
    register unsigned int i;
    struct body *b;
    if(s->length <= decrease_len)
        return;
    b = s->body;
    s->length -= decrease_len;
    while(b->next != NULL)
        b = b->next;
    for(i = 0; i < decrease_len; ++i){
        b = b->prev;
        free(b->next);
        b->next = NULL;
    }
}


/* Saves the snake into the filename. */
void snake_save(struct snake *s, char *filename) {
    FILE *f = fopen(filename, "w");
    int buffer[3] = {0,0};
    struct snake *tmp;
    if(f == NULL || s == NULL)
        exit(1);
    tmp = s;
    while(tmp->body != NULL){
        buffer[0] = tmp->body->pos.j + 48;
        buffer[1] = tmp->body->pos.i + 48;
        fprintf(f,"%d\n%d\n",buffer[0], buffer[1]);
        tmp->body = tmp->body->next;
    }
    free(tmp);
    fclose(f);
    return;
}

/* Loads the snake from filename */
struct snake *snake_read(char *filename) {
    unsigned int i = 0;
    FILE *f;
    struct snake *s;
    char buff_in[2] = {0,0};
    s = calloc(1,sizeof(struct snake));
    f = fopen(filename, "r");
    if(f != NULL){
        while(fscanf(f,"%c",buff_in[i]) != 0){
            if(i % 2 == 0)
                s->body->pos.j = (unsigned int)buff_in[i];
            else
                s->body->pos.i = (unsigned int)buff_in[i];
            ++i;
        }
        s->length = (i/2);
    }
    return s;    
}

static struct position new_pos(struct position p, enum direction d, unsigned int rows, unsigned int cols){
    switch(d){
        case UP:
            p.i = (p.i + (rows-1)) % rows; 
            break;
        case DOWN:
            p.i = (p.i + 1) % rows;
            break;
        case LEFT:
            p.j = (p.j + (cols - 1)) % cols;
            break;
        case RIGHT:
            p.j = (p.j + 1) % cols;
            break;
        default:
            break;
    }
    return p;
}