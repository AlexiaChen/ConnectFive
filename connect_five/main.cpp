#include <graphics.h>
#include "welcome_ui.h"
#include "draw_chessboard_ui.h"



int main(){

	game_welcome();
	
	
		
		while(!kbhit()){

			char ch;

			if((ch=getch()) == 'y'){
				init_board();
				break;
			}else if((ch=getch()) == 'n'){
				closegraph();
				return 0;
			}

		}

    for(;is_run();delay_fps(60)){

		run_game();
	}
	
	
	
	closegraph();
	
	return 0;
}

