#ifndef CHESS_BOARD_UI_H 
#define CHESS_BOARD_UI_H 
#include <graphics.h>

//Chess Status
enum STATUS{
	C_BLACK = 1,
	C_WHITE = 2,
	C_SPACE = 3
};

typedef struct Position{
    int x;
	int y;
}C_POS;


bool run_game();

void update_score();

#endif