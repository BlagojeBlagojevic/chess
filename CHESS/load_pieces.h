#ifndef LOAD_PIECES
#define LOAD_PIECES


#define NUM_OF_PICES 12

typedef struct piece{
	SDL_Texture *texture;
	SDL_Rect    position;
	char name[100];       //Name of the pices
	
}Piece;



void load_White_King(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/white_king.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x;
	pieces[num_of_pices].position.y = y;
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
	pieces[num_of_pices].position.x = x;
	pieces[num_of_pices].position.y = y;
	strcpy_s(pieces[num_of_pices].name,100,"black_king");
	
	
}

void load_White_Queen(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/white_queen.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x;
	pieces[num_of_pices].position.y = y;
	strcpy_s(pieces[num_of_pices].name,100,"white_queen");
	
}


void load_Black_Queen(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/black_queen.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x;
	pieces[num_of_pices].position.y = y;
	//pieces[num_of_pices].name[] = "black_queen";
	strcpy_s(pieces[num_of_pices].name,100,"black_queen");
}

void load_White_Rook(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/white_rook.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x;
	pieces[num_of_pices].position.y = y;
	//pieces[num_of_pices].name[] = "white_rook";
	strcpy_s(pieces[num_of_pices].name,100,"white_rook");
}

void load_Black_Rook(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/black_rook.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x;
	pieces[num_of_pices].position.y = y;
	//pieces[num_of_pices].name[] = "black_rook";
	strcpy_s(pieces[num_of_pices].name,100,"black_rook");
}

void load_White_Knight(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/white_knight.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x;
	pieces[num_of_pices].position.y = y;
	//pieces[num_of_pices].name[] = "white_knight";
	strcpy_s(pieces[num_of_pices].name,100,"white_knight");
}

void load_Black_Knight(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/black_knight.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x;
	pieces[num_of_pices].position.y = y;
	//pieces[num_of_pices].name[] = "black_knight";
	strcpy_s(pieces[num_of_pices].name,100,"black_knight");
}

void load_White_Bishop(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/white_bishop.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x;
	pieces[num_of_pices].position.y = y;
	//pieces[num_of_pices].name[] = "white_bishop";
	strcpy_s(pieces[num_of_pices].name,100,"white_bishop");
}

void load_Black_Bishop(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/black_bishop.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x;
	pieces[num_of_pices].position.y = y;
	
	strcpy_s(pieces[num_of_pices].name,100,"black_bishop");
}

void load_White_Pawn(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/white_pawn.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x;
	pieces[num_of_pices].position.y = y;
	//pieces[num_of_pices].name[] = "white_pawn";
	strcpy_s(pieces[num_of_pices].name,100,"white_pawn");
}

void load_Black_Pawn(SDL_Renderer *renderer, Piece *pieces,size_t num_of_pices,size_t x, size_t y){
	
	SDL_Surface *surface;
	surface = SDL_LoadBMP("data/black_pawn.bmp");
	pieces[num_of_pices].texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	pieces[num_of_pices].position.h = SQUER_SIZE - 1;
	pieces[num_of_pices].position.w = SQUER_SIZE - 1;
	pieces[num_of_pices].position.x = x;
	pieces[num_of_pices].position.y = y;
	//pieces[num_of_pices].name[] = "black_pawn";
	strcpy_s(pieces[num_of_pices].name,100,"black_pawn");
}


#endif