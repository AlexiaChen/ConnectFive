#include <graphics.h>

#include "board_ui.h"
#include "game_logic.h"



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

