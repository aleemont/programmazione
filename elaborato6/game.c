#define STUD
#ifdef STUD

#include "game.h"

#define LEFT  -1
#define RIGHT  1
#define UP    -1
#define DOWN   1

typedef struct{
	struct position p;
	int len;
	int score;
	int max_height;
} paletta;

typedef struct{
	struct position p;
	struct position d;
	struct position init_pos;
	struct position init_dir;
	int max_height;
	int max_width;
} palla;

palla ball;
paletta pad1, pad2;

void setup_game(int height, int width, 
                struct position ball_pos, struct position ball_dir,
                struct position pad1_pos, struct position pad2_pos, int pad_len){

						pad1.p.x = pad1_pos.x;
						pad1.p.y = pad1_pos.y;
						pad2.p.x = pad2_pos.x;
						pad2.p.y = pad2_pos.y;
						
						pad1.len = pad_len;
						pad2.len = pad_len;

						pad1.max_height = height;
						pad2.max_height = height;

						ball.p.x = ball_pos.x;
						ball.p.y = ball_pos.y;

						ball.init_pos.x = ball_pos.x;
						ball.init_pos.y = ball_pos.y;

						ball.d.x = ball_dir.x;
						ball.d.y = ball_dir.y;
						
						ball.init_dir.x = ball_dir.x;
						ball.init_dir.y = ball_dir.y;
						
						ball.max_height = height;
						ball.max_width = width;

						pad1.score = 0;
						pad2.score = 0;
				}

/* Moves pad1 one position up. */
void move_pad1_up(void){
	if(pad1.p.y > 0)
		pad1.p.y += UP;
}

/* Moves pad2 one poisiton up */
void move_pad2_up(void){
	if(pad2.p.y > 0)
		pad2.p.y += UP;
}

/* Moves pad1 one position down. */
void move_pad1_down(void){
	if(pad1.p.y + pad1.len < pad1.max_height)
		pad1.p.y += DOWN;
}

/* Moves pad2 one position down. */
void move_pad2_down(void){
	if(pad2.p.y + pad2.len < pad2.max_height)
		pad2.p.y += DOWN;
}

/* Moves the ball in the current direction */
void move_ball(void){

    if(ball.p.x <= 0){
        pad2.score += 1;

        ball.p.x = ball.init_pos.x;
		ball.p.y = ball.init_pos.y;
		ball.d.x = ball.init_dir.x;
		ball.d.y = ball.init_dir.y;
    }
    if(ball.p.x >= ball.max_width){
        pad1.score += 1;

        ball.p.x = ball.init_pos.x;
		ball.p.y = ball.init_pos.y;
		ball.d.x = ball.init_dir.x;
		ball.d.y = ball.init_dir.y;
    }
    /*Tocco pieno pad1*/
	if(ball.p.x == (pad1.p.x + 1) && (ball.p.y >= pad1.p.y && ball.p.y <= pad1.p.y + pad1.len)){
		ball.d.x = RIGHT;
	}
    /*Tocco pieno pad2*/
	if(ball.p.x == (pad2.p.x - 2) && (ball.p.y >= pad2.p.y && ball.p.y <= pad2.p.y + pad2.len)){
		ball.d.x = LEFT;
	}
    /*Tocco sopra pad1*/
	if((ball.p.x == (pad1.p.x + 2) && (ball.p.y == pad1.p.y - 1)) || (ball.p.x == (pad1.p.x + 1) && (ball.p.y == pad1.p.y))){
		ball.d.y = UP;
		ball.d.x = RIGHT;
	}
    /*Tocco sotto pad1*/
	if((ball.p.x == (pad1.p.x + 1) && (ball.p.y == pad1.p.y + pad1.len - 1)) || (ball.p.x == (pad1.p.x) && (ball.p.y == pad1.p.y + pad1.len))){
		ball.d.y = DOWN;
		ball.d.x = RIGHT;
	}
    /*Tocco sopra pad2*/
	if((ball.p.x == (pad2.p.x - 2) && (ball.p.y == pad2.p.y - 1)) || (ball.p.x == (pad2.p.x - 1) && (ball.p.y == pad2.p.y))){
		ball.d.y = UP;
		ball.d.x = LEFT;
	}
    /*Tocco sotto pad2*/
	if((ball.p.x == (pad2.p.x - 2) && (ball.p.y == pad2.p.y + pad2.len)) || (ball.p.x == (pad2.p.x - 1) && (ball.p.y == pad2.p.y + pad2.len))){
		ball.d.y = DOWN;
		ball.d.x = LEFT;
	}
	
	/*Rimbalzo bordi*/
	if(ball.p.y <= 0)
        ball.d.y  = DOWN;
    if(ball.p.y == ball.max_height) {
        ball.d.y = UP;
    }
	
    /* always used */
    ball.p.x += ball.d.x;
    ball.p.y += ball.d.y;
}

/* Returns ball current position */
struct position get_ball_pos(void){
	return ball.p;
}

/* Returns pad1 current position */
struct position get_pad1_pos(void){
	return pad1.p;
}

/* Returns pad2 current position */
struct position get_pad2_pos(void){
	return pad2.p;
}

/* Returns the pad length */
unsigned int get_pad_len(void){
	return pad1.len;
}

/* Returns pad1 current score */
unsigned int get_pad1_score(void){
	return pad1.score;
}

/* Returns pad2 current score */
unsigned int get_pad2_score(void){
	return pad2.score;
}


#endif