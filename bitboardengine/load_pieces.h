#ifndef LOAD_PIECES
#define LOAD_PIECES
#include<stdint.h>
//#include "generator.h"

#define ARR_SIZE(X) (sizeof((X)) / sizeof((X[0])))

#define TRUE  1
#define FALSE 0

int NUM_OF_PICES = 32;


typedef enum pieces_name {

	WHITE_PAWN = 'P',
	BLACK_PAWN = 'p',

	WHITE_KNIGHT = 'N',
	BLACK_KNIGHT = 'n',

	WHITE_BISHOP = 'B',
	BLACK_BISHOP = 'b',

	WHITE_ROOK = 'R',
	BLACK_ROOK = 'r',

	WHITE_QUEEN = 'Q',
	BLACK_QUEEN = 'q',

	WHITE_KING = 'K',
	BLACK_KING = 'k',



	} Pieces_Name;


typedef struct piece {

	SDL_Texture *texture;
	SDL_Rect    position;
	uint8_t pieces_name;
	char name[100];       //Name of the pices
	uint8_t is_piece_selected;
	uint8_t is_piece_eaten;
	uint8_t color;
	uint8_t moves[64];
	uint8_t num_of_moves;
	uint8_t is_move;
	} Piece;



void load_White_King(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y) {

	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/white_king.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	pieces[num_of_pices].pieces_name = WHITE_KING;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	//pieces[num_of_pices].name[] = "white_king";
	strcpy(pieces[num_of_pices].name,"white_king");
	pieces[num_of_pices].color = TRUE;
	pieces[num_of_pices].num_of_moves = FALSE;
	pieces[num_of_pices].is_move = FALSE;
	}

void load_Black_King(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y) {

	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/black_king.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	strcpy(pieces[num_of_pices].name,"black_king");
	pieces[num_of_pices].pieces_name = BLACK_KING;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	//printf("%u",BLACK_KING);
	pieces[num_of_pices].color = FALSE;
	pieces[num_of_pices].num_of_moves = FALSE;
	pieces[num_of_pices].is_move = FALSE;
	}

void load_White_Queen(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y) {

	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/white_queen.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	strcpy(pieces[num_of_pices].name,"white_queen");
	pieces[num_of_pices].pieces_name = WHITE_QUEEN;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	pieces[num_of_pices].color = TRUE;
	pieces[num_of_pices].num_of_moves = FALSE;
	pieces[num_of_pices].is_move = FALSE;
	}


void load_Black_Queen(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y) {

	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/black_queen.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	//pieces[num_of_pices].name[] = "black_queen";
	strcpy(pieces[num_of_pices].name,"black_queen");
	pieces[num_of_pices].pieces_name = BLACK_QUEEN;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	pieces[num_of_pices].color = FALSE;
	pieces[num_of_pices].num_of_moves = FALSE;
	pieces[num_of_pices].is_move = FALSE;
	}

void load_White_Rook(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y) {

	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/white_rook.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	//pieces[num_of_pices].name[] = "white_rook";
	strcpy(pieces[num_of_pices].name,"white_rook");
	pieces[num_of_pices].pieces_name = WHITE_ROOK;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	pieces[num_of_pices].color = TRUE;
	pieces[num_of_pices].num_of_moves = FALSE;
	pieces[num_of_pices].is_move = FALSE;
	}

void load_Black_Rook(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y) {

	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/black_rook.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	//pieces[num_of_pices].name[] = "black_rook";
	strcpy(pieces[num_of_pices].name,"black_rook");
	pieces[num_of_pices].pieces_name = BLACK_ROOK;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	pieces[num_of_pices].color = FALSE;
	pieces[num_of_pices].num_of_moves = FALSE;
	pieces[num_of_pices].is_move = FALSE;
	}

void load_White_Knight(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y) {

	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/white_knight.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	//pieces[num_of_pices].name[] = "white_knight";
	strcpy(pieces[num_of_pices].name,"white_knight");
	pieces[num_of_pices].pieces_name = WHITE_KNIGHT;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	pieces[num_of_pices].color = TRUE;
	pieces[num_of_pices].num_of_moves = FALSE;
	pieces[num_of_pices].is_move = FALSE;
	}

void load_Black_Knight(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y) {

	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/black_knight.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	//pieces[num_of_pices].name[] = "black_knight";
	strcpy(pieces[num_of_pices].name,"black_knight");
	pieces[num_of_pices].pieces_name = BLACK_KNIGHT;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	pieces[num_of_pices].color = FALSE;
	pieces[num_of_pices].num_of_moves = FALSE;
	pieces[num_of_pices].is_move = FALSE;
	}

void load_White_Bishop(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y) {

	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/white_bishop.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	//pieces[num_of_pices].name[] = "white_bishop";
	strcpy(pieces[num_of_pices].name,"white_bishop");
	pieces[num_of_pices].pieces_name = WHITE_BISHOP;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	pieces[num_of_pices].color = TRUE;
	pieces[num_of_pices].num_of_moves = FALSE;
	pieces[num_of_pices].is_move = FALSE;
	}

void load_Black_Bishop(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y) {

	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/black_bishop.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;

	strcpy(pieces[num_of_pices].name,"black_bishop");
	pieces[num_of_pices].pieces_name = BLACK_BISHOP;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	pieces[num_of_pices].color = FALSE;
	pieces[num_of_pices].num_of_moves = FALSE;
	pieces[num_of_pices].is_move = FALSE;
	}

