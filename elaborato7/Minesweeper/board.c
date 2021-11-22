#define BOARD_STUDENT
#ifdef BOARD_STUDENT
#include "board.h"
#include <stdlib.h>
#include <time.h>

#define START(x) !x ? x : x - 1
#define END(x, y) (x == y - 1) ? x : x + 1

static int is_beside(unsigned int x, unsigned int y, unsigned int i, unsigned int j);
static int flags(int board[][GAME_COLS], unsigned int x, unsigned int y);
static int display(int board[][GAME_COLS], unsigned x, unsigned y);
static int check_bomb(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j);
static int are_bombs(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j);

/*
 * Fills the rows*cols board with num_mines random mines
 * leaving free the neighborhood of position i,j
 */
void random_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j, unsigned int num_mines) {
    srand(time(NULL));
    
    unsigned int r, c;
    for(r = 0; r < rows; ++r){
        for(c = 0; c < cols; ++c){
            board[r][c] = UNKN_FREE;
        }
    }
    
    unsigned int m;
    for(m = 0; m < num_mines; ++m){
        unsigned int m_c, m_r;
        
        do{
            m_c = rand() % GAME_COLS;
            m_r = rand() % GAME_ROWS;
        } while(board[m_c][m_r] == UNKN_MINE || is_beside(m_c, m_r, i, j));
        board[m_c][m_r] = UNKN_MINE;
    }
}




/*
* Flags/unflags the i,j position in the board. Returns
* - -1 if the position was flagged. Removes the flag
* -  0 if the position is already displyed
* -  1 if the position is not flagged and not already
*    displayed. Puts a flag in position i,j.
*/
int flag_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j) {
switch(board[i][j]){
    case FLAG_FREE:
        board[i][j] = UNKN_FREE;
        return -1;
    case FLAG_MINE:
        board[i][j] = UNKN_MINE;
        return -1;
    case UNKN_FREE:
        board[i][j] = FLAG_FREE;
        return 1;
    case UNKN_MINE:
        board[i][j] = FLAG_MINE;
        return 1;
}
return 0;
    
}

/*
* Displays position i,j in the board. Returns the number of
* displayed cells or -1 if i,j contains a mine.
*/

int display_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j) {
   int cell_val, end_y, end_x, start_y, start_x, ret_val, n_mines, x, y; 
    start_x = START(i); 
    start_y =START(j); 
    end_x =END(i, cols); 
    end_y =END(j, rows); 
    cell_val = board[i][j]; 
   if (cell_val == UNKN_FREE) { 
        n_mines =0; 
       for (x = start_x; x <= end_x; x++) { 
           for (y = start_y; y <= end_y; y++) { 
               if (board[x][y] == UNKN_MINE || board[x][y] == FLAG_MINE) 
                    n_mines++; 
            } 
        } 
        board[i][j] = n_mines; 
        ret_val =1; 
       if (!n_mines) { 
           for (x = start_x; x <= end_x; x++) { 
               for (y = start_y; y <= end_y; y++) { 
                   if (x != i || y != j) { 
                        cell_val =display_board(board, rows, cols, x, y); 
                        ret_val += cell_val; 
                    } 
                } 
            } 
        } 
    }else { 
       if (cell_val == UNKN_MINE) { 
            board[i][j] = MINE; 
            ret_val = -1; 
        }else { 
            ret_val =0; 
        } 
    } 
   return ret_val;
}



/*
 * Expands all the free cells sourrounding  position i,j in
 * the board. Returns the number of expanded cells or -1 if
 * one contains a mine.
 */
int expand_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j) {
    
    int k, l, x= i, y= j, r= rows, c = cols, cont = 0;

    if (board[i][j] == flags(board, x, y) && (board[i][j] != UNKN_FREE || board[i][j] != UNKN_MINE))
    {
        for (k = x- 1; k < x+ 2; k++)
        {
            if (k < r&& k >= 0)
            {
                for (l = y- 1; l < y+ 2; l++)
                {
                    if (l < c && l >= 0)
                    {
                        if (l != j || k != i)
                        {
                            if (board[k][l] == UNKN_MINE)
                            {
                                return -1;
                            }
                            else if (board[k][l] == UNKN_FREE)
                            {
                                cont += display_board(board, rows, cols, k, l);
                            }
                        }
                    }
                }
            }
        }
    }
    else
        return 0;

    return cont;
}

static int is_beside(unsigned int x, unsigned int y, unsigned int i, unsigned int j){
    return((x >= i -1 && x <= x + 1) && (y >= j - 1 && y <= j + 1));
}

static int flags(int board[][GAME_COLS], unsigned int x, unsigned int y){
    int f = 0;
    unsigned int i, j;
     for (j = y == 0 ? y : y - 1; j <= y + 1; ++j) { 
         for (i = x == 0 ? x : x - 1; i <= x + 1; ++i) {
            if(i >= 0 && i < GAME_COLS && j >= 0 && j < GAME_ROWS){
                if(board[i][j] == FLAG || board[i][j] == FLAG_MINE || board[i][j] == FLAG_FREE)
                    ++f;
            }
        }   
    }
    return f;
}

static int display(int board[][GAME_COLS], unsigned x, unsigned y){
    int k = 0;
    unsigned int i, j;
    for (j = y == 0 ? y : y - 1; j <= y + 1; j++){ 
         for (i = x == 0 ? x : x - 1; i <= x + 1; i++){
            
            if(i >= 0 && i < GAME_COLS && j >= 0 && j < GAME_ROWS)
                if(board[i][j] != FLAG_FREE && board[i][j] != FLAG_MINE){
                    if(board[i][j] == UNKN_MINE) return -1;
                    k += display_board(board, GAME_ROWS, GAME_COLS, i, j);    
                }
        }
    }
    return k;
}

static int are_bombs(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j) {
    int bombs = 0;
    unsigned int k, l, x= i, y= j, r= rows, c = cols;

    for (k = x- 1; k < x+ 2; k++)
    {
        for (l = y- 1; l < y+ 2; l++)
        {
            if (l < cols && k < rows && l >= 0 && k >= 0)
            {
                if (board[k][l] == UNKN_MINE || board[k][l] == FLAG_MINE)
                {
                    bombs++;
                }
            }
        }
    }

    return bombs;
}

static int check_bomb(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j)
{
    int x= i, y= j, r= rows, c = cols;
    switch (are_bombs(board, r, c, x, y))
    {
    case 1:
        board[x][y] = C1;
        break;
    case 2:
        board[x][y] = C2;
        break;
    case 3:
        board[x][y] = C3;
        break;
    case 4:
        board[x][y] = C4;
        break;
    case 5:
        board[x][y] = C5;
        break;
    case 6:
        board[x][y] = C6;
        break;
    case 7:
        board[x][y] = C7;
        break;
    case 8:
        board[x][y] = C8;
        break;
    default:
        board[x][y] = C0;
        break;
    }

    return board[x][y];
}

#endif