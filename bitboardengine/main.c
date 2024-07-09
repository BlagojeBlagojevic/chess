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
#include<time.h>
#define SQUER_SIZE 100

#define WIDTH  8 * SQUER_SIZE
#define HEIGHT 8 * SQUER_SIZE

#define GREEN  0x00FF0000
#define WHITE  0x00800020
#include "generator.h"
#include "load_pieces.h"

//#include "move.h"



void Draw_Board(SDL_Renderer *renderer) {


	SDL_Rect  squer = {.w = SQUER_SIZE, .h = SQUER_SIZE};

	//exit(1);
	for(size_t y = 0; y < 8; y++) {
		for(size_t x = 0; x < 8; x++) {
			squer.x = x * SQUER_SIZE;
			squer.y = y * SQUER_SIZE;
			if((x + y) % 2 == 0) {

				SDL_SetRenderDrawColor(renderer,128,0,32,0);
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
		if((int)(pieces[i].position.x / SQUER_SIZE) == X && (int)(pieces[i].position.y / SQUER_SIZE) == Y) {

			if(!pieces[i].is_piece_selected && !pieces[i].is_piece_eaten) {
				printf("Eaten piece is %s na poziciji (%d %d) ",pieces[i].name,X,Y);
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
	//printf("X =  %d Y = %d\n",X, Y);
	for(size_t i = 0; i < NUM_OF_PICES; i++) {

		if(pieces[i].is_piece_selected == TRUE) {
			//SWITCH TRUE MOVES
			pieces[i].position.x = X * SQUER_SIZE;
			pieces[i].position.y = Y * SQUER_SIZE;
			Check_Is_Piece_Is_Dead(pieces,X,Y);
			pieces[i].is_piece_selected = FALSE;
			check_Piece_Selection = FALSE;
			}


		}



	//Processes mouse input in regardrs of a piece selection
	for(size_t i = 0; i < NUM_OF_PICES && check_Piece_Selection; i++) {
		//printf("%d\n",i);

		if((int)(pieces[i].position.x / SQUER_SIZE) == X && (int)(pieces[i].position.y / SQUER_SIZE) == Y && !pieces[i].is_piece_eaten) {
			for(size_t j = i; j < NUM_OF_PICES; j++) {
				pieces[j].is_piece_selected  = FALSE;
				//printf("%d\n", j);
				}
			pieces[i].is_piece_selected = TRUE;
			printf("Selected pieces is %s na poziziji (%d %d)\n", pieces[i].name,X, Y);
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
	//MOVES moves;
	//Fen_Loader(renderer,pieces);
	//system("pause");
	init_attack_table();
	if(init_masks() != TRAP_NONINIT) {

		}
	else return -1;
	init_slider_attacks(bishop);
	init_slider_attacks(rook);
	init_utils();
#define start_fen_r "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/1NBQKBNR w KQkq - 0 1"
	if(fen_loader(start_fen_full) == TRAP_FEN) {
		printf("FEN ERROR !!!\n");
		return -1;
		}

	Board board;
	Moves m;
	m.counter = 0;
	print_board();
	//system("pause");
	srand(time(0));
	//Piece_Loader(renderer,board,&pieces);
	init_board_state(&board);
	Hashmap ma;
	init_hashmap(&ma);

	while(1) {
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			//system("pause");
			if(event.type == SDL_QUIT) {
				return -1;
				}
			}

		//generate_posible_moves(board, &m,1,1);

		//int index = index_bestT(board, ma, m);
		search_position(ma,&board, 6);
		//print_move(board.best_move);
		make_move(&board, board.best_move);
		//system("pause");
		init_iternal_state(&board);

		SDL_RenderClear(renderer);
		Draw_Board(renderer);
		//memset(&pieces,0,sizeof(Piece));
		size_t num_of_pieces = Piece_Loader(renderer,board,&pieces);
		//system("pause");
		//system("pause");
		for(size_t i = 0; i < num_of_pieces; i++) {
			SDL_RenderCopy(renderer, pieces[i].texture, NULL,&pieces[i].position);
			}

		SDL_RenderPresent(renderer);
		//system("cls");
		//print_board();

		SDL_Delay(1000);

		if(board.piece[k]==0) {

			printf("White wins!!!\n");
			//system("pause");
			break;
			}
		if(board.piece[K]==0) {
			printf("Blacks wins!!!\n");
			//system("pause");
			break;
			}


		}


	printf("Nesto");
	return 0;
	}
