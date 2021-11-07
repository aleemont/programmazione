#define STUD
#ifdef STUD

#include "game.h"
#include <stdio.h>

#define LEFT  -1
#define RIGHT  1
#define UP    -1
#define DOWN   1

static struct{
	struct position p;
	int score;
} pad1, pad2;

static struct{
	struct position p;
	struct position d;
	struct position init_pos;
} ball;

int max_height;
int max_width;
int _pad_len;
/*Riporta la pallina alla posizione iniziale*/
static void reset_ball();

void setup_game(int height, int width, 
                struct position ball_pos, struct position ball_dir,
                struct position pad1_pos, struct position pad2_pos, int pad_len){

					pad1.score = 0;
					pad2.score = 0;

					_pad_len = pad_len;

					max_width = width;
					max_height = height;

					ball.init_pos.x = ball_pos.x;
					ball.init_pos.y = ball_pos.y;
					ball.p.x = ball_pos.x;
					ball.p.y = ball_pos.y;

					ball.d.y = ball_dir.y;
					ball.d.x = ball_dir.x;

					pad1.p.y = pad1_pos.y;
					pad1.p.x = pad1_pos.x;
					pad2.p.y = pad2_pos.y;
					pad2.p.x = pad2_pos.x;
					return;
				}

/* Moves pad1 one position up. */
void move_pad1_up(void){
	if((0 < pad1.p.y) &&
     ((((ball.p.x != pad1.p.x + -1 && (ball.p.x != pad1.p.x)) && (ball.p.x != pad1.p.x + 1)) ||
      (ball.p.y != pad1.p.y + -1))))

		pad1.p.y += UP;
	
	return;
}

/* Moves pad2 one poisiton up */
void move_pad2_up(void){
	if((0 < pad1.p.y) &&
	((((ball.p.x != pad2.p.x + -1 && (ball.p.x != pad2.p.x)) && (ball.p.x != pad2.p.x + -2)) ||
      (ball.p.y != pad2.p.y + -1))))
		
		pad2.p.y += UP;

	return;
}

/* Moves pad1 one position down. */
void move_pad1_down(void){
	if((pad1.p.y -1 + _pad_len < max_height) &&
     ((((ball.p.x != pad1.p.x -1 && (ball.p.x != pad1.p.x)) && (ball.p.x != pad1.p.x + 1)) ||
      (ball.p.y != pad1.p.y + _pad_len))))

		pad1.p.y += DOWN;
	
	return;
}

/* Moves pad2 one position down. */
void move_pad2_down(void){
	if((pad2.p.y -1 + _pad_len < max_height) &&
     ((((ball.p.x != pad2.p.x -1 && (ball.p.x != pad2.p.x)) && (ball.p.x != pad2.p.x -2)) ||
      (ball.p.y != pad2.p.y + _pad_len))))

		pad2.p.y += DOWN;
	
	return;
}

/* Moves the ball in the current direction */
void move_ball(void){

	/*Assegnazione punteggio*/
    if ((ball.p.x == 0) || (ball.p.x == max_width - 1)) {
		if (ball.p.x == 0) {
		pad2.score = pad2.score + 1;
		}
		else {
		pad1.score = pad1.score + 1;
		}
		reset_ball();
		return;
  	}

	/*Rimbalzo bordi*/
	if (ball.p.y <= 0) {
        ball.d.y = DOWN;
    } else if (ball.p.y >= max_height) {
        ball.d.y = UP;
    }

    /*Tocco pieno pad1*/
	if(ball.p.x == (pad1.p.x + 1) && (ball.p.y >= pad1.p.y && ball.p.y <= pad1.p.y + _pad_len)){
		ball.d.x = RIGHT;
	}
    /*Tocco pieno pad2*/
	if(ball.p.x == (pad2.p.x - 2) && (ball.p.y >= pad2.p.y && ball.p.y <= pad2.p.y + _pad_len)){
		ball.d.x = LEFT;
	}
    /*Tocco sopra pad1*/
	if((ball.p.x == pad1.p.x || ball.p.x == pad1.p.x + 1 || ball.p.x == pad1.p.x - 1) && (ball.p.y == pad1.p.y -1)){
		ball.d.y = UP;
		ball.d.x = RIGHT;
	}
	/*Tocco sopra pad2*/
	if((ball.p.x == pad2.p.x || ball.p.x + 2 == pad2.p.x || ball.p.x + 1 == pad2.p.x) && (ball.p.y == pad2.p.y - 1)){
		ball.d.y = DOWN;
		ball.d.x = RIGHT;
	}

	/*Tocco sotto pad1*/
	if((ball.p.x == pad1.p.x || ball.p.x == pad1.p.x + 1 || ball.p.x == pad1.p.x - 1) && (ball.p.y == pad1.p.y + _pad_len)){
		ball.d.y = UP;
		ball.d.x = LEFT;
	}
	/*Tocco sotto pad2*/
	if((ball.p.x == pad2.p.x || ball.p.x + 2 == pad2.p.x || ball.p.x + 1 == pad2.p.x) && (ball.p.y == pad2.p.y + _pad_len)){
		ball.d.y = DOWN;
		ball.d.x = LEFT;
	}

    /* always used */
    ball.p.x += ball.d.x;
    ball.p.y += ball.d.y;

	return;
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
	return _pad_len;
}

/* Returns pad1 current score */
unsigned int get_pad1_score(void){
	return pad1.score;
}

/* Returns pad2 current score */
unsigned int get_pad2_score(void){
	return pad2.score;
}

static void reset_ball(void){
	ball.p.x = ball.init_pos.x;
	ball.p.y = ball.init_pos.y;
}

#endif