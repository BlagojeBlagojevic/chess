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
#include<SDL2/SDl_timer.h>
#include<SDL2/SDL_rwops.h>
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define SQUER_SIZE 50

#define WIDTH  8 * SQUER_SIZE
#define HEIGHT 8 * SQUER_SIZE

#define GREEN  0x00FF0000
#define WHITE  0xFFFFFFFF

#include "load_pieces.h"

#define ARR_SIZE(X) (sizeof((X)) / sizeof((X[0])))

void Fen_Loader(SDL_Renderer *renderer,Piece *pieces) {

	//char start_position[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
	//char start_position[] = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR";
	char start_position[] = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R";
	size_t x = 0, y = 0, num_of_pices = 0;


	for(size_t i = 0; i < ARR_SIZE(start_position); i++) {


		//assert(num_of_pices <=  NUM_OF_PICES);
		//if(x == 8) {
			//x = 0;
			//y++;
			//}
			printf("num of pices %d\n", (int)num_of_pices);

		switch(start_position[i]) {

			case 'r':
				load_Black_Rook(renderer,pieces,num_of_pices, x++,y);
				num_of_pices++;
				break;

			case 'R':
				load_White_Rook(renderer,pieces,num_of_pices, x++,y);
				num_of_pices++;
				break;

			case 'K':
				load_White_King(renderer,pieces,num_of_pices, x++,y);
				num_of_pices++;
				break;
			
			case 'k':
				load_Black_King(renderer,pieces,num_of_pices, x++,y);
				num_of_pices++;
				break;
				
			case 'Q':
				load_White_Queen(renderer,pieces,num_of_pices, x++,y);
				num_of_pices++;
				break;
				
			case 'q':
				load_Black_Queen(renderer,pieces,num_of_pices, x++,y);
				num_of_pices++;
				break;
				
			case 'B':
				load_White_Bishop(renderer,pieces,num_of_pices, x++,y);
				num_of_pices++;
				break;	
			
			case 'b':
				load_Black_Bishop(renderer,pieces,num_of_pices, x++,y);
				num_of_pices++;
				break;
				
			case 'N':
				load_White_Knight(renderer,pieces,num_of_pices++, x++,y);
				break;
				
			case 'n':
				load_Black_Knight(renderer,pieces,num_of_pices, x++,y);
				num_of_pices++;
				break;
				
			case 'P':
				load_White_Pawn(renderer,pieces,num_of_pices, x++,y);
				num_of_pices++;
				break;
				
			case 'p':
				load_Black_Pawn(renderer,pieces,num_of_pices, x++,y);
				num_of_pices++;
				break;
			
			case '/':	
				x = 0;
				y++;
				break;
			
			case '1':
				x += 1;
				break;
				
			case '2':
				x += 2;
				break;
				
			case '3':
				x += 3;
				break;
				
			case '4':
				x += 4;
				break;
				
			case '5':
				x += 5;
				break;
				
			case '6':
				x += 6;
				break;
				
			case '7':
				x += 7;
				break;
			
			case '8':
				x	+= 8;
				break;		
			}
			
			
				
			
		}



	}


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


void Load_Pieces_Test(SDL_Renderer *renderer,Piece *pieces) {

	size_t x = 0, y = 0, counter = 0;
	load_White_King(renderer,pieces,counter++,x, y);
	load_Black_King(renderer,pieces,counter++,x+=SQUER_SIZE, y);
	load_White_Queen(renderer,pieces,counter++,x+=SQUER_SIZE, y);
	load_Black_Queen(renderer,pieces,counter++,x+=SQUER_SIZE, y);
	}



int main(int argc,char** argv) {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_CreateWindowAndRenderer(WIDTH,HEIGHT,SDL_RENDERER_ACCELERATED,&window,&renderer);
	//SDL_RWops pices;

	Piece pieces[NUM_OF_PICES];
	//Load_Pieces_Test(renderer,pieces);
	Fen_Loader(renderer,pieces);
	system("pause");
	while(1) {
		SDL_RenderClear(renderer);

		Draw_Board(renderer);
		system("pause");
		for(size_t i = 0; i < 32; i++)
			SDL_RenderCopy(renderer, pieces[i].texture, NULL,&pieces[i].position);
		SDL_RenderPresent(renderer);
		system("pause");
		}


	printf("Nesto");
	return 0;

	}
