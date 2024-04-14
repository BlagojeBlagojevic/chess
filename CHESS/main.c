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

#define SQUER_SIZE 40

#define WIDTH  8 * SQUER_SIZE
#define HEIGHT 8 * SQUER_SIZE

#define GREEN  0x00FF0000
#define WHITE  0xFFFFFFFF

#include "load_pieces.h"


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


void Load_Pieces_Test(SDL_Renderer *renderer,Piece *pieces){
	
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
	Load_Pieces_Test(renderer,pieces);

	while(1) {
		SDL_RenderClear(renderer);

		Draw_Board(renderer);
		for(size_t i = 0;i < 4;i++)
			SDL_RenderCopy(renderer, pieces[i].texture, NULL,&pieces[i].position);
		SDL_RenderPresent(renderer);
		system("pause");
		}


	printf("Nesto");
	return 0;

	}
