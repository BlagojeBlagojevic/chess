#ifndef LOAD_PIECES
#define LOAD_PIECES
#include<stdint.h>

#define NUM_OF_PICES 33

typedef enum pieces_name{
	
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
	
	
	
}Pieces_Name;


typedef struct piece{
	SDL_Texture *texture;
	SDL_Rect    position;
	uint8_t pieces_name;
	char name[100];       //Name of the pices
	
	
	
}Piece;



void load_White_King(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/white_king.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	pieces[num_of_pices].pieces_name = WHITE_KING;
	//pieces[num_of_pices].name[] = "white_king";
	strcpy_s(pieces[num_of_pices].name,100,"white_king");
	
}

void load_Black_King(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/black_king.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	strcpy_s(pieces[num_of_pices].name,100,"black_king");
	pieces[num_of_pices].pieces_name = BLACK_KING;
	//printf("%u",BLACK_KING);
}

void load_White_Queen(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/white_queen.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	strcpy_s(pieces[num_of_pices].name,100,"white_queen");
	pieces[num_of_pices].pieces_name = WHITE_QUEEN;
}


void load_Black_Queen(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/black_queen.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	//pieces[num_of_pices].name[] = "black_queen";
	strcpy_s(pieces[num_of_pices].name,100,"black_queen");
	pieces[num_of_pices].pieces_name = BLACK_QUEEN;
}

void load_White_Rook(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/white_rook.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	//pieces[num_of_pices].name[] = "white_rook";
	strcpy_s(pieces[num_of_pices].name,100,"white_rook");
	pieces[num_of_pices].pieces_name = WHITE_ROOK;
}

void load_Black_Rook(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/black_rook.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	//pieces[num_of_pices].name[] = "black_rook";
	strcpy_s(pieces[num_of_pices].name,100,"black_rook");
	pieces[num_of_pices].pieces_name = BLACK_ROOK;
}

void load_White_Knight(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/white_knight.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	//pieces[num_of_pices].name[] = "white_knight";
	strcpy_s(pieces[num_of_pices].name,100,"white_knight");
	pieces[num_of_pices].pieces_name = WHITE_KNIGHT;
}

void load_Black_Knight(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/black_knight.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	//pieces[num_of_pices].name[] = "black_knight";
	strcpy_s(pieces[num_of_pices].name,100,"black_knight");
	pieces[num_of_pices].pieces_name = BLACK_KNIGHT;
}

void load_White_Bishop(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/white_bishop.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	//pieces[num_of_pices].name[] = "white_bishop";
	strcpy_s(pieces[num_of_pices].name,100,"white_bishop");
	pieces[num_of_pices].pieces_name = WHITE_BISHOP;
	
}

void load_Black_Bishop(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/black_bishop.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	
	strcpy_s(pieces[num_of_pices].name,100,"black_bishop");
	pieces[num_of_pices].pieces_name = BLACK_BISHOP;
}

void load_White_Pawn(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/white_pawn.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	//pieces[num_of_pices].name[] = "white_pawn";
	strcpy_s(pieces[num_of_pices].name,100,"white_pawn");
	pieces[num_of_pices].pieces_name = WHITE_PAWN;
}

void load_Black_Pawn(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/black_pawn.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x * SQUER_SIZE;
	pieces[num_of_pices].position.y = y * SQUER_SIZE;
	//pieces[num_of_pices].name[] = "black_pawn";
	strcpy_s(pieces[num_of_pices].name,100,"black_pawn");
	pieces[num_of_pices].pieces_name = BLACK_PAWN;
}


#endif
