//USE "DEFINE" TO SELECT TEST
//#define TEST_TOCCO_PIENO_PAD1
//#define TEST_TOCCO_PIENO_PAD2
#define TEST_TOCCO_SUP_PAD1	
//#define TEST_TOCCO_SUP_PAD2
//#define TEST_TOCCO_INF_PAD1
//#define TEST_TOCCO_INF_PAD2
//#define TEST_PALLA_BORDO_SUP
//#define TEST_PALLA_BORDO_INF
//#define TEST_PALLA_BORDO_SX
//#define TEST_PALLA_BORDO_DX
//#define TEST_PALLA_CENTRO


#define HARD



/*
Significato simboli codeboard
@M =	move_ball();
@z = move_pad1_down();
@a=	move_pad1_up();
@u = move_pad2_down();
@d=	move_pad2_up();		
a=(0,0) e=(39,12) a indica la risposta della vostra libreria, e indica il valore atteso
*/


#ifndef GAME_H
#define GAME_H

struct position {
	int x;
	int y;
};

/*
* Setup a game with the following starting configuration:
* - table dimension equal to heigth*width
* - ball starting position at ball_pos
* - ball starting direction towards ball_dir
* - pad1 starting position at pad1_pos
* - pad2 starting position at pad2_pos
* - pad length equal to pad_len
*/
void setup_game(int height, int width,
	struct position ball_pos, struct position ball_dir,
	struct position pad1_pos, struct position pad2_pos, int pad_len);

/* Moves pad1 one position up. */
void move_pad1_up(void);

/* Moves pad2 one poisiton up */
void move_pad2_up(void);

/* Moves pad1 one position down. */
void move_pad1_down(void);

/* Moves pad2 one position down. */
void move_pad2_down(void);

/* Moves the ball in the current direction */
void move_ball(void);

/* Returns ball current position */
struct position get_ball_pos(void);

/* Returns pad1 current position */
struct position get_pad1_pos(void);

/* Returns pad2 current position */
struct position get_pad2_pos(void);

/* Returns the pad length */
unsigned int get_pad_len(void);

/* Returns pad1 current score */
unsigned int get_pad1_score(void);

/* Returns pad2 current score */
unsigned int get_pad2_score(void);

#endif
