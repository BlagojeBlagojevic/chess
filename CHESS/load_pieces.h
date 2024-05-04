#ifndef LOAD_PIECES
#define LOAD_PIECES
#define asdad 
#include<stdint.h>


#define ARR_SIZE(X) (sizeof((X)) / sizeof((X[0])))

#define TRUE  1
#define FALSE 0

#define WHITE 1
#define BLACK 0

const int NUM_OF_PICES = 32;
uint8_t piece_to_move = WHITE;


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
	uint8_t color;
	char name[100];       //Name of the pices
	uint8_t is_piece_selected;	
	uint8_t is_piece_eaten;
	uint8_t is_move;
	SDL_Point moves[65];
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
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	//pieces[num_of_pices].name[] = "white_king";
	strcpy(pieces[num_of_pices].name,"white_king");
	pieces[num_of_pices].color  = WHITE;
	pieces[num_of_pices].is_move = FALSE;
	
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
	strcpy(pieces[num_of_pices].name,"black_king");
	pieces[num_of_pices].pieces_name = BLACK_KING;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	pieces[num_of_pices].color  = BLACK;
	pieces[num_of_pices].is_move = FALSE;
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
	strcpy(pieces[num_of_pices].name,"white_queen");
	pieces[num_of_pices].pieces_name = WHITE_QUEEN;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	pieces[num_of_pices].color  = WHITE;
	pieces[num_of_pices].is_move = FALSE;
	
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
	strcpy(pieces[num_of_pices].name,"black_queen");
	pieces[num_of_pices].pieces_name = BLACK_QUEEN;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	pieces[num_of_pices].color  = BLACK;
	pieces[num_of_pices].is_move = FALSE;
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
	strcpy(pieces[num_of_pices].name,"white_rook");
	pieces[num_of_pices].pieces_name = WHITE_ROOK;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	pieces[num_of_pices].color  = WHITE;
	pieces[num_of_pices].is_move = FALSE;
	
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
	strcpy(pieces[num_of_pices].name,"black_rook");
	pieces[num_of_pices].pieces_name = BLACK_ROOK;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	pieces[num_of_pices].color  = BLACK;
	pieces[num_of_pices].is_move = FALSE;
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
	strcpy(pieces[num_of_pices].name,"white_knight");
	pieces[num_of_pices].pieces_name = WHITE_KNIGHT;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	pieces[num_of_pices].color  = WHITE;
	pieces[num_of_pices].is_move = FALSE;
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
	strcpy(pieces[num_of_pices].name,"black_knight");
	pieces[num_of_pices].pieces_name = BLACK_KNIGHT;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	pieces[num_of_pices].color  = BLACK;
	pieces[num_of_pices].is_move = FALSE;
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
	strcpy(pieces[num_of_pices].name,"white_bishop");
	pieces[num_of_pices].pieces_name = WHITE_BISHOP;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	pieces[num_of_pices].color  = WHITE;
	pieces[num_of_pices].is_move = FALSE;
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
	
	strcpy(pieces[num_of_pices].name,"black_bishop");
	pieces[num_of_pices].pieces_name = BLACK_BISHOP;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	pieces[num_of_pices].color  = BLACK;
	pieces[num_of_pices].is_move = FALSE;
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
	strcpy(pieces[num_of_pices].name,"white_pawn");
	pieces[num_of_pices].pieces_name = WHITE_PAWN;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	pieces[num_of_pices].color  = WHITE;
	pieces[num_of_pices].is_move = FALSE;
	
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
	strcpy(pieces[num_of_pices].name,"black_pawn");
	pieces[num_of_pices].pieces_name = BLACK_PAWN;
	pieces[num_of_pices].is_piece_selected = FALSE;
	pieces[num_of_pices].is_piece_eaten = FALSE;
	pieces[num_of_pices].color  = BLACK;
	pieces[num_of_pices].is_move = FALSE;
}

void Fen_Loader(SDL_Renderer *renderer,Piece *pieces) {  //Dodati ostale zajebancije

	char start_position[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
	//char start_position[] = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR";
	//char start_position[] = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R";
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




#endif
