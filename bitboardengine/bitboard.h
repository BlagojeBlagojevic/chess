#include<stdint.h>


//MACRO USED FOR ARRAY SIZE
#define SIZE(x) sizeof(x) / sizeof(x[0])




typedef uint64_t U64;

//SQUERS REPRESENTATION
typedef enum {

	a8, b8, c8, d8, e8, f8, g8, h8,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a1, b1, c1, d1, e1, f1, g1, h1


	} Squeres;

//MACROS FOR BITS SET->SETS BIT ON Squeres  GET->GET BIT VALUE Squeres  POP->POP BIT ON Squers EATING PIECES
//SET(bitboard,h1);
#define SET(bitboard, square)  (bitboard |= (1ULL << square))

//GET(bitboard,h1);
#define GET(bitboard, square)  (bitboard & (1ULL << (square)))

//POP(bitboard,h1);
#define POP(bitboard, square)  (GET(bitboard, square) ? bitboard ^= (1ULL << square) : 0)

//REPRESENT ETARNAL ERROR INSIDE OF A ENGINE
typedef enum trap {

	TRAP_OK,
	TRAP_FEN,   //THIS TRAP IS FOR FEN LOADING ERRROR


	} Trap;




//PRINT BITBOARD REPRESENTATION
void print_bitboard(U64 bitboard) {
	printf("\n=================================================\n\n");

	for(size_t i = 0; i < 64; i++) {
		if(i % 8 == 0) {

			printf("\n\n");
			printf(" %d\t",(int)(8 - i / 8));
			}
		printf("  %d  ", GET(bitboard, i) ? 1 : 0 );
		}
	printf("\n\n\n\t");
	for(size_t i = 0; i < 8; i++) {
		printf("  %c  ", 'a' + i);
		}


	printf("\n\n\n \tBITBOARD VALUE 0x%llX\n", bitboard);
	printf("\n=================================================\n\n");
	}

//BITBOARD REPRESENTETATION OF ALL PIECES
static U64 white_pawn = 0,   black_pawn = 0;
static U64 white_knight = 0, black_knight = 0;
static U64 white_bishop = 0, black_bishop = 0;
static U64 white_rook = 0,   black_rook = 0;
static U64 white_quean = 0,  black_quean = 0;
static U64 white_king = 0,   black_king = 0;


//REPRESENT STARTING POSITION IN FEN NOTOTATION

