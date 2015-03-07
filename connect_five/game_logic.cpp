#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "game_logic.h"
#include "board_ui.h"






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


static bool is_win(int x,int y,  enum STATUS status_t){

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

	gen_pos(pos);

	while(mousemsg()){
		msg = getmouse();

		if(msg.is_down() && get_current_status() == C_BLACK_S ){

			C_POS c_pos;
			int board_x,board_y;
			
			get_right_pos(msg.x,msg.y,&board_x,&board_y);

			c_pos.x = pos[board_x][board_y].x;
			c_pos.y = pos[board_x][board_y].y;

			draw_chess(&c_pos,BLACK);
			update_board_status(board_x,board_y,C_BLACK);
			if(is_win(board_x,board_y,C_BLACK)) xyprintf(480,120,black_win);
            
			update_status(white_status);
		}

		else if(msg.is_down() && get_current_status() == C_WHITE_S){
			C_POS c_pos;

			int board_x,board_y;

			get_right_pos(msg.x,msg.y,&board_x,&board_y);
			c_pos.x = pos[board_x][board_y].x;
			c_pos.y = pos[board_x][board_y].y;

			draw_chess(&c_pos,WHITE);
			update_board_status(board_x,board_y,C_WHITE);
			if(is_win(board_x,board_y,C_WHITE)) xyprintf(480,120,white_win);

			update_status(black_status);
		}


	}


	return true;
}