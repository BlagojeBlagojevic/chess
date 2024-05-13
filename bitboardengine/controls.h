#ifndef CONTROLS_H
#define CONTROLS_H
#include "load_pieces.h"

typedef struct move{
	
	size_t x[64];
	size_t y[64];
	int num_of_moves;
	
}Moves;

void Check_Is_Piece_Is_Dead(Piece *pieces, int X, int Y) {

	for(size_t i = 0; i < NUM_OF_PICES; i++) {
		if((int)(pieces[i].position.x / SQUER_SIZE) == X && (int)(pieces[i].position.y / SQUER_SIZE) == Y){
		
			if(!pieces[i].is_piece_selected && !pieces[i].is_piece_eaten) {
				printf("Eaten piece is %s na poziciji (%d %d) ",pieces[i].name,X,Y);
				pieces[i].is_piece_eaten = TRUE;
				}
		}
	}
	}




void Procss_Mouse_Input(Piece *pieces, Moves *moves) {

	int X = 0, Y = 0;
	uint8_t check_Piece_Selection = TRUE, Is_Move_Posible = FALSE;
	SDL_GetMouseState(&X, &Y);
	X = X / SQUER_SIZE;
	Y = Y / SQUER_SIZE;
	
		for(size_t i = 0; i < moves->num_of_moves; i++){
		if(X == moves->x[i] && Y == moves->y[i])
			{
				Is_Move_Posible = TRUE;
				break;
			}
	}
	
	for(size_t i = 0; i < NUM_OF_PICES && Is_Move_Posible; i++) {
		
		if(pieces[i].is_piece_selected == TRUE) {
			//SWITCH TRUE MOVES
			pieces[i].position.x = X * SQUER_SIZE;
			pieces[i].position.y = Y * SQUER_SIZE;
			for(size_t j = 0;j < 64;j++)
					{
						moves->x[j] = 0;
						moves->y[j] = 0;
					}
			Check_Is_Piece_Is_Dead(pieces,X,Y);
			for(size_t j = 0;j < NUM_OF_PICES; j++)
				pieces[j].is_piece_selected = FALSE;
			check_Piece_Selection = FALSE;
			}


		}
	
	//Processes mouse input in regardrs of a piece selection
	for(size_t i = 0; i < NUM_OF_PICES && check_Piece_Selection; i++) {
		//printf("%d\n",i);

		if(	(int)(pieces[i].position.x / SQUER_SIZE) == X && 
				(int)(pieces[i].position.y / SQUER_SIZE) == Y && 
				!pieces[i].is_piece_eaten) {
		
			pieces[i].is_piece_selected = TRUE;
			printf("Selected pieces is %s na poziziji (%d %d)\n", pieces[i].name,X, Y);
			break;

			}
		}

		
	printf("X =  %d Y = %d\n",X, Y);
	



	

	//moves->num_of_moves = 0;
	}









#endif