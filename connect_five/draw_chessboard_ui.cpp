#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "draw_chessboard_ui.h"


//chess board is 15*15 standard 
static int chessboard_status[15][15] = {C_BLANK};

typedef struct _POS_BOARD{
	int x;
	int y;
}BoardPos;

static BoardPos pos[15][15]={0};

static char*  black        = "black step count: %d";
static char*  white        = "white step count: %d";
static char*  black_status = "black user";
static char*  white_status = "white user";


static char*  black_win = "black user WIN";
static char*  white_win = "white user WIN";

char blk_cnt[100];
char wht_cnt[100];

int blk_step_count = 0;
int wht_step_count = 0;

typedef enum _BWS{
	C_BLACK_S = 0,
	C_WHITE_S = 1
}BWS;

int current_s;

#define TEST 0  //debug switch turned off , this switch prepare for developer

void gen_pos(BoardPos (*pos)[15]){

    #if TEST
	FILE* fp = NULL;
	if(NULL == ( fp = freopen("debug.txt", "a+" ,stdout)))
		printf("Cannot open file.\n");

    #endif

	


	
	for(int x = 0; x < 15; x++){
		
		for(int y = 0; y < 15; y++){
		    
			pos[x][y].x = 20 + 30*y;
		    pos[x][y].y = 60 + 30*x;

			#if TEST
			printf("(%d,%d) ",pos[x][y].x,pos[x][y].y);
            #endif
		}

        #if TEST
		puts("");
        #endif
    }

    #if TEST
	printf("/*****************************************************************************************/   \n");
	fclose(fp);
    #endif
	
}

void draw_chess(C_POS* position,color_t color){

	setcolor(color);
	setfillcolor(color);
	fillellipse(position->x,position->y,15,15);
}

#if TEST
void test_pos_draw(){

	for(int x = 0; x < 15; x++){

		for(int y = 0; y < 15; y++){
            
			C_POS c_pos;
			c_pos.x = pos[x][y].x;
			c_pos.y = pos[x][y].y;

			draw_chess(&c_pos,WHITE);

        }
    }
}

#endif


void update_score(){

	sprintf(blk_cnt,black,blk_step_count);
	sprintf(wht_cnt,white,wht_step_count);

	xyprintf(480,50,blk_cnt);
	xyprintf(480,90,wht_cnt);

}

void update_status(char *status){
	outtextxy(30,30,status);

	switch(status[0]){
	case 'b':
	    current_s = C_BLACK_S;
		break;
	case 'w':
		current_s = C_WHITE_S;
		break;
	}
	
}



void draw_chessboard(){

	cleardevice();
	setbkcolor(GREEN);
    setcolor(BLACK);
	
	int x = 20,y = 60;
	for(; x <= 440;x += 30)
		line(x,60,x,480);
	for(; y <= 480;y += 30)
		line(20,y,440,y);

	outtextxy(30,30,black_status);

}


void init_board(){
	draw_chessboard();
	update_score();
	update_status(black_status);
	gen_pos(pos);
    
    #if TEST
	test_pos_draw();
    #endif
}

void find_min(int (*dis)[15], int *min_x, int *min_y){

	int min_distance = dis[0][0];
	
	for(int x = 0; x < 15; ++x){
		for(int y = 0; y < 15; ++y){

			if(min_distance > dis[x][y]){

				min_distance = dis[x][y];

				*min_x = x;
				*min_y = y;
			}

		}

	}



}

//let the position of chess align the position of board
void get_right_pos(int msg_x,int msg_y,int *board_min_x, int *board_min_y){

	int distance_seq[15][15] = {0};   
	
	
	for(int x = 0; x < 15; ++x){
		for(int y = 0; y < 15; ++y){
			
			int d =  (int)sqrt((double)(abs(msg_x - pos[x][y].x)*abs(msg_x - pos[x][y].x)+abs(msg_y - pos[x][y].y)*abs(msg_y - pos[x][y].x)));
			distance_seq[x][y] = d;

		}
			
	}

	int min_x, min_y;
	
	find_min(distance_seq,&min_x,&min_y);
	
	*board_min_x = min_x;
	*board_min_y = min_y;

	
}