const char start_position[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
//const char start_position[] = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR";

//LOAD STARTING BITBOARDS
Trap fen_loader(void) {

	Squeres position = 0;

	for(size_t i = 0; i < SIZE(start_position); i++) {

		//printf("position %d", position);
		if(position > 64)
			return TRAP_FEN;

		//TODO: ADD OTHER STUFF
		switch(start_position[i]) {

			//BLACK PIECES
			case 'r': {
					SET(black_rook, position);
					position++;
					break;
					}

			case 'n': {
					SET(black_knight, position);
					position++;
					break;
					}

			case 'b': {
					SET(black_bishop, position);
					position++;
					break;
					}

			case 'q': {
					SET(black_quean, position);
					position++;
					break;
					}

			case 'k': {
					SET(black_king, position);
					position++;
					break;
					}

			case 'p': {
					SET(black_pawn, position);
					position++;
					break;
					}

			//WHITE PIECES

			case 'R': {
					SET(white_rook, position);
					position++;
					break;
					}

			case 'N': {
					SET(white_knight, position);
					position++;
					break;
					}

			case 'B': {
					SET(white_bishop, position);
					position++;
					break;
					}

			case 'Q': {
					SET(white_quean, position);
					position++;
					break;
					}

			case 'K': {
					SET(white_king, position);
					position++;
					break;
					}

			case 'P': {
					SET(white_pawn, position);
					position++;
					break;
					}

			// SKIP FIELD WITHOUT PIECES
			case '1':
				position += 1;
				break;

			case '2':
				position += 2;
				break;

			case '3':
				position += 3;
				break;

			case '4':
				position += 4;
				break;

			case '5':
				position += 5;
				break;

			case '6':
				position += 6;
				break;

			case '7':
				position += 7;
				break;

			case '8':
				position	+= 8;
				break;
			}

		}



	return TRAP_OK;
	}



void print_board() {

	printf("\n=================================================\n\n");
	for(size_t  i = 0; i < 64; i++) {

		//NEW LINE
		if(i%8 == 0) {
			printf("\n\n");
			printf(" %d\t", (int)(8 - i / 8));
			}


		//WHITE PIECES
		if(GET(white_pawn, i)) {
			printf("  P  ");
			}

		else	if(GET(white_rook, i)) {
			printf("  R  ");
			}

		else	if(GET(white_knight, i)) {
			printf("  N  ");
			}

		else	if(GET(white_bishop, i)) {
			printf("  B  ");
			}

		else	if(GET(white_quean, i)) {
			printf("  Q  ");
			}

		else	if(GET(white_king, i)) {
			printf("  K  ");
			}

		//BLACK PIECES
		else if(GET(black_pawn, i)) {
			printf("  p  ");
			}

		else	if(GET(black_rook, i)) {
			printf("  r  ");
			}

		else	if(GET(black_knight, i)) {
			printf("  n  ");
			}

		else	if(GET(black_bishop, i)) {
			printf("  b  ");
			}

		else	if(GET(black_quean, i)) {
			printf("  q  ");
			}

		else	if(GET(black_king, i)) {
			printf("  k  ");
			}

		//EMPTY SQUER
		else {
			printf("  #  ");
			}
		}
	printf("\n\n\n\t");
	for(size_t i = 0; i < 8; i++) {
		printf("  %c  ", 'a' + (uint8_t)i);



		}
	printf("\n==================================================\n\n");
	}


//GENERATING ATTACK TABELS FOR PIECES USED FOR EASER PROCESING

//COLOR USED FOR DESTINGUISING WHAT SIDE IS TO PLAYS
#define WHITE 0
#define BLACK 1


U64 a  =  0xFEFEFEFEFEFEFEFE;
U64 h  =  0x7F7F7F7F7F7F7F7F;
U64 ab =  0xFCFCFCFCFCFCFCFC;
U64 gh =  0x3F3F3F3F3F3F3F3F;

/*USED TO CALCULATE FILES FOR BORDER CASES NO WHRAPPING OF PIECES
void calculate_above(){
	U64 a;
	for(size_t y = 0; y < 8; y++){
		for(size_t x = 0; x < 8; x++){
				if(x != 0){
					SET(a, (y*8 + x));
				}
				if(x != 7){
					SET(h, (y*8 + x));
				}
				if(x < 6){
					SET(gh, (y*8 + x));
				}
			if(x > 1){
				SET(ab,(y*8+x));
			}

		}

	}

}*/



//REPRESENT ALL POSIBLE ATTACKS BY PAWN
//TODO: WRITE PREPROCESOR INITILISATION

#define LOG_ATTACK 0

//WHITE PAWN ATTACKS
static U64 white_pawn_attack_table[64];

void init_white_pawn_attack_table() {

	Squeres position = 0;
	for(size_t i = 0; i < 64; i++, position++) {
		SET(white_pawn_attack_table[i],position >> 9);
		SET(white_pawn_attack_table[i], position >> 7);
		if((i % 8) == 7)
			white_pawn_attack_table[i] &= a;
		if((i % 8) == 0)
			white_pawn_attack_table[i] &= h;
#if LOG_ATTACK
		print_bitboard(white_pawn_attack_table[i]);
#endif

		}

	}

//BLACK PAWN ATTACKS
static U64 black_pawn_attack_table[64];

void init_black_pawn_attack_table() {

	Squeres position = 0;
	for(size_t i = 0; i < 64; i++, position++) {
		SET(black_pawn_attack_table[i],position << 9);
		SET(black_pawn_attack_table[i], position << 7);
		if((i % 8) == 7)
			black_pawn_attack_table[i] &= a;
		if((i % 8) == 0)
			black_pawn_attack_table[i] &= h;
#if LOG_ATTACK
		print_bitboard(black_pawn_attack_table[i]);
#endif

		}

	}

//knight attack table
static U64 knight_attack_table[64];

void init_knight_attack_table() {
	Squeres position = 0;

	for(size_t i = 0; i < 64; i++,position++) {

		SET(knight_attack_table[i], position >> 17);
		SET(knight_attack_table[i], position >> 15);
		SET(knight_attack_table[i], position >> 10);
		SET(knight_attack_table[i], position >> 6);
		SET(knight_attack_table[i], position << 17);
		SET(knight_attack_table[i], position << 15);
		SET(knight_attack_table[i], position << 10);
		SET(knight_attack_table[i], position << 6);
		if(i%8 <= 1)
			knight_attack_table[i] &= gh;
		if(i%8 >= 6)
			knight_attack_table[i]  &= ab;
#if LOG_ATTACK
		print_bitboard(knight_attack_table[i]);
#endif
		}
	}

//bishop attack table
static U64 bishop_attack_table[64];

void init_bishop_attack_table() {
	Squeres position;
	for(size_t i = 0; i < 64; i++, position++) {
		int tr = i / 8 ;
		int tf = i % 8;
		for(int y = tr + 1, x = tf + 1; y < 8 && x < 8; x++,y++) {
			SET(bishop_attack_table[i], (y * 8 + x));
			}
		for(int y = tr - 1, x = tf - 1; y >= 0 && x >= 0; x--,y--) {
			SET(bishop_attack_table[i], (y * 8 + x));
			}
		for(int y = tr + 1, x = tf - 1; y < 8 && x >= 0; x--,y++) {
			SET(bishop_attack_table[i], (y * 8 + x));
			}

		for(int y = tr - 1, x = tf + 1; y >=  0 && x < 8; x++,y--) {
			SET(bishop_attack_table[i], (y * 8 + x));
			}
		//if err check
		POP(bishop_attack_table[i], position);
#if LOG_ATTACK
		print_bitboard(bishop_attack_table[i]);
#endif


		}

	}

//ROOK ATTACK TABLE
static U64 rook_attack_table[64];

void init_rook_attack_table() {

	for(size_t i = 0; i < 64; i++) {
		int tr = i / 8;
		int tf = i % 8;
		for(int y = tr + 1, x = tf; y <= 8; y++) {
			SET(rook_attack_table[i], (y * 8 + x));
			}
		for(int y = tr - 1, x = tf; y >=  0; y--) {
			SET(rook_attack_table[i], (y * 8 + x));
			}
		for(int y = tr, x = tf - 1; x >= 0; x--) {
			SET(rook_attack_table[i], (y * 8 + x));
			}

		for(int y = tr, x = tf + 1; x <= 8; x++) {
			SET(rook_attack_table[i], (y * 8 + x));
			}
		POP(rook_attack_table[i], i);

#if LOG_ATTACK
		print_bitboard(rook_attack_table[i]);
#endif

		}
	}

//QUEAN ATTACK TABLE
static U64 quean_attack_table[64];

void init_quean_attack_table() {
	for(size_t i = 0; i < 64; i++) {
		quean_attack_table[i] = bishop_attack_table[i] | rook_attack_table[i];

#if LOG_ATTACK
		print_bitboard(quean_attack_table[i]);
#endif

		}
	}

static U64 king_attack_table[64];

void init_king_attack_table() {

	Squeres position = 0;
	for(size_t i = 0; i < 64; i++, position++) {

		king_attack_table[i] = white_pawn_attack_table[i] | black_pawn_attack_table[i];
		SET(king_attack_table[i], position << 1);
		SET(king_attack_table[i], position >> 1);
		SET(king_attack_table[i], position >> 8);
		SET(king_attack_table[i], position << 8);
		if((i % 8) == 7)
			king_attack_table[i] &= a;
		if((i % 8) == 0)
			king_attack_table[i] &= h;
#if LOG_ATTACK
		print_bitboard(king_attack_table[i]);
#endif
		}


	}

//SHOUD BE CALL BEFORE ENITING ELSE
void init_attack_table(){
	
	init_white_pawn_attack_table();
	init_black_pawn_attack_table();
	init_knight_attack_table();
	init_bishop_attack_table();
	init_rook_attack_table();
	init_quean_attack_table();
	init_king_attack_table();
	
	
	
}