void load_White_Pawn(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y) {

	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/white_pawn.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	//pieces[num_of_pices].name[] = "white_pawn";
	strcpy(pieces[num_of_pices].name,"white_pawn");
	pieces[num_of_pices].pieces_name = WHITE_PAWN;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	pieces[num_of_pices].color = TRUE;
	pieces[num_of_pices].num_of_moves = FALSE;
	pieces[num_of_pices].is_move = FALSE;
	}

void load_Black_Pawn(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y) {

	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/black_pawn.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	//pieces[num_of_pices].name[] = "black_pawn";
	strcpy(pieces[num_of_pices].name,"black_pawn");
	pieces[num_of_pices].pieces_name = BLACK_PAWN;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	pieces[num_of_pices].color = FALSE;
	pieces[num_of_pices].num_of_moves = FALSE;
	pieces[num_of_pices].is_move = FALSE;
	}

size_t Piece_Loader(SDL_Renderer *renderer,Board board, Piece *pieces) {  //Dodati ostale zajebancije
	//GO THRU ALL PIECES
	size_t piece_counter = 0;
	U64 bitboard;
	for(int i = P; i <= k; i++) {
		bitboard = board.piece[i];
		switch(i) {
		//WHITE 
			case P: {
					while(bitboard) {
						size_t index = LSB(bitboard);
						size_t y = (size_t)index / 8, x = (size_t)index % 8;
						load_White_Pawn(renderer, pieces,piece_counter, x, y);
						piece_counter++;
						POP(bitboard, index);
						//printf("\nx %d y %d\n\n",x,y);
						}
					break;
					}
					
				case N: {
					while(bitboard) {
						size_t index = LSB(bitboard);
						size_t y = (size_t)index / 8, x = (size_t)index % 8;
						load_White_Knight(renderer, pieces,piece_counter, x, y);
						piece_counter++;
						POP(bitboard, index);
						//printf("\nx %d y %d\n\n",x,y);
						}
					break;
					}
					
				case B: {
					while(bitboard) {
						size_t index = LSB(bitboard);
						size_t y = (size_t)index / 8, x = (size_t)index % 8;
						load_White_Bishop(renderer, pieces,piece_counter, x, y);
						piece_counter++;
						POP(bitboard, index);
						//printf("\nx %d y %d\n\n",x,y);
						}
					break;
					}
				
				case R: {
					while(bitboard) {
						size_t index = LSB(bitboard);
						size_t y = (size_t)index / 8, x = (size_t)index % 8;
						load_White_Rook(renderer, pieces,piece_counter, x, y);
						piece_counter++;
						POP(bitboard, index);
						//printf("\nx %d y %d\n\n",x,y);
						}
					break;
					}
					
					case Q: {
					while(bitboard) {
						size_t index = LSB(bitboard);
						size_t y = (size_t)index / 8, x = (size_t)index % 8;
						load_White_Queen(renderer, pieces,piece_counter, x, y);
						piece_counter++;
						POP(bitboard, index);
						//printf("\nx %d y %d\n\n",x,y);
						}
					break;
					}
				
				case K: {
					while(bitboard) {
						size_t index = LSB(bitboard);
						size_t y = (size_t)index / 8, x = (size_t)index % 8;
						load_White_King(renderer, pieces,piece_counter, x, y);
						piece_counter++;
						POP(bitboard, index);
						//printf("\nx %d y %d\n\n",x,y);
						}
					break;
					}
					
				//BLACK
				
				case p: {
					while(bitboard) {
						size_t index = LSB(bitboard);
						size_t y = (size_t)index / 8, x = (size_t)index % 8;
						load_Black_Pawn(renderer, pieces,piece_counter, x, y);
						piece_counter++;
						POP(bitboard, index);
						//printf("\nx %d y %d\n\n",x,y);
						}
					break;
					}
					
				case n: {
					while(bitboard) {
						size_t index = LSB(bitboard);
						size_t y = (size_t)index / 8, x = (size_t)index % 8;
						load_Black_Knight(renderer, pieces,piece_counter, x, y);
						piece_counter++;
						POP(bitboard, index);
						//printf("\nx %d y %d\n\n",x,y);
						}
					break;
					}
					
				case b: {
					while(bitboard) {
						size_t index = LSB(bitboard);
						size_t y = (size_t)index / 8, x = (size_t)index % 8;
						load_Black_Bishop(renderer, pieces,piece_counter, x, y);
						piece_counter++;
						POP(bitboard, index);
						//printf("\nx %d y %d\n\n",x,y);
						}
					break;
					}
				
				case r: {
					while(bitboard) {
						size_t index = LSB(bitboard);
						size_t y = (size_t)index / 8, x = (size_t)index % 8;
						load_Black_Rook(renderer, pieces,piece_counter, x, y);
						piece_counter++;
						POP(bitboard, index);
						//printf("\nx %d y %d\n\n",x,y);
						}
					break;
					}
					
					case q: {
					while(bitboard) {
						size_t index = LSB(bitboard);
						size_t y = (size_t)index / 8, x = (size_t)index % 8;
						load_Black_Queen(renderer, pieces,piece_counter, x, y);
						piece_counter++;
						POP(bitboard, index);
						//printf("\nx %d y %d\n\n",x,y);
						}
					break;
					}
				
				case k: {
					while(bitboard) {
						size_t index = LSB(bitboard);
						size_t y = (size_t)index / 8, x = (size_t)index % 8;
						load_Black_King(renderer, pieces,piece_counter, x, y);
						piece_counter++;
						POP(bitboard, index);
						//printf("\nx %d y %d\n\n",x,y);
						}
					break;
					}
				
					
					
			}
		}
		
		return piece_counter;
	}






#endif