void update_board_status(int x, int y, enum STATUS status_t){

	chessboard_status[x][y] = status_t;
};

bool is_win(int x,int y,  enum STATUS status_t){

	// 8 directions status searching on board
	int left_to_right = 0, up_to_down = 0; 
	int upper_left_to_lower_right = 0, upper_right_to_lower_left = 0;
	
	int temp_x = x, temp_y = y;
	
	while(chessboard_status[temp_x][temp_y] == status_t && temp_y >=0 && temp_y <= 14){
		
		left_to_right++;

		temp_y--;


	}

	temp_x = x, temp_y = y;
	
	while(chessboard_status[temp_x][temp_y] == status_t && temp_y >=0 && temp_y <= 14){

		left_to_right++;

		temp_y++;


	}

	if(left_to_right == 5)   return true;

	temp_x = x, temp_y = y;
	while(chessboard_status[temp_x][temp_y] == status_t && temp_x >=0 && temp_x <= 14){

		up_to_down++;

		temp_x--;


	}

	temp_x = x, temp_y = y;
	while(chessboard_status[temp_x][temp_y] == status_t && temp_x >=0 && temp_x <= 14){

		up_to_down++;

		temp_x++;


	}

	if(up_to_down == 5)  return true;

	temp_x = x, temp_y = y;
	while(chessboard_status[temp_x][temp_y] == status_t 
		&& temp_x >= 0 && temp_x <= 14
		&& temp_y >= 0 && temp_y <= 14){

		upper_left_to_lower_right++;

		temp_x--;
		temp_y--;


	}

	temp_x = x, temp_y = y;
	while(chessboard_status[temp_x][temp_y] == status_t 
		&& temp_x >= 0 && temp_x <= 14
		&& temp_y >= 0 && temp_y <= 14){

			upper_left_to_lower_right++;

			temp_x++;
			temp_y++;


	}

	if(upper_left_to_lower_right == 5)  return true;

	temp_x = x, temp_y = y;
	while(chessboard_status[temp_x][temp_y] == status_t 
		&& temp_x >= 0 && temp_x <= 14
		&& temp_y >= 0 && temp_y <= 14){

			upper_right_to_lower_left++;

			temp_x--;
			temp_y++;


	}

	temp_x = x, temp_y = y;
	while(chessboard_status[temp_x][temp_y] == status_t 
		&& temp_x >= 0 && temp_x <= 14
		&& temp_y >= 0 && temp_y <= 14){

			upper_right_to_lower_left++;

			temp_x++;
			temp_y--;


	}

	if(upper_right_to_lower_left == 5) return true;




	return false;



};


bool run_game(){
	
	    mouse_msg msg = {0};
	    
		while(mousemsg()){
			 msg = getmouse();
			
			if(msg.is_down() && current_s == C_BLACK_S ){

				C_POS c_pos;
				int board_x,board_y;
				
				get_right_pos(msg.x,msg.y,&board_x,&board_y);
				c_pos.x = pos[board_x][board_y].x;
				c_pos.y = pos[board_x][board_y].y;
				
				draw_chess(&c_pos,BLACK);
				update_board_status(board_x,board_y,C_BLACK);
                if(is_win(board_x,board_y,C_BLACK)) xyprintf(480,120,black_win);
				
				blk_step_count++;
				update_status(white_status);
				update_score();
			}

			else if(msg.is_down() && current_s == C_WHITE_S){
				C_POS c_pos;
				
				int board_x,board_y;

				get_right_pos(msg.x,msg.y,&board_x,&board_y);
				c_pos.x = pos[board_x][board_y].x;
				c_pos.y = pos[board_x][board_y].y;

				draw_chess(&c_pos,WHITE);
				update_board_status(board_x,board_y,C_WHITE);
				if(is_win(board_x,board_y,C_WHITE)) xyprintf(480,120,white_win);
				
				wht_step_count++;
				update_status(black_status);
				update_score();
			}

			
		}
		
	
	return true;
}