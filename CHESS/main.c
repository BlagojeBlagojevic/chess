#include<SDL2/SDL.h>
#include<SDL2/SDL_hints.h>
#include<SDL2/SDL_error.h>
#include<SDL2/SDL_log.h>
#include<SDL2/SDL_video.h>
#include<SDL2/SDL_render.h>
#include<SDL2/SDL_pixels.h>
#include<SDL2/SDL_rect.h>
#include<SDL2/SDL_surface.h>
#include<SDL2/SDL_clipboard.h>
#include<SDL2/SDL_events.h>
#include<SDL2/SDL_image.h>
//#include<SDL2/SDl_timer.h>
#include<SDL2/SDL_rwops.h>
#include<SDL2/SDL_mouse.h>
//#include<SDL2/SDL_event.h>
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define SQUER_SIZE 50

#define WIDTH  8 * SQUER_SIZE
#define HEIGHT 8 * SQUER_SIZE

#define GREEN  0x00FF0000
//#define WHITE_C  0xFFFFFFFF

#include "load_pieces.h"
#include "moves.h"



void Draw_Board(SDL_Renderer *renderer) {


	SDL_Rect  squer = {.w = SQUER_SIZE, .h = SQUER_SIZE};

	//exit(1);
	for(size_t y = 0; y < 8; y++) {
		for(size_t x = 0; x < 8; x++) {
			squer.x = x * SQUER_SIZE;
			squer.y = y * SQUER_SIZE;
			if((x + y) % 2 == 0) {

				SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
				}
			else {
				SDL_SetRenderDrawColor(renderer,41,152,41,00);

				}

			SDL_RenderFillRect(renderer,&squer);
			}

		}
	//exit(1);
	//SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0x00);

	//system("pause");

	}

void Check_Is_Piece_Is_Dead(Piece *pieces, int X, int Y) {

	for(size_t i = 0; i < NUM_OF_PICES; i++) {
		if((int)(pieces[i].position.x / SQUER_SIZE) == X 
			&& (int)(pieces[i].position.y / SQUER_SIZE) == Y
			){	
			if(!pieces[i].is_piece_selected && !pieces[i].is_piece_eaten) {
				//printf("Eaten piece is %s na poziciji (%d %d) ",pieces[i].name,X,Y);
				pieces[i].is_piece_eaten = TRUE;
				}
		}
	}
	}




void Procss_Mouse_Input(Piece *pieces) {

	int X = 0, Y = 0;
	uint8_t check_Piece_Selection = TRUE;
	SDL_GetMouseState(&X, &Y);
	X = X / SQUER_SIZE;
	Y = Y / SQUER_SIZE;
	
	//PIECE MOVMENT CHECKING
	for(size_t i = 0; i < NUM_OF_PICES; i++) {
		if(pieces[i].is_piece_selected == TRUE 
			&& pieces[i].color == piece_to_move 
			&& !pieces[i].is_piece_eaten){
			//SWITCH TRUE MOVES
			pieces[i].position.x = X * SQUER_SIZE;
			pieces[i].position.y = Y * SQUER_SIZE;
			Check_Is_Piece_Is_Dead(pieces,X,Y);
			pieces[i].is_piece_selected = FALSE;
			check_Piece_Selection = FALSE;
			piece_to_move = (!piece_to_move);
			}
		}



	//Processes mouse input in regardrs of a piece selection
	for(size_t i = 0; i < NUM_OF_PICES && check_Piece_Selection; i++) {
		//printf("%d\n",i);

		if((int)(pieces[i].position.x / SQUER_SIZE) == X 
			&& (int)(pieces[i].position.y / SQUER_SIZE) == Y 
			&& !pieces[i].is_piece_eaten) {
			for(size_t j = i; j < NUM_OF_PICES; j++) {
				pieces[j].is_piece_selected  = FALSE;
				//printf("%d\n", j);
				}
			pieces[i].is_piece_selected = TRUE;
			printf("\nSelected pieces is %s na poziziji (%d %d)\n", pieces[i].name,X, Y);
			break;

			}
		}

	}




int main(int argc,char** argv) {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_CreateWindowAndRenderer(WIDTH,HEIGHT,SDL_RENDERER_ACCELERATED,&window,&renderer);
	//SDL_RWops pices;

	Piece pieces[NUM_OF_PICES];
	//Load_Pieces_Test(renderer,pieces);
	Fen_Loader(renderer,pieces);
	//system("pause");
	while(1) {
		SDL_Event event;
		if(SDL_WaitEvent(&event)) {
			//printf("nesto");
			if(event.type == SDL_QUIT)
				return 0;

			if(event.type == SDL_MOUSEBUTTONDOWN) {
				Procss_Mouse_Input(pieces);
				//Get_Posible_Moves(pieces,&Move);
				
				
				}
			}


		//
		
		SDL_RenderClear(renderer);
		Draw_Board(renderer);
		//system("pause");
		for(size_t i = 0; i < 32; i++){
			if(!pieces[i].is_piece_eaten)
			SDL_RenderCopy(renderer, pieces[i].texture, NULL,&pieces[i].position);
		}
			
		SDL_RenderPresent(renderer);
		SDL_Delay(10);
		//system("pause");
		}


	printf("Nesto");
	return 0;

	}
