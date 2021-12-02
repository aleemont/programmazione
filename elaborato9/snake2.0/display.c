#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <curses.h>
#include "display.h"

/* Sets the getch() timeout depending on the snake length.*/
static void display_timeout(struct world *W);

/* Shows the paused game. Returns 1 if the game has to be resumed.*/
static int display_pause(struct world *W);

/* Draws the border of the board.*/
static void display_border(struct world *W, unsigned int start_row, unsigned int start_col);

/* Draws the food.*/
static void display_food(struct world *W, unsigned int start_row, unsigned int start_col);

/* Draws the snake.*/
static void display_snake(struct world *W, unsigned int start_row, unsigned int start_col);

void display_width(int *max_row, int *max_col) {
	getmaxyx(stdscr,*max_row,*max_col);	
}

void display_open(void) {
	initscr();
	cbreak();
	noecho();               
	keypad(stdscr, TRUE); /* make keys work*/
	curs_set(0);          /* hide cursor*/
	/*timeout(STARTING_TIMEOUT); /* Sets the waiting time for getch()*/
}

void display_plot(struct world *W) {
	unsigned int start_row = (LINES - W->rows)/2;
	unsigned int start_col = (COLS - W->cols)/2;

	/* Update every time the getch() timeout */
	display_timeout(W);
	erase();
	mvprintw(start_row-2,start_col,"SCORE: %u",W->snake->length);
	mvprintw(start_row+W->rows+1,start_col+1,"[Q]uit [P]ause");
	display_border(W,start_row,start_col);
	display_food(W,start_row,start_col);
	display_snake(W,start_row,start_col);
	refresh();
}

int display_gameover(struct world *W) {
	unsigned int start_row = (LINES - W->rows)/2;
	unsigned int start_col = (COLS - W->cols)/2;
	struct position head = snake_head(W->snake);
	char *str = "GAME OVER";
	char new_game;

	erase();
	mvprintw(start_row-2, start_col,"SCORE: %u",W->snake->length);
	display_border(W,start_row,start_col);
	display_food(W,start_row,start_col);
	display_snake(W,start_row,start_col);
	mvaddch(start_row+head.i, start_col+head.j,'X');
	mvprintw(start_row+W->rows+1,start_col+1,"[Q]uit  [R]estart");
	mvprintw(start_row+W->rows+2,start_col+(((int)W->cols-strlen(str))/2),str);
	refresh();

	timeout(-1); /* Wait forever for 'q' or 'r' to be pressed */
	while((new_game = getch()) != 'q' && new_game != 'r');

	return new_game == 'r';
}

void display_close(void) {
	endwin();
}

enum direction display_input(struct world *W, enum direction previous) {
	int ch = getch();

	switch (ch) {
		/* We cannot move the snake in one direction */
    /* and immediately after in the opposite direction. */
		case KEY_LEFT:  /* Move the snake left*/
			if (previous != RIGHT) return LEFT;
			else break;
		case KEY_RIGHT: /* Move the snake right*/
			if (previous != LEFT)  return RIGHT;
			else break;
		case KEY_DOWN:  /* Move the snake down*/
			if (previous != UP)    return DOWN;
			else break;
		case KEY_UP:   /* Move the snake up*/
			if (previous != DOWN)  return UP;
			else break;
		case 'p': /* Freezes the game*/
			if(display_pause(W) == 1)
				break;
		case 'q': /* Quits the game: ugly but cheap!*/
			display_close();
			exit(0);
	}
	return previous;
}

static void display_timeout(struct world *W) {
	unsigned int time = MINIMUM_TIMEOUT < W->snake->length ? MINIMUM_TIMEOUT : STARTING_TIMEOUT-W->snake->length+1;
	timeout(time);
}

static int display_pause(struct world *W) {
	unsigned int start_row = (LINES - W->rows)/2;
	unsigned int start_col = (COLS - W->cols)/2;
	char resume;

	erase();
	mvprintw(start_row-2,start_col,"SCORE: %u",W->snake->length);
	mvprintw(start_row+W->rows+1,start_col+1,"[Q]uit [R]esume");
	display_border(W,start_row,start_col);
	display_food(W,start_row,start_col);
	display_snake(W,start_row,start_col);
	refresh();
	
	timeout(-1); /* Wait forever for 'q' or 'r' to be pressed*/
	while((resume = getch()) != 'q' && resume != 'r');
	return resume == 'r';
}

static void display_border(struct world *W, unsigned int start_row, unsigned int start_col) {
	unsigned int i;
	
	mvaddch(start_row-1,start_col-1,ACS_ULCORNER);
	mvaddch(start_row-1,start_col+W->cols,ACS_URCORNER);
	mvaddch(start_row+W->rows,start_col-1,ACS_LLCORNER);
	mvaddch(start_row+W->rows,start_col+W->cols,ACS_LRCORNER);

	for(i = 0; i < W->rows; i++) {
		mvaddch(start_row+i,start_col-1,ACS_VLINE);
    mvaddch(start_row+i,start_col+W->cols,ACS_VLINE);
	}

	for(i = 0; i < W->cols; i++) {
		mvaddch(start_row-1,start_col+i,ACS_HLINE);
		mvaddch(start_row+W->rows,start_col+i,ACS_HLINE);
	}
	
}

static void display_food(struct world *W, unsigned int start_row, unsigned int start_col) {
	unsigned int i,j;

	for(i = 0; i < W->rows; i++)
		for(j = 0; j < W->cols; j++)
			switch(W->board[i][j]) {
				case GOOD_FOOD:   mvaddch(start_row+i,start_col+j,GOOD_FOOD_SYMBOL); break;
				case BAD_FOOD:    mvaddch(start_row+i,start_col+j,BAD_FOOD_SYMBOL); break;
				case CREEPY_FOOD: mvaddch(start_row+i,start_col+j,CREEPY_FOOD_SYMBOL); break;
				default: break;
			}
}

/* Ugly: we need to know how here the organization of the snake data strucure*/
static void display_snake(struct world *W, unsigned int start_row, unsigned int start_col) {
	unsigned int i;
	struct position p;
	for(i = 0; i < W->snake->length; i++) {
		p = snake_body(W->snake,i);
		mvaddch(start_row+p.i, start_col+p.j,SNAKE_SYMBOL);
	}
}
