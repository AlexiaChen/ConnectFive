#include <graphics.h>
#include "welcome_ui.h"
#include "draw_chessboard_ui.h"



int main(){

	game_welcome();

	while(!kbhit()){
		
		char ch;
		
		if((ch=getch()) == 'y'){
			run_game();
		  }else if((ch=getch()) == 'n'){
			closegraph();
			return 0;
		   }
      delay_ms(500);
	}
	
	
	
	
	return 0;
}

