#include "draw_chessboard_ui.h"

#include <graphics.h>
#include <stdio.h>
#include <math.h>


//chess board is 15*15 standard 
static int chessboard[15][15] = {C_BLANK};

typedef struct _POS_BOARD{
	int x;
	int y;
}BoardPos;

static BoardPos pos[15][15]={0};

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

#define TEST 1  //debug switch turned on

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
	gen_pos(pos);
}

int get_pos(int msg_x,int msg_y){

	
	//int d =  (int)sqrt((double)((msg_x-X2)*(msg_x-X2)+(msg_y-Y2)*(msg_y-Y2)));

	return 0;
}


bool run_game(){
	
	
	
	
	
	
	    mouse_msg msg = {0};
	    
		while(mousemsg()){
			 msg = getmouse();
			//msg = GetMouseMsg();
			/*int msg_x, msg_y;
			mousepos(&msg_x,&msg_y);*/
			
			if(msg.is_down() && current_s == C_BLACK_S /*&& d <= 5 */ ){

				C_POS pos;
				/*int msg_x, msg_y;
				
				mousepos(&msg_x,&msg_x);*/
				pos.x = msg.x;/*msg_x*/
				pos.y = msg.y;/*msg_x*/
				
				draw_chess(&pos,BLACK);
				blk_step_count++;
				update_status(white_status);
				update_score();
			}

			else if(msg.is_down() && current_s == C_WHITE_S /*&&  d <= 5*/){
				C_POS pos;
				/*int msg_x, msg_y;

				mousepos(&msg_x,&msg_x);*/
				pos.x = msg.x;/*msg_x*/
				pos.y = msg.y;/*msg_x*/

				draw_chess(&pos,WHITE);
				wht_step_count++;
				update_status(black_status);
				update_score();
			}

			
		}
		
	
	return true;
}