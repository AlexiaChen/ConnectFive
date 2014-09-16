#include "welcome_ui.h"

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