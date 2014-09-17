#include "draw_chessboard_ui.h"

#include <graphics.h>
#include <stdio.h>


//chess board is 15*15 standard 
static int chessboard[15][15] = {C_BLANK};

static char *  black        = "black step count: %d";
static char *  white        = "white step count: %d";
static char *  black_status = "black user";
static char *  white_status = "white user";

char blk_cnt[100];
char wht_cnt[100];

int blk_step_count = 0;
int wht_step_count = 0;

typedef enum _BWS{
	C_BLACK_S = 0,
	C_WHITE_S = 1
}BWS;

int current_s;

void draw_chess(C_POS* position,color_t color){

	setcolor(color);
	setfillcolor(color);
	fillellipse(position->x,position->y,15,15);
}

void update_score(){

	sprintf(blk_cnt,black,blk_step_count);
	sprintf(wht_cnt,white,wht_step_count);

	xyprintf(450,50,blk_cnt);
	xyprintf(450,90,wht_cnt);

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
}


bool run_game(){
	
	
	
	
	
	
	    mouse_msg msg = {0};
	    
		while(mousemsg()){
			 msg = getmouse();
			//msg = GetMouseMsg();
			/*int msg_x, msg_y;
			mousepos(&msg_x,&msg_y);*/
			if(msg.is_down() && current_s == C_BLACK_S/*&& msg.x - 15 <= 20  && msg.y - 15 <= 60*/){

				C_POS pos;
				/*int msg_x, msg_y;
				
				mousepos(&msg_x,&msg_x);*/
				pos.x = msg.x;/*msg_x*/
				pos.y = msg.y;/*msg_x*/
				
				draw_chess(&pos,BLACK);
				update_status(white_status);
			}

			else if(msg.is_down() && current_s == C_WHITE_S){
				C_POS pos;
				/*int msg_x, msg_y;

				mousepos(&msg_x,&msg_x);*/
				pos.x = msg.x;/*msg_x*/
				pos.y = msg.y;/*msg_x*/

				draw_chess(&pos,WHITE);
				update_status(black_status);
			}

			
		}
		
	
	return true;
}