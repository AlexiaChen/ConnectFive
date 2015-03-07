#include <graphics.h>
#include <stdio.h>

#include "board_ui.h"



static int current_s;

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

int get_current_status(){

	return current_s;
}


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



void game_welcome(){


	setinitmode( INIT_ANIMATION );
	initgraph(700,600);
	setfont(-16, 10,"ËÎÌו");
	setcolor(YELLOW);
	setcaption("connect-five by AlexiaChen");

	//draw welcome text to play or exit game ui
	outtextxy(185,180,"WELCOME TO PLAY,BUDDY!");
	outtextxy(200,210,"Author:AlexiaChen");
	outtextxy(170,250,"To Play,Please input 'y'!");
	outtextxy(170,270,"To Exit,Please input 'n'!");


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



void draw_chess(C_POS* position,color_t color){

	setcolor(color);
	setfillcolor(color);
	fillellipse(position->x,position->y,15,15);
}

// for test
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



void init_board(){
	draw_chessboard();
	update_status(black_status);
	gen_pos(pos);

#if TEST
	test_pos_draw();
#endif
}
