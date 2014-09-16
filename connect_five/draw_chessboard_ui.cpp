#include "draw_chessboard_ui.h"

#include <graphics.h>
#include <stdio.h>


//chess board is 15*15 standard 
static int chessboard[15][15] = {C_SPACE};

static char *  black        = "black step count: %d";
static char *  white        = "white step count: %d";
static char *  black_status = "黑方执手";
static char *  white_status = "白方执手";

char blk_cnt[100];
char wht_cnt[100];

int blk_step_count = 0;
int wht_step_count = 0;

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





bool run_game(){
	
	
	
	draw_chessboard();
	update_score();
	update_status(black_status);
	
	

		while(mousemsg()){
			mouse_msg msg = getmouse();
			int msg_x, msg_y;
			mousepos()
			if(msg.is_left() && msg.x - 15 <= 20  && msg.y - 15 <= 60){

				C_POS pos = {msg.x, msg.y};
				draw_chess(&pos,WHITE);
			}

		}
		
	
	return true;
}