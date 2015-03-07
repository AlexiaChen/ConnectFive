#ifndef WELCOME_UI_H
#define WELCOME_UI_H


//Chess Status
enum STATUS{
	C_BLACK = 1,
	C_WHITE = 2,
	C_BLANK = 3
};

//chess board is 15*15 standard 
static int chessboard_status[15][15] = {C_BLANK};

static char*  black_status = "black user";
static char*  white_status = "white user";


static char*  black_win = "black user WIN";
static char*  white_win = "white user WIN";



typedef enum _BWS{
	C_BLACK_S = 0,
	C_WHITE_S = 1
}BWS;



typedef struct _POS_BOARD{
	int x;
	int y;
}BoardPos;

static BoardPos pos[15][15]={0};

typedef struct Position{
	int x;
	int y;
}C_POS;

void game_welcome();
void draw_chessboard();
void draw_chess(C_POS* position,color_t color);

void init_board();

void gen_pos(BoardPos (*pos)[15]);
void update_status(char *status);
int get_current_status();

#define TEST 0    //test function turns off

#endif