#ifndef ENGINE_H
#define ENGINE_H

#include<stdint.h>
#include <string.h>
#ifdef NNUE
#include "nnue_eval.h"
#endif
//#include "nnue_eval.c"

//MACRO USED FOR ARRAY SIZE
#define SIZE(x) sizeof(x) / sizeof(x[0])




typedef uint64_t U64;
typedef uint32_t U32;
enum {bishop, rook, knight, king, quean, pawn};        // REPRESENT PIECES
enum {white = 0, black = 1};  														// REPRESENT PIECES   COLORS
enum { P, N, B, R, Q, K, p, n,  r, b, q, k };
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

const char *squers_name[] = {
	"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
	"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
	"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
	"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
	"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
	"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
	"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
	"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
	};

//REPRESENT ETARNAL ERROR INSIDE OF A ENGINE I MEAN NOT ERROR BUT UNEXEPECTED EVENTS
//AND HANDLING OF THIS ERROR IF WE COUD CALLE THEM LIKE THAT IS HAPENING IN CODE
typedef enum trap {
	TRAP_MAGIC = -1,
	TRAP_ZERO = -1,
	TRAP_OVERFLOW = -1,
	TRAP_OK,
	TRAP_FEN,   //THIS TRAP IS FOR FEN LOADING ERRROR
	TRAP_NONINIT,
	TRAP_CHECKMATE,
	TRAP_ILEGAL,
	TRAP_MOVE_OK,
	TRAP_MATE,
	TRAP_DRAW,
	//TRAP_

	} Trap;


//MACROS FOR BITS SET->SETS BIT ON Squeres  GET->GET BIT VALUE Squeres  POP->POP BIT ON Squers EATING PIECES
//SET(bitboard,h1);
#define SET(bitboard, square)  (bitboard |= (1ULL << square))

//GET(bitboard,h1);
#define GET(bitboard, square)  (bitboard & (1ULL << (square)))

//POP(bitboard,h1);
#define POP(bitboard, square)  (GET(bitboard, square) ? bitboard ^= (1ULL << square) : 0)

//prints lsb bit of bitboard
#define PRINT(bitboard) printf("\nLSB BIT IS %s\n",squers_name[NUM((bitboard & -bitboard) - 1)])

#define LOG_COUNT 0
#define INLINE __attribute__((always_inline))\
	static inline
//#define INLINE static inline

//GET NUMBER OF BITS IN BITBOARD
INLINE int NUM(U64 bitboard) {

	int count = 0;
	while(bitboard) {
		count++;
		bitboard &= bitboard - 1;

		}
#if LOG_COUNT
	printf("\nNUM OF BITS %d\n", count);
#endif
	return count;

	}
//get lsb bit in bitboard
#define LOG_LSB 0
INLINE int LSB(U64 bitboard) {
	if(bitboard) {

#if LOG_LSB
		PRINT(bitboard);
#endif
		return NUM((bitboard & -bitboard) - 1);
		}
	else {
#if LOG_LSB
		printf("TRAP_ZERO");
#endif
		return TRAP_ZERO;
		}

	}



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

const char start_positiona[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR ";
//const char start_position[] = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR";
#define start_fen_full "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define empty_board "8/8/8/8/8/8/8/8 w - - "
#define start_positiona "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 "
#define tricky_position "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1 "
#define killer_position "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"
#define cmk_position "r2q1rk1/ppp2ppp/2n1bn2/2b1p3/3pP3/3P1NPP/PPP1NPB1/R1BQ1RK1 b - - 0 9 "


// GLOBAL STATES INSIDE HOW TO MOVE IS ENPESAN POSIBLE AND IS CASTLE POSIBLE
int side = white;
int en_pesant = -1;
int castle[4];         // add values of
//REPRESENT SQUERS ON WITCH WE COUD FIND PIECES
static U64 position_white, position_black;
#define position_all (position_white | position_black)

//LOAD STARTING BITBOARDS  //start_position as a argument
Trap fen_loader(char start_position[]) {

	Squeres position = 0;
	size_t i = 0;
	//RESET ALL PIECES
	white_bishop = 0;
	white_king = 0;
	white_rook = 0;
	white_knight = 0;
	white_pawn = 0;
	white_quean = 0;
	black_bishop = 0;
	black_king = 0;
	black_rook = 0;
	black_knight = 0;
	black_pawn = 0;
	black_quean = 0;
	//RESET CASTLE AND ENPESANT
	for(size_t j = 0; j < 4; j++)
		castle[j] = 0;
	en_pesant = -1;
	//RESET POSITION_WHITE AND POSITION_BLACK
	position_white = 0;
	position_black = 0;
	//PARSING DISTRIBUTION OF PIECES ON BOARD
	for(; start_position[i] != ' '; i++) {

		//printf("position %d", position);
		if(position > 64)
			return TRAP_FEN;

		//TODO: ADD ANPASS AND CASTLING RIGHTS
		switch(start_position[i]) {

			//BLACK PIECES
			case 'r': {
					SET(position_black, position);
					SET(black_rook, position);
					position++;
					break;
					}

			case 'n': {
					SET(position_black, position);
					SET(black_knight, position);
					position++;
					break;
					}

			case 'b': {
					SET(position_black, position);
					SET(black_bishop, position);
					position++;
					break;
					}

			case 'q': {
					SET(position_black, position);
					SET(black_quean, position);
					position++;
					break;
					}

			case 'k': {
					SET(position_black, position);
					SET(black_king, position);
					position++;
					break;
					}

			case 'p': {
					SET(position_black, position);
					SET(black_pawn, position);
					position++;
					break;
					}

			//WHITE PIECES

			case 'R': {
					SET(position_white, position);
					SET(white_rook, position);
					position++;
					break;
					}

			case 'N': {
					SET(position_white, position);
					SET(white_knight, position);
					position++;
					break;
					}

			case 'B': {
					SET(position_white, position);
					SET(white_bishop, position);
					position++;
					break;
					}

			case 'Q': {
					SET(position_white, position);
					SET(white_quean, position);
					position++;
					break;
					}

			case 'K': {
					SET(position_white, position);
					SET(white_king, position);
					position++;
					break;
					}

			case 'P': {
					SET(position_white, position);
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

			default:
				break;
			}

		}

	int counter_white_spaces = 0;
	for(; start_position[i] != '\0' && counter_white_spaces != 3; i++) {
		if(i == 1000) {
			return TRAP_FEN;
			}

		switch(start_position[i]) {

			case 'w': {
					side = white;
					break;
					}

			case 'b': {
					side = black;
					break;
					}

			case 'K': {
					castle[0] = 1;
					break;
					}

			case 'k': {
					castle[1] = 1;

					break;
					}
			case 'Q': {
					castle[2] = 1;
					break;
					}

			case 'q': {
					castle[3] = 1;
					break;
					}

			case ' ': {
					counter_white_spaces++;
					break;
					}

			//we see what do
			default: {

					break;
					}
			}


		}
	// PROCES ANPESANT

	if(start_position[i]!= '-') {
		en_pesant = (start_position[i] - 'a')  + (8 -  (start_position[i+1] - '0')) * 8 ;
		en_pesant = en_pesant;
		//printf("x %c, y %d",start_position[i] - 'a' + 'a', (8 -  (start_position[i+1] - '0')));
		}
	else {
		en_pesant = -1;
		}

	return TRAP_OK;
	}



void print_board() {

	printf("\n=================================================\n\n");
	if(!side)
		printf("\t\t BOARD, to move white\n");
	else
		printf("\t\t BOARD, to move black\n");
	printf("Castling rights K = %d, k = %d, Q = %d,  q = %d \n", castle[0], castle[1], castle[2], castle[3]);
	if(en_pesant != -1 && en_pesant < 64)
		printf("En_pesant %s\n", squers_name[en_pesant]);
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
			printf("  .  ");
			}
		}
	printf("\n\n\n\t");
	for(size_t i = 0; i < 8; i++) {
		printf("  %c  ", 'a' + (uint8_t)i);



		}
	printf("\n==================================================\n\n");
	}

char *unicode_pieces[12] = {"♙", "♘", "♗", "♖", "♕", "♔", "♟", "♞", "♝", "♜", "♛", "♚"};
//do not use on syestem witch does not suport unicode encoding aka windows i mean it depends of compiler
void print_board_pieces() {


	printf("\n=================================================\n\n");
	for(size_t  i = 0; i < 64; i++) {

		//NEW LINE
		if(i%8 == 0) {
			printf("\n\n");
			printf(" %d\t", (int)(8 - i / 8));
			}


		//WHITE PIECES
		if(GET(white_pawn, i)) {

			printf("  %c  ",unicode_pieces[6]);
			}

		else	if(GET(white_rook, i)) {
			printf("  %c  ",unicode_pieces[9]);
			}

		else	if(GET(white_knight, i)) {
			printf("  %c  ", unicode_pieces[7]);
			}

		else	if(GET(white_bishop, i)) {
			printf("  %c  ", unicode_pieces[8]);
			}

		else	if(GET(white_quean, i)) {
			printf("  %c  ", unicode_pieces[10]);
			}

		else	if(GET(white_king, i)) {
			printf("  %c  ", unicode_pieces[11]);
			}


		//BLACK PIECES
		else if(GET(black_pawn, i)) {
			printf("  %c  ", unicode_pieces[0]);
			}

		else	if(GET(black_rook, i)) {
			printf("  %c  ",unicode_pieces[3]);
			}

		else	if(GET(black_knight, i)) {
			printf("  %c  ", unicode_pieces[1]);
			}

		else	if(GET(black_bishop, i)) {
			printf("  %c  ",unicode_pieces[2]);
			}

		else	if(GET(black_quean, i)) {
			printf("  %c  ", unicode_pieces[4]);
			}

		else	if(GET(black_king, i)) {
			printf("  %c  ",unicode_pieces[5]);
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


const U64 a     =  0xFEFEFEFEFEFEFEFE;
const U64 h     =  0x7F7F7F7F7F7F7F7F;
const U64 ab    =  0xFCFCFCFCFCFCFCFC;
const U64 gh    =  0x3F3F3F3F3F3F3F3F;
const U64 rank1 =  0xFFFFFFFFFFFFFF00;
const U64 rank2 =  0x00FFFFFFFFFFFFFF;


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
	Squeres position = 0;
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

	for(int i = 0; i < 64; i++) {
		int tr = i / 8;
		int tf = i % 8;
		for (int r = tr + 1; r <= 6; r++) rook_attack_table[i] |= (1ULL << (r * 8 + tf));
		for (int r = tr - 1; r >= 1; r--) rook_attack_table[i] |= (1ULL << (r * 8 + tf));
		for (int f = tf + 1; f <= 6; f++) rook_attack_table[i] |= (1ULL << (tr * 8 + f));
		for (int f = tf - 1; f >= 1; f--) rook_attack_table[i] |= (1ULL << (tr * 8 + f));

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
void init_attack_table() {

	init_white_pawn_attack_table();
	init_black_pawn_attack_table();
	init_knight_attack_table();
	init_bishop_attack_table();
	init_rook_attack_table();
	init_quean_attack_table();
	init_king_attack_table();

	}

//THIS SECTION REPRESENT POSIBLE MOVES DEPENDING OF DISTRIBUTION OF OTHER PIECES NOT LOKING INTO TYPE
//LAST SQUERE SHOUD BE 1 CUZ OF CAPTURE
//BRUTE FORCE METOD
INLINE U64 get_bishop_moves(int squere, U64 pieces) {

	U64 posible_moves = 0;
	int tr = squere / 8;
	int tf = squere % 8;
	//MAYBE DECLARED UP SEE
	//printf("%d\n", squere);
	for(int y = tr + 1, x = tf + 1; y < 8 && x < 8; x++,y++) {
		SET(posible_moves, (y * 8 + x));
		if(GET(pieces, (y*8 + x)))
			break;
		}
	for(int y = tr - 1, x = tf - 1; y >= 0 && x >= 0; x--,y--) {
		SET(posible_moves, (y * 8 + x));
		if(GET(pieces, (y * 8 + x)))
			break;
		}
	for(int y = tr + 1, x = tf - 1; y < 8 && x >= 0; x--,y++) {
		SET(posible_moves, (y * 8 + x));
		if(GET(pieces, (y * 8 + x)))
			break;
		}

	for(int y = tr - 1, x = tf + 1; y >=  0 && x < 8; x++,y--) {
		SET(posible_moves, (y * 8 + x));
		if(GET(pieces, (y * 8 + x)))
			break;
		}



	return posible_moves;

	/*TEST FOR BISHOP MOVES

	init_attack_table();
	U64 a = 0;
	SET(a, d5);
	SET(a, c2);
	SET(a, h1);
	SET(a, g6);
	U64 bishop = get_bishop_move(e4, a);
	print_bitboard(bishop);

	*/

	}

//rook
INLINE U64 get_rook_moves(int squere, U64 pieces) {

	U64 posible_moves = 0;
	int tr = squere / 8;
	int tf = squere % 8;

	for(int y = tr + 1, x = tf; y < 8; y++) {
		SET(posible_moves, (y * 8 + x));
		if(GET(pieces, (y * 8 + x)))
			break;
		}

	for(int y = tr - 1, x = tf; y >=  0; y--) {
		SET(posible_moves, (y * 8 + x));
		if(GET(pieces, (y * 8 + x)))
			break;
		}

	for(int y = tr, x = tf - 1; x >= 0; x--) {
		SET(posible_moves, (y * 8 + x));
		if(GET(pieces, (y * 8 + x)))
			break;
		}

	for(int y = tr, x = tf + 1; x < 8; x++) {
		SET(posible_moves, (y * 8 + x));
		if(GET(pieces, (y * 8 + x)))
			break;
		}
	return posible_moves;

	/*TEST FOR POSIBLE ROOK MOVES
	U64 a = 0;
	SET(a, e6);
	SET(a, e2);
	SET(a, d4);
	SET(a, h4);
	SET(a, g4);
	U64 b = get_rook_moves(e4,a);
	print_bitboard(b);
	*/

	}

//quean
INLINE U64 get_quean_moves(int squere, U64 pieces) {

	U64 b_moves = get_bishop_moves(squere, pieces);
	U64 r_moves = get_rook_moves(squere, pieces);

	return (b_moves | r_moves);

	/*
	U64 a = 0;
	SET(a, e6);
	SET(a, e2);
	SET(a, d4);
	SET(a, h4);
	SET(a, g4);
	SET(a, d5);
	SET(a, c2);
	SET(a, h1);
	SET(a, g6);
	U64 b = get_quean_moves(e4,a);
	print_bitboard(b);*/
	}

//NOT NESESARY
//static inline U64 get_knight_moves(int squere, U64 pieces){
//}

//QCCUPANCY IS WHEY TO REPRESENT ALL SQUER ON WITCH WE CAN FIND PIECES
//PROBOBLY NEAD TO MAKE THIS  ONE SQUERE LESS EASY TO SEARCH
//MASKS

//bishop_mask
//rook_mask
static U64 bishop_mask[64],rook_mask[64];
Trap init_masks() {
	// USAGE if(init_masks() != TRAP_NONINIT)

	for(size_t i = 0; i < 64; i++) {

		if(rook_attack_table[i] == 0 || bishop_attack_table[i] == 0) {
			printf("\nTRAP_NONINIT!!!\n\n");
			return TRAP_NONINIT;
			}


		else {
			rook_mask[i] = rook_attack_table[i];


			bishop_mask[i] = bishop_attack_table[i];
			bishop_mask[i] &= a;
			bishop_mask[i] &= h;
			bishop_mask[i] &= rank1;
			bishop_mask[i] &= rank2;
			}


		}
	return TRAP_OK;

	}
INLINE U64 occupancy(int index, int bit_in_mask, U64 piece_attack_table) {

	U64 occupancy_bitboard = 0;
	for(int i = 0; i < bit_in_mask; i++) {
		int squere = LSB(piece_attack_table);

		POP(piece_attack_table, squere);
		if(index & (1 << i)) {
			SET(occupancy_bitboard, squere);
			}
		}

	return occupancy_bitboard;
	}

const int bishop_relevant[] = {
	6,  5,  5,  5,  5,  5,  5,  6,
	5,  5,  5,  5,  5,  5,  5,  5,
	5,  5,  7,  7,  7,  7,  5,  5,
	5,  5,  7,  9,  9,  7,  5,  5,
	5,  5,  7,  9,  9,  7,  5,  5,
	5,  5,  7,  7,  7,  7,  5,  5,
	5,  5,  5,  5,  5,  5,  5,  5,
	6,  5,  5,  5,  5,  5,  5,  6,
	};

const int rook_relevant[] = {
	12, 11, 11, 11, 11, 11, 11, 12,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	12, 11, 11, 11, 11, 11, 11, 12
	};

// RANDOM NUBER GENERATOR
// USED STDLIB RAND FUNCTION
// SOMTING LIKE HASH FUNCRION IS ALSO POSIBLE
/*static inline U16 rand();*/
#include <stdlib.h>
/*INLINE U32 rand32() {

	U32 y  = rand() & 0xff;
	y |= (y & 0xFF) << 8;
	y |= (y & 0xFF) << 16;
	y |= (y & 0xFF) << 24;
	return y;

	}*/
INLINE U32 rand32() {
	U32 y = rand() & 0xFF;
	y = (y << 16) | rand();
	return y;
	}
INLINE U64 rand64() {
	U64 a = rand32();
	U64 b = a << 32;
	a = rand32();
	b |= a;
	return b;
	}

//static U64 seed = 1234;
//INLINE U64 rand64(){

    
 //   return (seed = (164603309694725029ull * seed) % 14738995463583502973ull);

//}

// MAYBE MACRO
INLINE U64 magic_candidate() {

	return rand64() & rand64() & rand64();

	}

//MAGIC NUMBER INIT



INLINE U64 find_magic_number(int square, int relevant_bits, int what_piece) {
	// init occupancies
	static U64 occupancies[4096];

	// init attack tables
	static U64 attacks[4096];

	// init used attacks
	static U64 used_attacks[4096];

	// init attack mask for a current piece
	U64 attack_mask = what_piece ? bishop_mask[square] : bishop_mask[square];

	// init occupancy indicies
	int occupancy_indicies = 1 << relevant_bits;

	// loop over occupancy indicies
	for (int index = 0; index < occupancy_indicies; index++) {
		// init occupancies
		occupancies[index] = occupancy(index, relevant_bits, attack_mask);

		// init attacks
		attacks[index] = what_piece ? get_bishop_moves(square, occupancies[index]) :
		                 get_rook_moves(square, occupancies[index]);
		}

	// test magic numbers loop
	for (int random_count = 0; random_count < 100000000; random_count++) {
		// generate magic number candidate
		U64 magic_number = magic_candidate();

		// skip inappropriate magic numbers
		if (NUM((attack_mask * magic_number) & 0xFF00000000000000) < 6) continue;

		// init used attacks
		memset(used_attacks, 0ULL, sizeof(used_attacks));

		// init index & fail flag
		int index, fail;

		// test magic index loop
		for (index = 0, fail = 0; !fail && index < occupancy_indicies; index++) {
			// init magic index
			int magic_index = (int)((occupancies[index] * magic_number) >> (64 - relevant_bits));

			// if magic index works
			if (used_attacks[magic_index] == 0ULL)
				// init used attacks
				used_attacks[magic_index] = attacks[index];

			// otherwise
			else if (used_attacks[magic_index] != attacks[index])
				// magic index doesn't work
				fail = 1;
			}

		// if magic number works
		if (!fail)
			// return it
			return magic_number;
		}

	// if magic number doesn't work
	printf("  Magic number fails!\n");
	return TRAP_MAGIC;
	}

// init magic numbers

static const U64 rook_magic_numbers[64] = {

	0x8a80104000800020ULL,
	0x140002000100040ULL,
	0x2801880a0017001ULL,
	0x100081001000420ULL,
	0x200020010080420ULL,
	0x3001c0002010008ULL,
	0x8480008002000100ULL,
	0x2080088004402900ULL,
	0x800098204000ULL,
	0x2024401000200040ULL,
	0x100802000801000ULL,
	0x120800800801000ULL,
	0x208808088000400ULL,
	0x2802200800400ULL,
	0x2200800100020080ULL,
	0x801000060821100ULL,
	0x80044006422000ULL,
	0x100808020004000ULL,
	0x12108a0010204200ULL,
	0x140848010000802ULL,
	0x481828014002800ULL,
	0x8094004002004100ULL,
	0x4010040010010802ULL,
	0x20008806104ULL,
	0x100400080208000ULL,
	0x2040002120081000ULL,
	0x21200680100081ULL,
	0x20100080080080ULL,
	0x2000a00200410ULL,
	0x20080800400ULL,
	0x80088400100102ULL,
	0x80004600042881ULL,
	0x4040008040800020ULL,
	0x440003000200801ULL,
	0x4200011004500ULL,
	0x188020010100100ULL,
	0x14800401802800ULL,
	0x2080040080800200ULL,
	0x124080204001001ULL,
	0x200046502000484ULL,
	0x480400080088020ULL,
	0x1000422010034000ULL,
	0x30200100110040ULL,
	0x100021010009ULL,
	0x2002080100110004ULL,
	0x202008004008002ULL,
	0x20020004010100ULL,
	0x2048440040820001ULL,
	0x101002200408200ULL,
	0x40802000401080ULL,
	0x4008142004410100ULL,
	0x2060820c0120200ULL,
	0x1001004080100ULL,
	0x20c020080040080ULL,
	0x2935610830022400ULL,
	0x44440041009200ULL,
	0x280001040802101ULL,
	0x2100190040002085ULL,
	0x80c0084100102001ULL,
	0x4024081001000421ULL,
	0x20030a0244872ULL,
	0x12001008414402ULL,
	0x2006104900a0804ULL,
	0x1004081002402ULL
	};
static const U64 bishop_magic_numbers[64] = {

	0x40040844404084ULL,
	0x2004208a004208ULL,
	0x10190041080202ULL,
	0x108060845042010ULL,
	0x581104180800210ULL,
	0x2112080446200010ULL,
	0x1080820820060210ULL,
	0x3c0808410220200ULL,
	0x4050404440404ULL,
	0x21001420088ULL,
	0x24d0080801082102ULL,
	0x1020a0a020400ULL,
	0x40308200402ULL,
	0x4011002100800ULL,
	0x401484104104005ULL,
	0x801010402020200ULL,
	0x400210c3880100ULL,
	0x404022024108200ULL,
	0x810018200204102ULL,
	0x4002801a02003ULL,
	0x85040820080400ULL,
	0x810102c808880400ULL,
	0xe900410884800ULL,
	0x8002020480840102ULL,
	0x220200865090201ULL,
	0x2010100a02021202ULL,
	0x152048408022401ULL,
	0x20080002081110ULL,
	0x4001001021004000ULL,
	0x800040400a011002ULL,
	0xe4004081011002ULL,
	0x1c004001012080ULL,
	0x8004200962a00220ULL,
	0x8422100208500202ULL,
	0x2000402200300c08ULL,
	0x8646020080080080ULL,
	0x80020a0200100808ULL,
	0x2010004880111000ULL,
	0x623000a080011400ULL,
	0x42008c0340209202ULL,
	0x209188240001000ULL,
	0x400408a884001800ULL,
	0x110400a6080400ULL,
	0x1840060a44020800ULL,
	0x90080104000041ULL,
	0x201011000808101ULL,
	0x1a2208080504f080ULL,
	0x8012020600211212ULL,
	0x500861011240000ULL,
	0x180806108200800ULL,
	0x4000020e01040044ULL,
	0x300000261044000aULL,
	0x802241102020002ULL,
	0x20906061210001ULL,
	0x5a84841004010310ULL,
	0x4010801011c04ULL,
	0xa010109502200ULL,
	0x4a02012000ULL,
	0x500201010098b028ULL,
	0x8040002811040900ULL,
	0x28000010020204ULL,
	0x6000020202d0240ULL,
	0x8918844842082200ULL,
	0x4010011029020020ULL
	};



/*
Trap init_magic_numbers() {
	for (int square = 0; square < 64; square++) {
		if((rook_magic_numbers[square] = find_magic_number(square, rook_relevant[square], rook)) == (U64)TRAP_MAGIC)
			return TRAP_MAGIC;
		}




	for (int square = 0; square < 64; square++) {

		if((bishop_magic_numbers[square] = find_magic_number(square, bishop_relevant[square], bishop)) == (U64)TRAP_MAGIC) {
			return TRAP_MAGIC;
			}
		}

	return TRAP_OK;

	}
*/
void print_magic() {

	printf("\n\n\t BISHOP MAGIC\n\n");
	for(size_t i = 0; i < 64; i++) {
		printf("%d.  ",i);
		printf("0x%llX\n", bishop_magic_numbers[i]);

		}

	printf("\n\n\t ROOK MAGIC\n\n");
	for(size_t i = 0; i < 64; i++) {
		printf("%d.  ",i);
		printf("0x%llX\n", rook_magic_numbers[i]);

		}


	}


//
static U64 bishop_attacks[64][512];
static U64 rook_attacks[64][4096];


//THIS FUNCTION POPULATE bishop and rook atacks depending of position
//THER IS 64*512 POSIBLE BISHOP POSITIONS AND 64*4096 ROOK POSITION
//THIS FUNCTION CHESSPROGRAMING WIKI FOR MORe

void init_slider_attacks(int bishop) {
	// loop over 64 board squares
	for (int square = 0; square < 64; square++) {
		// init bishop & rook masks
		bishop_mask[square] = bishop_mask[square];
		rook_mask[square] = rook_mask[square];

		// init current mask
		U64 attack_mask = bishop ? bishop_mask[square] : rook_mask[square];

		// init relevant occupancy bit count
		int relevant_bits_count = NUM(attack_mask);

		// init occupancy indicies
		int occupancy_indicies = (1 << relevant_bits_count);

		// loop over occupancy indicies
		for (int index = 0; index < occupancy_indicies; index++) {
			// bishop
			if (bishop) {
				// init current occupancy variation
				U64 occupancy1 = occupancy(index, relevant_bits_count, attack_mask);

				// init magic index
				int magic_index = (occupancy1 * bishop_magic_numbers[square]) >> (64 - bishop_relevant[square]);

				// init bishop attacks
				bishop_attacks[square][magic_index] = get_bishop_moves(square, occupancy1);
				}

			// rook
			else {
				// init current occupancy variation
				U64 occupancy2 = occupancy(index, relevant_bits_count, attack_mask);

				// init magic index
				int magic_index = (occupancy2 * rook_magic_numbers[square]) >> (64 - rook_relevant[square]);

				// init bishop attacks
				rook_attacks[square][magic_index] = get_rook_moves(square, occupancy2);

				}
			}
		}
	}
// THIS SECTION USES MAGIC BIT BOARDS TO GENERATE POSIBLE MOVES MUTCH FASTER

// GET BISHOP ATTACK DEPENNDING OFF POSITION OF PIECES
INLINE U64 get_bishop_moves_magic(int square, U64 occupancy) {
	// get bishop attacks assuming current board occupancy
	occupancy &= bishop_mask[square];
	occupancy *= bishop_magic_numbers[square];
	occupancy >>= 64 - bishop_relevant[square];

	// return bishop attacks
	return bishop_attacks[square][occupancy];
	}

// get rook attacks
//ther is some error  +1 operation (and) i coud not find it
//this is for what util is used for
static U64 utiliti_rook[64];
void init_utils() {
	for(size_t i = 0; i < 64; i++) {
		utiliti_rook[i] = get_rook_moves(i, 0);
		}

	}
__attribute__((always_inline))
static inline U64 get_rook_moves_magic(int square, U64 occupancy) {
	// get bishop attacks assuming current board occupancy
	occupancy &= rook_mask[square];
	occupancy *= rook_magic_numbers[square];
	occupancy >>= 64 - rook_relevant[square];

	//ERROR I MEAN THIIS IS TEM FIX BUT IS WORKING
	return (rook_attacks[square][occupancy] & utiliti_rook[square]);
	}
__attribute__((always_inline))
static inline U64 get_quean_moves_magic(int squere, U64 pieces) {

	U64 b_moves = get_bishop_moves_magic(squere, pieces);
	U64 r_moves = get_rook_moves_magic(squere, pieces);

	return (b_moves | r_moves);

	}

//THIS IS SECTION WITCH REPRESENT IS SQUARE ATACKED BY PIECE
//THIS TYPE OF FUNCTION WILL BE USED AS A CHECKING FOR CHESS AND IN BOARD EVALUATION
//MAYBE GO WITH SEPARETE IMPLEMENTATION
__attribute__((always_inline))
static inline int check_is_square_attacked(int side, int square) {




	if((side == white) && (black_pawn_attack_table[square] & white_pawn)) return 1;

	if((side == black) && (white_pawn_attack_table[square] & black_pawn)) return 1;

	if (knight_attack_table[square] & ((side == white) ? white_knight : black_knight)) return 1;

	if(get_bishop_moves_magic(square, position_all) & ((side == white) ? white_bishop : black_bishop)) return 1;

	if(get_rook_moves_magic(square, position_all) & ((side == white) ? white_rook : black_rook)) return 1;

	if(get_quean_moves_magic(square, position_all) & ((side == white) ? white_quean : black_quean)) return 1;

	if(king_attack_table[square] & ((side == white) ? white_king : black_king)) return 1;

	return 0;

	}

int print_is_square_attacked(int side, int square) {
	// print_is_square_attacked(black, c6);
	int is = check_is_square_attacked(side, square);
	if(is == -1)
		return TRAP_OVERFLOW;

	else if(is) {
		print_board();
		printf("\nSquare attacked %s\n ", squers_name[square]);

		}
	else {
		print_board();
		printf("\nSquare is not attacked %s\n ", squers_name[square]);
		}

	}


#include<math.h>
//THIS PART REPRESENTS  MOVE GENERATOR PART OF A CHESS ENGENIN

//WE WILL SEE WHAT TYPE OF STRUCTURE TO STORE MOVES ONE 32 BIT INT IN THIS MANER OR U32
/*
          binary move bits                               hexidecimal constants

    0000 0000 0000 0000 0011 1111    source square       0x3f
    0000 0000 0000 1111 1100 0000    target square       0xfc0
    0000 0000 1111 0000 0000 0000    piece               0xf000
    0000 1111 0000 0000 0000 0000    promoted piece      0xf0000
    0001 0000 0000 0000 0000 0000    capture flag        0x100000
    0010 0000 0000 0000 0000 0000    double push flag    0x200000
    0100 0000 0000 0000 0000 0000    enpassant flag      0x400000
    1000 0000 0000 0000 0000 0000    castling flag       0x800000
*/

// MACROS FOR ENCODIING MOVES

#define ENCODE(source, target, piece, promoted, capture, double, enpassant, castling) \
	(source) |          \
	(target << 6) |     \
	(piece << 12) |     \
	(promoted << 16) |  \
	(capture << 20) |   \
	(double << 21) |    \
	(enpassant << 22) | \
	(castling << 23)    \


#define SOURCE(move) (move & 0x3f)


#define TARGET(move) ((move & 0xfc0) >> 6)


#define PIECE(move) ((move & 0xf000) >> 12)


#define PROMOTED(move) ((move & 0xf0000) >> 16)


#define CAPTURE(move) (move & 0x100000)


#define DOUBLE(move) (move & 0x200000)


#define ENPESANT(move) (move & 0x400000)


#define CASTLING(move) (move & 0x800000)

//STORE ALL MOVES AS A STRUCTURE MOVES
typedef struct {

	int moves[256];
	int value[256];
	int counter;
	} Moves;


// REPRESENTS BOARD STATE THER IS A 6 + 6 PIECES SO piece shoud have 12 bitboards witch represents state of the game
typedef struct {

	U64 piece[13];
	U64 position_white;
	U64 position_black;
	U64 position_alll;
	int side;
	int enpesant;
	int castle[4];
	int best_move;
	int ply;
	//MAYBE OTHER STATES
	} Board;

//INIT MAIN BOARD AS GENERATED FEN NOTATION IN PREVIOS PART OF THE ENGING
// P, N, B, R, Q, K, p, n, b, r, q, k
Trap init_board_state(Board *bo) {

	bo->piece[P] = white_pawn;
	bo->piece[N] = white_knight;
	bo->piece[B] = white_bishop;
	bo->piece[R] = white_rook;
	bo->piece[Q] = white_quean;
	bo->piece[K] = white_king;

	bo->piece[p] = black_pawn;
	bo->piece[n] = black_knight;
	bo->piece[b] = black_bishop;
	bo->piece[r] = black_rook;
	bo->piece[q] = black_quean;
	bo->piece[k] = black_king;

	bo->position_white  = white_pawn | white_knight | white_rook | white_bishop | white_quean | white_king;
	bo->position_black  = black_pawn | black_knight | black_rook | black_bishop | black_quean | black_king;
	bo->position_alll   = bo->position_white | bo->position_black;
	bo->side            = side;
	bo->enpesant        = en_pesant;
	bo->ply             = 0;
	bo->best_move       = 0;
	memcpy(bo->castle, castle, sizeof(int)*4);  //MAYBE DOS NOT WORKS
	return TRAP_OK;

	};

Trap init_iternal_state(Board *bo) {

	white_pawn   = bo->piece[P];
	white_knight = bo->piece[N];
	white_bishop = bo->piece[B];
	white_rook   = bo->piece[R];
	white_quean  = bo->piece[Q];
	white_king   = bo->piece[K];
	black_pawn   = bo->piece[p];
	black_knight = bo->piece[n];
	black_bishop = bo->piece[b];
	black_rook   = bo->piece[r];
	black_quean  = bo->piece[q];
	black_king   = bo->piece[k];

	position_white = bo->position_white;
	position_black = bo->position_black;
	side           = bo->side;
	en_pesant      = bo->enpesant;
	memcpy(castle, bo->castle, sizeof(int)*4);
	return TRAP_OK;

	};



//MAYBE LIKE UCI
void print_move(int move) {

	int source_square = SOURCE(move);
	int target_square = TARGET(move);
	//int piece = PIECE(move);
	//int promoted_piece = PROMOTED(move);


	printf("source square: %s\n", squers_name[source_square]);
	printf("target square: %s\n", squers_name[target_square]);
	printf("capture flag: %d\n", CAPTURE(move) ? 1 : 0);
	printf("double pawn push flag: %d\n", DOUBLE(move) ? 1 : 0);
	printf("enpassant flag: %d\n", ENPESANT(move) ? 1 : 0);
	printf("castling flag: %d\n", CASTLING(move) ? 1 : 0);

	}

//black,c1, &bo
INLINE int check_is_square_attacked_board(int side, int square, const Board *__restrict__ bo) {

	const U64 white_pawna     = bo->piece[P];
	const U64 white_knighta   = bo->piece[N];
	const U64 white_bishopa   = bo->piece[B];
	const U64 white_rooka     = bo->piece[R];
	const U64 white_queana    = bo->piece[Q];
	const U64 white_kinga     = bo->piece[K];
	const U64 black_pawna     = bo->piece[p];
	const U64 black_knighta   = bo->piece[n];
	const U64 black_bishopa   = bo->piece[b];
	const U64 black_rooka     = bo->piece[r];
	const U64 black_queana    = bo->piece[q];
	const U64 black_kinga     = bo->piece[k];
	const U64 position_whitea = bo->position_white;
	const U64 position_blacka = bo->position_black;
	const U64 position_alll   = bo->position_white & bo->position_black;
	//const U64 en_pesanta      = bo->enpesant;
	//int side            = bo->side;
	//PROBOBLY NO THIS
	//if(square > 63 && square < 0) {
	//printf("OVERFLOW!!!\n");
	//return TRAP_OVERFLOW;
	//}



	if((side == white) && (black_pawn_attack_table[square] & white_pawna)) return 1;

	else if((side == black) && (white_pawn_attack_table[square] & black_pawna)) return 1;

	else if (knight_attack_table[square] & ((side == white) ? white_knighta : black_knighta)) return 1;

	else if(get_bishop_moves_magic(square, position_alll) & ((side == white) ? white_bishopa : black_bishopa)) return 1;

	else if(get_rook_moves_magic(square, position_alll) & ((side == white) ? white_rooka : black_rooka)) return 1;

	else if(get_quean_moves_magic(square, position_alll) & ((side == white) ? white_queana : black_queana)) return 1;

	else if(king_attack_table[square] & ((side == white) ? white_kinga : black_kinga)) return 1;

	else return 0;
	}



INLINE void sort_moves(const Board *__restrict__ bo, Moves *__restrict__ m) {
	for(int i = 1; i < m->counter; i++) {
		//IF IS CAPTURE FIRST
		if(CAPTURE(m->moves[i])) {
			int tempa = m->moves[i];
			m->moves[i] = m->moves[0];
			m->moves[0] = tempa;
			}
		/// IF PIECE IS CAPTURED LAST

		//P, N, B, R, Q, K, p, n,  r, b, q, k
		if(check_is_square_attacked_board(bo->side,TARGET(m->moves[i]),bo)
		    && (PIECE(m->moves[i]) == r ||  PIECE(m->moves[i]) == R
		        || PIECE(m->moves[i]) == Q  ||  PIECE(m->moves[i]) == q
		        || PIECE(m->moves[i]) == k  || PIECE(m->moves[i]) == K
		        || PIECE(m->moves[i]) == n  || PIECE(m->moves[i]) == N
		        || PIECE(m->moves[i]) == b  || PIECE(m->moves[i]) == B)) {
			int tempa = m->moves[i];
			m->moves[i] = m->moves[i - 1];
			m->moves[i - 1] = tempa;

			}
		}
	}
//}
//RATE THE MOVES WE WILL PICE VALUE
INLINE void rate_moves(const Board *__restrict__ bo, Moves *__restrict__ m) {
	for(int i = 0; i < m->counter; i++) {
		//IF MOVE CAPTURE
		//GET PIECE ON SQUARE
		m->value[i] = 0;
		int start_piece, stop_piece;
		int target = TARGET(m->moves[i]);
		int _piece    = PIECE(m->moves[i]);
		if(bo->side == WHITE) {
			start_piece = P;
			stop_piece  = K;
			}
		else {
			start_piece = p;
			stop_piece  = k;
			}
		//IF CAPTURE
		if(CAPTURE(m->moves[i])) {

			//LOOP OVER ALL IF PIECE IS GRATER++ ELSE--
			for(int j = start_piece; j <= stop_piece; j++) {
				if(GET(bo->piece[j], target)) {
					m->value[i] = j - _piece;
					}
				}
			}
		//IF QUIET
		else {
			m->value[i] = _piece;
			if(start_piece == P) {
				if(check_is_square_attacked_board(WHITE, target, bo)) {
					m->value[i]-=4;
					}
				}
			else {
				if(check_is_square_attacked_board(WHITE, target, bo)) {
					m->value[i]= _piece - 4;
					}
				}
			}

		}
	}


INLINE void sort_moves1(const Board *__restrict__ bo, Moves *__restrict__ m) {
	rate_moves(bo, m);

	for(int i = 0; i < m->counter; i++) {
		for(int j = i + 1; j < m->counter; j++) {
			if(m->value[j] > m->value[i]) {
				int tempa = m->moves[i];
				m->moves[i] = m->moves[j];
				m->moves[j] = tempa;
				int tempa_value = m->value[i];
				m->value[i] = m->value[j];
				m->value[j] = tempa_value;

				}
			}
		}
	}


//GENERATE MOVES MAIN FUNCTION WITCH GENERATES MOVES
//ACORDING TO CHESS PROGRAMING WIKI MAX AMOUNT OF MOVES IS 218
//PROBOBLY WE WILL HAVE SOME TYPE OF STRUCTURE IN WITCH WE WILL STORE MOVES

#define LOG_MOVES_PAWN    0
#define LOG_MOVES_KING    0
#define LOG_MOVES_KNIGHT  0
#define LOG_MOVES_BISHOP  0
#define LOG_MOVES_ROOK    0
#define LOG_MOVES_QUEAN   0
//CHANGE BOARD TO BE AS A POINTER
//#include <omp.h>

//MAKE HASH MAP STRUCTURE WITCH WILL STORE PREVIUSLY SEARCHED BOARDS
//IT WILL HAVE 100MB OF MEMORY(SIZE) AND USE ZOBRIST HASH FOR ACCESING BOARD VALUE

//#define HASHSIZE 1073741800
#define HASHSIZE 10737418

//#define HASHSIZE 107374
//4157458668

typedef struct {

	int   *__restrict__  score;
	U64   *__restrict__ zob;
	//Moves *moves;

	} Hashmap;


static U64 zob_table[64][12];

void init_hashmap(Hashmap *__restrict__ m) {

	m->score = (int*)calloc(HASHSIZE,sizeof(int));
	m->zob   = (U64*)calloc(HASHSIZE,sizeof(U64));
	//m->moves = (Moves*)calloc(HASHSIZE, sizeof(Moves));
	for(size_t j = 0; j < 12; j++)
		for(size_t i = 0; i < 64; i++) {
			zob_table[i][j] = rand64();
			printf("%lu\n", zob_table[i][j]);
			}
	}
//void free_hashmap(Hashmap *m);

INLINE  U64 hash(const Board *b) {
	U64 key = 0;
	for(int i = P; i <= k ; i++) {
		U64 bitboard = b->piece[i];

		while(bitboard) {

			int lsb = LSB(bitboard);
			key ^= zob_table[lsb][i];
			POP(bitboard, lsb);
			}


		}

	//printf("hash %u\n", key % HASHSIZE);
	//system("pause");
	return key;
	}

INLINE void store_position(Hashmap m,const Board *b, int score) {

	U64 i = hash(b);
	U64 index = i % HASHSIZE;
	m.zob[index] = i;
	m.score[index] = score;
	//Moves m;
	//generate_posible_moves(&b, &m, 1, 1);
	//memcpy(&m->moves, &m, sizeof(Moves));
	}
INLINE int return_score(Hashmap m,const Board *b, int *is_store) {
	U64 a = hash(b);
	U32 index = a % HASHSIZE;
	//printf("Index %d", index);
	if(m.zob[index] == a) {
		*is_store = 1;
		}
	else {
		*is_store = 0;
		}

	return m.score[index];
	}

//HAHSMAP FOR STORING THE MOVES

typedef struct {
	Moves *move;
	U64   *zob;
}HashMapM;


HashMapM hashmapm;

#define HASHMOVESIZE 1000000
void init_hashmap_moves(){
		hashmapm.move  = (Moves*)calloc(HASHMOVESIZE, sizeof(Moves));
		hashmapm.zob   = (U64*)calloc(HASHMOVESIZE, sizeof(U64));
	
}


INLINE void store_moves(const Board *b, Moves *m) {

	U64 i = hash(b);
	U64 index = i % HASHMOVESIZE;
	if(hashmapm.zob[index]==0){
			hashmapm.zob[index] = index;
			memcpy(&hashmapm.move[index], m, sizeof(Moves));		
	}

	//Moves m;
	//generate_posible_moves(&b, &m, 1, 1);
	//memcpy(&m->moves, &m, sizeof(Moves));
	}
INLINE Moves return_moves(const Board *b, int *is_store) {
	U64 a = hash(b);
	U32 index = a % HASHMOVESIZE;
	//printf("Index %d", index);
	if(hashmapm.zob[index] == a) {
		*is_store = 1;
		}
	else {
		*is_store = 0;
		}

	return hashmapm.move[index];
	}







INLINE void generate_posible_moves(const Board *__restrict__ bo, Moves *__restrict__ m,const int is_capture,const int is_quiet) {
	int is_store = 0;
	Moves move = return_moves(bo, &is_store);
	if(is_store == 1 && move.counter != 0){
			memcpy(m, &move, sizeof(Moves));
			return;
		}			


	static int target, source; // SQUER WITCH MOVE STARTS FROM AND WHER TO GO

	static U64 bitboard, attacks;

	m->counter = 0;                //RESET COUNTER
	//white pawn

	if(bo->side == white) {

		bitboard = bo->piece[P];

		while(bitboard) {
			//system("pause");
			source = LSB(bitboard);
			target = source - 8;   //ONE SQUARE FORWARD DIFERENCS IS 8
#if LOG_MOVES_PAWN
			print_board();
#endif
			//FORWARD MOVE
			//IF NOTING IS IN FORWARD SQUARE AND WE ARE NOT OUT OF BOARD
			if(!(target < 0)  && !GET((bo->position_alll), target)) {
				//printf("Nesto");

				// GENERATE PROMTION WE AS WHITE CAN PROMOTE PIECES IF THER ARE IN 7 RANK
				if(source <= h7 && source >= a7 ) {
#if LOG_MOVES_PAWN
					printf("white pawn promoted to q %s%s\n",squers_name[source], squers_name[target]);
					printf("white pawn promoted to n %s%s\n",squers_name[source], squers_name[target]);
					printf("white pawn promoted to r %s%s\n",squers_name[source], squers_name[target]);
					printf("white pawn promoted to b %s%s\n",squers_name[source], squers_name[target]);
#endif
//         ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_quiet) {
						m->moves[m->counter++] = ENCODE(source, target,P, Q, 0, 0,0,0);
						m->moves[m->counter++] = ENCODE(source, target,P, R, 0, 0,0,0);
						m->moves[m->counter++] = ENCODE(source, target,P, N, 0, 0,0,0);
						m->moves[m->counter++] = ENCODE(source, target,P, B, 0, 0,0,0);
						}

					}

				//ONE AND TWO FORWARD MOVES
				else {
					//CHECK ON TOP
#if LOG_MOVES_PAWN
					printf("white pawn moved to %s%s\n",squers_name[source], squers_name[target]);
#endif
					if(is_quiet)
						m->moves[m->counter++] = ENCODE(source, target,P,0,0,0,0,0);
					//CHECK IF TWO MOVES FORWARD IS POSIBLE
					if(source <= h2 && source >= a2 && (!GET((bo->position_alll), (target - 8)))) {
						if(is_quiet)
							m->moves[m->counter++] = ENCODE(source, (target-8),P,0,0,1,0,0);
#if LOG_MOVES_PAWN
						printf("white pawn moved 2 to %s%s\n",squers_name[source], squers_name[target - 8]);
#endif

						}

					}
				}
			// CAPTURES
			attacks  = white_pawn_attack_table[source] & bo->position_black; // THIS IS CHECK IS THER A PIECE ON ATTACKED SQUERS
			//print_bitboard(attacks);
			while(attacks) {
				//source alredy init
				target = LSB(attacks);
				// GENERATE PROMTION WE AS WHITE CAN PROMOTE PIECES IF THER ARE IN 7 RANK
				if(source <= h7 && source >= a7) {
#if LOG_MOVES_PAWN
					printf("white pawn capture promoted to q %s%s\n",squers_name[source], squers_name[target]);
					printf("white pawn capture promoted to n %s%s\n",squers_name[source], squers_name[target]);
					printf("white pawn capture promoted to r %s%s\n",squers_name[source], squers_name[target]);
					printf("white pawn capture promoted to b %s%s\n",squers_name[source], squers_name[target]);
#endif
//        ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_capture) {
						m->moves[m->counter++] = ENCODE(source, target,P, Q, 1, 0,0,0);
						m->moves[m->counter++] = ENCODE(source, target,P, R, 1, 0,0,0);
						m->moves[m->counter++] = ENCODE(source, target,P, N, 1, 0,0,0);
						m->moves[m->counter++] = ENCODE(source, target,P, B, 1, 0,0,0);

						}


					}

				//ONE AND TWO FORWARD MOVES
				else {
					//CHECK ON TOP
#if LOG_MOVES_PAWN
					printf("white pawn capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
//        ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_capture)
						m->moves[m->counter++] = ENCODE(source, target, P, 0, 1, 0, 0, 0);
					}
				POP(attacks, target);
				}

			//ENPESANT
			if(bo->enpesant != -1) {
				U64 en =  white_pawn_attack_table[source] & (1 << bo->enpesant);
				//print_bitboard(en);
				//system("pause");

				if(en) {
					int target_en = LSB(en);
#if LOG_MOVES_PAWN
					printf("white pawn capture_EN to %s%s\n",squers_name[source], squers_name[target_en]);
#endif
//         ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_capture) {
						m->moves[m->counter++] = ENCODE(source, target_en,P, 0, 1, 0, 1, 0);
						}


					}

				}
			POP(bitboard, source);
			}

		//white king

		bitboard = bo->piece[K];
		source = LSB(bitboard);

		//CHECK IS CASTLING POSIBLE 0 2 K Q
		if(castle[0] && !GET(bo->position_alll, f1) && !GET(bo->position_alll, g1)) {
			//MAYBE CHECK IS CHECK BUT IF CHECK ONLY LEGAL MOVES ARE WITH KING
			//if(check_is_square_attacked_board(black,f1, bo) == 0 && check_is_square_attacked_board(black, g1, bo) == 0) {
				{

#if LOG_MOVES_KING
				printf("WHITE CASTLE KING\n");
#endif
				//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
				if(is_quiet) {
					m->moves[m->counter++] = ENCODE(source, g1,K, 0, 0, 0,0,1);

					}

				}
			}
		//QUEAN SIDE CASTLING
		if(castle[2] && !GET(bo->position_alll, b1) && !GET(bo->position_alll, c1)&& !GET(bo->position_alll, d1)) {
			//	if(check_is_square_attacked_board(black,d1, bo) == 0
			//	    && check_is_square_attacked_board(black,c1, bo) == 0
			//	    && check_is_square_attacked_board(black, b1, bo) == 0)
				{
#if LOG_MOVES_KING
				printf("WHITE CASTLE QUEAN\n");
#endif
				//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
				if(is_quiet)
					m->moves[m->counter++] = ENCODE(source, c1,K, 0, 0, 0,0,1);

				}
			}



		//CHECK OTHER KING MOVES
		while(bitboard) {
			source = LSB(bitboard);
			//WHERE IS NO WHITE PIECE
			attacks = king_attack_table[source] & ~(bo->position_white);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(bo->position_black, target)) {  // NO
#if LOG_MOVES_KING
					printf("white king move to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_quiet)
						m->moves[m->counter++] = ENCODE(source, target,K, 0, 0, 0, 0, 0);

					}

				else { //CAPTURE
#if LOG_MOVES_KING
					printf("white king capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_capture)
						m->moves[m->counter++] = ENCODE(source, target,K, 0, 1, 0, 0, 0);

					}

				POP(attacks,target);
				}

			POP(bitboard, source);
			}








		//white knight

		bitboard = bo->piece[N];
		while(bitboard) {
			source = LSB(bitboard);
			//WHERE IS NO WHITE PIECE
			attacks = knight_attack_table[source] & ~(bo->position_white);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(bo->position_black, target)) {  // NO
#if LOG_MOVES_KNIGHT
					printf("white knight move to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_quiet)
						m->moves[m->counter++] = ENCODE(source, target, N, 0, 0, 0, 0, 0);

					}

				else { //CAPTURE
#if LOG_MOVES_KNIGHT
					printf("white knight capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_capture)
						m->moves[m->counter++] = ENCODE(source, target, N, 0, 1, 0, 0, 0);
					}

				POP(attacks,target);
				}

			POP(bitboard, source);
			}


		//white bishop

		bitboard = bo->piece[B];
		while(bitboard) {
			source = LSB(bitboard);
			//GET BISHOPS ATTACKS
			attacks = get_bishop_moves_magic(source, bo->position_alll) & ~(bo->position_white);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(bo->position_black, target)) {  // NO
#if LOG_MOVES_BISHOP
					printf("white bishop move to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_quiet)
						m->moves[m->counter++] = ENCODE(source, target, B, 0, 0, 0, 0, 0);
					}

				else { //CAPTURE
#if LOG_MOVES_BISHOP
					printf("white bishop capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_capture)
						m->moves[m->counter++] = ENCODE(source, target, B, 0, 1, 0, 0, 0);
					}

				POP(attacks,target);
				}

			POP(bitboard, source);
			}




		//white rook

		bitboard = bo->piece[R];
		while(bitboard) {
			source = LSB(bitboard);
			//GET ROOK ATTACKS
			attacks = get_rook_moves_magic(source, bo->position_alll) & ~(bo->position_white);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(bo->position_black, target)) {  // NO
#if LOG_MOVES_ROOK
					printf("white rook move to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_quiet)
						m->moves[m->counter++] = ENCODE(source, target, R, 0, 0, 0, 0, 0);
					}

				else { //CAPTURE
#if LOG_MOVES_ROOK
					printf("white rook capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_capture)
						m->moves[m->counter++] = ENCODE(source, target, R, 0, 1, 0, 0, 0);
					}

				POP(attacks,target);
				}

			POP(bitboard, source);
			}




		//white quean

		bitboard = bo->piece[Q];
		while(bitboard) {
			source = LSB(bitboard);
			//GET ROOK ATTACKS
			attacks = get_quean_moves_magic(source, bo->position_alll) & ~(bo->position_white);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(bo->position_black, target)) {  // NO
#if LOG_MOVES_QUEAN
					printf("white quean move to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_quiet)
						m->moves[m->counter++] = ENCODE(source, target, Q, 0, 0, 0, 0, 0);
					}

				else { //CAPTURE
#if LOG_MOVES_QUEAN
					printf("white quean capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_capture)
						m->moves[m->counter++] = ENCODE(source, target, Q, 0, 1, 0, 0, 0);

					}

				POP(attacks,target);
				}

			POP(bitboard, source);
			}



		}
//++++++++++++++++++++++++++++++++BLACK PIECES++++++++++++++++++++++++++++++++


	//black pawn
	if(bo->side == black) {

		bitboard = bo->piece[p];
		while(bitboard) {

			source = LSB(bitboard);
			target = source + 8;   //ONE SQUARE FORWARD DIFERENCS IS 8
#if LOG_MOVES_PAWN
			//print_board();
#endif
			//FORWARD MOVE
			//IF NOTING IS IN FORWARD SQUARE AND WE ARE NOT OUT OF BOARD
			if(!(target >= 63)  && !GET((bo->position_alll), target)) {
				//printf("Nesto");

				// GENERATE PROMTION WE AS WHITE CAN PROMOTE PIECES IF THER ARE IN 7 RANK
				if(source <= h2 && source >= a2 ) {
#if LOG_MOVES_PAWN
					printf("black pawn promoted to q %s%s\n",squers_name[source], squers_name[target]);
					printf("black pawn promoted to n %s%s\n",squers_name[source], squers_name[target]);
					printf("black pawn promoted to r %s%s\n",squers_name[source], squers_name[target]);
					printf("white pawn promoted to b %s%s\n",squers_name[source], squers_name[target]);
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)

#endif
					if(is_quiet) {
						m->moves[m->counter++] = ENCODE(source, target, p, q, 0, 0, 0, 0);
						m->moves[m->counter++] = ENCODE(source, target, p, n, 0, 0, 0, 0);
						m->moves[m->counter++] = ENCODE(source, target, p, r, 0, 0, 0, 0);
						m->moves[m->counter++] = ENCODE(source, target, p, b, 0, 0, 0, 0);

						}

					}

				//ONE AND TWO FORWARD MOVES
				else {
					//CHECK ON TOP
#if LOG_MOVES_PAWN
					printf("black pawn moved to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_quiet)
						m->moves[m->counter++] = ENCODE(source, target, p, 0, 0, 0, 0, 0);
					//CHECK IF TWO MOVES FORWARD IS POSIBLE
					if(source <= h7 && source >= a7 && (!GET((bo->position_alll), (target + 8)))) {
#if LOG_MOVES_PAWN
						printf("black pawn moved 2 to %s%s\n",squers_name[source], squers_name[target + 8]);
#endif
						//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
						if(is_quiet)
							m->moves[m->counter++] = ENCODE(source, (target + 8), p, 0, 0, 1, 0, 0);
						}

					}
				}
			// CAPTURES
			attacks  = black_pawn_attack_table[source] & bo->position_white; // THIS IS CHECK IS THER A PIECE ON ATTACKED SQUERS

			while(attacks) {
				//source alredy init
				target = LSB(attacks);
				// GENERATE PROMTION WE AS WHITE CAN PROMOTE PIECES IF THER ARE IN 7 RANK
				if(source <= h2 && source >= a2) {
#if LOG_MOVES_PAWN
					printf("black pawn capture promoted to q %s%s\n",squers_name[source], squers_name[target]);
					printf("black pawn capture promoted to n %s%s\n",squers_name[source], squers_name[target]);
					printf("black pawn capture promoted to r %s%s\n",squers_name[source], squers_name[target]);
					printf("black pawn capture promoted to b %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_capture) {
						m->moves[m->counter++] = ENCODE(source, target, p, q, 1, 0, 0, 0);
						m->moves[m->counter++] = ENCODE(source, target, p, n, 1, 0, 0, 0);
						m->moves[m->counter++] = ENCODE(source, target, p, r, 1, 0, 0, 0);
						m->moves[m->counter++] = ENCODE(source, target, p, b, 1, 0, 0, 0);
						}

					}

				//ONE AND TWO FORWARD MOVES
				else {
					//CHECK ON TOP
#if LOG_MOVES_PAWN
					printf("black pawn capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_capture)
						m->moves[m->counter++] = ENCODE(source, target, p, 0, 1, 0, 0, 0);

					}
				POP(attacks, target);
				}
			//ENPESANT
			if(bo->enpesant != -1) {
				U64 en =  black_pawn_attack_table[source] & (1 << bo->enpesant);
				//print_bitboard(en);
				//system("pause");

				if(en) {
					int target_en = LSB(en);
#if LOG_MOVES_PAWN
					printf("black pawn capture_EN to %s%s\n",squers_name[source], squers_name[target_en]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_capture)
						m->moves[m->counter++] = ENCODE(source, target_en, p, 0, 1, 0, 1, 0);
					}

				}

			POP(bitboard, source);
			}

		//black king

		bitboard = bo->piece[k];

		source = LSB(bitboard);

		//CHECK IS CASTLING POSIBLE 1 3 k q
		if(castle[1] && !GET(bo->position_alll, f8) && !GET(bo->position_alll, g8)) {
			//MAYBE CHECK IS CHECK BUT IF CHECK ONLY LEGAL MOVES ARE WITH KING
			//if(check_is_square_attacked_board(white,f8, bo) == 0 && check_is_square_attacked_board(white,g8, bo) == 0)
				{
#if LOG_MOVES_KING
				printf("BLACK CASTLE KING\n");
#endif
				//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
				if(is_quiet)
					m->moves[m->counter++] = ENCODE(source, g8, k, 0, 0, 0, 0, 1);
				}



			}
		//QUEAN SIDE CASTLING
		if(castle[3] && !GET((bo->position_alll), d8)
		    && !GET(bo->position_alll, c8) && !GET(bo->position_alll, b8)) {
//			if(check_is_square_attacked_board(white,d8, bo) == 0 && check_is_square_attacked_board(white,c8, bo) == 0
//			    && check_is_square_attacked_board(white,b8, bo) == 0)
				{
				//MAYBE NO B8
#if LOG_MOVES_KING
				printf("BLACK CASTLE QUEAN\n");
#endif
				//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
				if(is_quiet)
					m->moves[m->counter++] = ENCODE(source, c8, k, 0, 0, 0, 0, 1);
				}
			}

		while(bitboard) {
			source = LSB(bitboard);
			//WHERE IS NO WHITE PIECE
			attacks = king_attack_table[source] & ~(bo->position_black);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(bo->position_white, target)) {  // NO
#if LOG_MOVES_KING
					printf("black king move to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_quiet)
						m->moves[m->counter++] = ENCODE(source, target, k, 0, 0, 0, 0, 0);
					}

				else { //CAPTURE
#if LOG_MOVES_KING
					printf("black king capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_capture)
						m->moves[m->counter++] = ENCODE(source, target, k, 0, 1, 0, 0, 0);
					}

				POP(attacks,target);
				}

			POP(bitboard, source);
			}




		//black knight

		bitboard = bo->piece[n];

		while(bitboard) {
			source = LSB(bitboard);
			//WHERE IS NO WHITE PIECE
			attacks = knight_attack_table[source] & ~(bo->position_black);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(bo->position_white, target)) {  // NO
#if LOG_MOVES_KNIGHT
					printf("black knight move to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_quiet)
						m->moves[m->counter++] = ENCODE(source, target, n, 0, 0, 0, 0, 0);
					}

				else { //CAPTURE
#if LOG_MOVES_KNIGHT
					printf("black knight capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_capture)
						m->moves[m->counter++] = ENCODE(source, target, n, 0, 1, 0, 0, 0);
					}

				POP(attacks,target);
				}

			POP(bitboard, source);
			}





		//black bishop

		bitboard = bo->piece[b];
		while(bitboard) {
			source = LSB(bitboard);
			//GET BISHOPS ATTACKS
			attacks = get_bishop_moves_magic(source, bo->position_alll) & ~(bo->position_black);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(bo->position_white, target)) {  // NO
#if LOG_MOVES_BISHOP
					printf("black bishop move to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_quiet)
						m->moves[m->counter++] = ENCODE(source, target, b, 0, 0, 0, 0, 0);
					}

				else { //CAPTURE
#if LOG_MOVES_BISHOP
					printf("black bishop capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					//b is alredy declared so bo
					if(is_capture)
						m->moves[m->counter++] = ENCODE(source, target, (b), 0, 1, 0, 0, 0);
					}

				POP(attacks,target);
				}

			POP(bitboard, source);
			}



		//black rook

		bitboard = bo->piece[r];
		while(bitboard) {
			source = LSB(bitboard);
			//GET ROOK ATTACKS
			attacks = get_rook_moves_magic(source, bo->position_alll) & ~(bo->position_black);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(bo->position_white, target)) {  // NO
#if LOG_MOVES_ROOK
					printf("black rook move to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_quiet)
						m->moves[m->counter++] = ENCODE(source, target, r, 0, 0, 0, 0, 0);
					}

				else { //CAPTURE
#if LOG_MOVES_ROOK
					printf("black rook capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_capture)
						m->moves[m->counter++] = ENCODE(source, target, r, 0, 1, 0, 0, 0);
					}

				POP(attacks,target);
				}

			POP(bitboard, source);
			}



		//black quean

		bitboard = bo->piece[q];
		while(bitboard) {
			source = LSB(bitboard);
			//GET ROOK ATTACKS
			attacks = get_quean_moves_magic(source, bo->position_alll) & ~(bo->position_black);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(bo->position_white, target)) {  // NO
#if LOG_MOVES_QUEAN
					printf("black quean move to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_quiet)
						m->moves[m->counter++] = ENCODE(source, target, q, 0, 0, 0, 0, 0);
					}

				else { //CAPTURE
#if LOG_MOVES_QUEAN
					printf("black quean capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					if(is_capture)
						m->moves[m->counter++] = ENCODE(source, target, q, 0, 1, 0, 0, 0);
					}

				POP(attacks,target);
				}

			POP(bitboard, source);
			}
		}


	///* //ORDER OF MOVES FOR SEARCH
	//sort_moves(bo, m);
	sort_moves1(bo, m);
	store_moves(bo, m);
	//*/


	}



const char promoted_pieces[] = {
	[Q] = 'q',
	[R] = 'r',
	[B] = 'b',
	[N] = 'n',
	[q] = 'q',
	[r] = 'r',
	[b] = 'b',
	[n] = 'n'
	};
const char ascii_pieces[12] = "PNBRQKpnbrqk";

void print_move_list(Moves *move_list) {
	// do nothing on empty move list
	if (!move_list->counter) {
		printf("\n     No move in the move list!\n");
		return;
		}

	printf("\n     move    piece     capture   double    enpass    castling\n\n");

	// loop over moves within a move list
	for (int move_count = 0; move_count < move_list->counter; move_count++) {
		// init move
		printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		int move = move_list->moves[move_count];


		// print move
		printf("      %s%s%c   %c         %d         %d         %d         %d\n", squers_name[SOURCE(move)],
		       squers_name[TARGET(move)],
		       PROMOTED(move) ? promoted_pieces[PROMOTED(move)] : ' ',
		       ascii_pieces[PIECE(move)],
		       CAPTURE(move) ? 1 : 0,
		       DOUBLE(move) ? 1 : 0,
		       ENPESANT(move) ? 1 : 0,
		       CASTLING(move) ? 1 : 0);

		}

	// print total number of moves
	printf("\n\n     Total number of moves: %d\n\n", move_list->counter);

	}


//SORT BEST MOVES







#define LOG_MOVES 0
// FUNCTION USED TO GENARTES MOVE AND RETURN IT WE ACCEPT BOARD STRUCTURE AS INPUT
__attribute__((always_inline))
static inline void make_move(Board *__restrict__ board, int move) {
	Board temp;// = &board;
	memcpy(&temp, board, sizeof(Board));
	//temp = board;  // LIKE MEMCPY WITHOUT ONE
	//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
	//DECODE MOVE
	int source    = SOURCE(move);
	int target    = TARGET(move);
	int piece     = PIECE(move);
	int promoted  = PROMOTED(move);
	int capture   = CAPTURE(move);
	int doubl     = DOUBLE(move);
	int en_pesant = ENPESANT(move);
	int castling  = CASTLING(move);

	POP(board->piece[piece], source);
	SET(board->piece[piece], target); //WE WILL SEE
#if LOG_MOVES
	printf("      %s%s%c   %c         %d         %d         %d         %d\n", squers_name[SOURCE(move)],
	       squers_name[TARGET(move)],
	       PROMOTED(move) ? promoted_pieces[PROMOTED(move)] : ' ',
	       ascii_pieces[PIECE(move)],
	       CAPTURE(move) ? 1 : 0,
	       DOUBLE(move) ? 1 : 0,
	       ENPESANT(move) ? 1 : 0,
	       CASTLING(move) ? 1 : 0);

#endif


	if(capture) {
		int start_piece, end_piece;   // we will loop over this pieces

		if(board->side == white) {
			start_piece = p;
			end_piece   = k;
			}

		else { //BLACK
			start_piece = P;
			end_piece   = K;
			}

		// LOOP OVER ALL PIECES
		for(int pi= start_piece; pi <= end_piece; pi++) {
			if(GET(board->piece[pi], target)) {  //IF PIECE IS ON SQUARE
				POP(board->piece[pi], target);


				}
			}
		}
	if (promoted) {

		if (board->side == white) {
			POP(board->piece[P], target);
			}

		else {
			POP(board->piece[p], target);
			}

		// PROMOTE PIECE
		SET(board->piece[promoted], target);
		}


	if(en_pesant) {
		//	printf("Enpesant");
		// GET RID OF THE PAWN ON THE SQUARE CUZZ ITS SAVED AS
		(board->side == white) ? POP(board->piece[p], (target  + 8))
		: POP(board->piece[P], (target - 8) );
		//DOES IT WORKS
		}

	// ENCODE A ENPESANT MOVE
	if(doubl) {
		(side == white) ? board->enpesant = (target + 8) : (target - 8);
		}
	//KING IS INITALI MOVED AND NOW W E NEAD TO MOVE ROOK TO A SQUARE
	if (castling) {
		//
		switch (target) {

			case (g1):

				POP(board->piece[R], h1);
				SET(board->piece[R], f1);
				break;


			case (c1):
				POP(board->piece[R], a1);
				SET(board->piece[R], d1);
				break;

			// black castles king side
			case (g8):
				POP(board->piece[r], h8);
				SET(board->piece[r], f8);
				break;


			case (c8):
				POP(board->piece[r], a8);
				SET(board->piece[r], d8);
				break;
			}
		}


	//UPDATE POSITION BITBOARDS CUZZ IS NESESARY TO CHECK IS CHECK
	board->position_white = 0;
	board->position_black = 0;
	board->position_alll  = 0;
	board->enpesant       = -1;
	board->side          ^=  1;

	for(int i = P; i <= K; i++) {
		board->position_white |= board->piece[i];
		}
	for(int i = p; i <= k; i++) {
		board->position_black |= board->piece[i];
		}
	board->position_alll = (board->position_white | board->position_black);
	//CHECK IS MOVE LEGAL AND UPDATE KING CASTTLING RIGHTS
	if(!GET(board->piece[K], e1)) {
		board->castle[0] = 0;
		board->castle[2] = 0;

		}

	if(!GET(board->piece[R], a1))
		board->castle[2] = 0;

	if(!GET(board->piece[R], h1))
		board->castle[0] = 0;



	// BLACK
	if(!GET(board->piece[k],e8)) {
		board->castle[1] = 0;
		board->castle[3] = 0;

		}

	if(!GET(board->piece[r], a8))
		board->castle[3] = 0;

	if(!GET(board->piece[r], h8))
		board->castle[1] = 0;



	//CHECK IS MOVE ILEGAL MOVE IS ILEGAL IF KING IS UNDER THE CHECK AFTER THE MOVE WE WANTED
	//TO PLAY
	///*
//	if(!board->side == white && (check_is_square_attacked_board(!board->side, LSB(board->piece[K]), &board))) {
	//printf("Ilegel!!! LSB(board) = %s\n",squers_name[LSB(board->piece[K])]);
	//system("pause");
	//memcpy(&board, &temp,sizeof(Board)); // RESTORE BOARD
	//return TRAP_ILEGAL;
	//}

	static int sq;
	if(board->side == white)
		sq = LSB(board->piece[k]);
	else
		sq = LSB(board->piece[K]);


	//int isincheck = check_is_square_attacked_board(board->side,sq, board);
	//if(isincheck == 1 && 0) {

	//printf("Is in Check %d!!!\n", isincheck);
	//printf("squere %s\n", squers_name[sq]);
	//print_board();
	//memcpy(board, &temp,sizeof(Board));
	//system("pause");
	//board = &temp;

	//return TRAP_ILEGAL;
	//}

	//return TRAP_MOVE_OK;
	}
//enum { P, N, B, R, Q, K, p, n,  r, b, q, k };

#define LOG_EVALUATION 0

#define inf 10000000
int mg_table[6][64] = {{
		0,   0,   0,   0,   0,   0,  0,   0,
		98, 134,  61,  95,  68, 126, 34, -11,
		-6,   7,  26,  31,  65,  56, 25, -20,
		-14,  13,   6,  21,  23,  12, 17, -23,
		-27,  -2,  -5,  12,  17,   6, 10, -25,
		-26,  -4,  -4, -10,   3,   3, 33, -12,
		-35,  -1, -20, -23, -15,  24, 38, -22,
		0,   0,   0,   0,   0,   0,  0,   0,
		}


	,{
		-167, -89, -34, -49,  61, -97, -15, -107,
		  -73, -41,  72,  36,  23,  62,   7,  -17,
		  -47,  60,  37,  65,  84, 129,  73,   44,
		  -9,  17,  19,  53,  37,  69,  18,   22,
		  -13,   4,  16,  13,  28,  19,  21,   -8,
		  -23,  -9,  12,  10,  19,  17,  25,  -16,
		  -29, -53, -12,  -3,  -1,  18, -14,  -19,
		  -105, -21, -58, -33, -17, -28, -19,  -23,
		  }


	,{
		-29,   4, -82, -37, -25, -42,   7,  -8,
		  -26,  16, -18, -13,  30,  59,  18, -47,
		  -16,  37,  43,  40,  35,  50,  37,  -2,
		  -4,   5,  19,  50,  37,  37,   7,  -2,
		  -6,  13,  13,  26,  34,  12,  10,   4,
		  0,  15,  15,  15,  14,  27,  18,  10,
		  4,  15,  16,   0,   7,  21,  33,   1,
		  -33,  -3, -14, -21, -13, -12, -39, -21,
		  }


	,{
		32,  42,  32,  51, 63,  9,  31,  43,
		27,  32,  58,  62, 80, 67,  26,  44,
		-5,  19,  26,  36, 17, 45,  61,  16,
		-24, -11,   7,  26, 24, 35,  -8, -20,
		-36, -26, -12,  -1,  9, -7,   6, -23,
		-45, -25, -16, -17,  3,  0,  -5, -33,
		-44, -16, -20,  -9, -1, 11,  -6, -71,
		-19, -13,   1,  17, 16,  7, -37, -26,
		}

	,{
		-28,   0,  29,  12,  59,  44,  43,  45,
		  -24, -39,  -5,   1, -16,  57,  28,  54,
		  -13, -17,   7,   8,  29,  56,  47,  57,
		  -27, -27, -16, -16,  -1,  17,  -2,   1,
		  -9, -26,  -9, -10,  -2,  -4,   3,  -3,
		  -14,   2, -11,  -2,  -5,   2,  14,   5,
		  -35,  -8,  11,   2,   8,  15,  -3,   1,
		  -1, -18,  -9,  10, -15, -25, -31, -50,
		  }


	,{
		-65,  23,  16, -15, -56, -34,   2,  13,
		  29,  -1, -20,  -7,  -8,  -4, -38, -29,
		  -9,  24,   2, -16, -20,   6,  22, -22,
		  -17, -20, -12, -27, -30, -25, -14, -36,
		  -49,  -1, -27, -39, -46, -44, -33, -51,
		  -14, -14, -22, -46, -44, -30, -15, -27,
		  1,   7,  -8, -64, -43, -16,   9,   8,
		  -15,  36,  12, -54,   8, -28,  24,  14,
		  }
	};



INLINE int max(int maxEval, int eval) {

	if(eval > maxEval)
		return eval;

	return maxEval;
	}

INLINE int min(int minEval,int eval) {

	if(eval < minEval)
		return eval;

	return minEval;
	}

//


//NEW
//VALUE OF PIECES
const int evaluation_piece[] = {1000,  3000,  3000,  5000,  10000,  1000000,
                                -1000, -3000, -3000, -5000, -10000, -1000000,
                                };


const int pawn_score[64] = {
	90,  90,  90,  90,  90,  90,  90,  90,
	30,  30,  30,  40,  40,  30,  30,  30,
	20,  20,  20,  30,  30,  30,  20,  20,
	10,  10,  10,  20,  20,  10,  10,  10,
	5,   5,  10,  20,  20,   5,   5,   5,
	0,   0,   0,   5,   5,   0,   0,   0,
	0,   0,   0, -10, -10,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0
	};

// knight positional score
const int knight_score[64] = {
	-5,   0,   0,   0,   0,   0,   0,  -5,
	  -5,   0,   0,  10,  10,   0,   0,  -5,
	  -5,   5,  20,  20,  20,  20,   5,  -5,
	  -5,  10,  20,  30,  30,  20,  10,  -5,
	  -5,  10,  20,  30,  30,  20,  10,  -5,
	  -5,   5,  20,  10,  10,  20,   5,  -5,
	  -5,   0,   0,   0,   0,   0,   0,  -5,
	  -5, -10,   0,   0,   0,   0, -10,  -5
	  };

// bishop positional score
const int bishop_score[64] = {
	0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,  10,  10,   0,   0,   0,
	0,   0,  10,  20,  20,  10,   0,   0,
	0,   0,  10,  20,  20,  10,   0,   0,
	0,  10,   0,   0,   0,   0,  10,   0,
	0,  30,   0,   0,   0,   0,  30,   0,
	0,   0, -10,   0,   0, -10,   0,   0

	};

// rook positional score
const int rook_score[64] = {
	50,  50,  50,  50,  50,  50,  50,  50,
	50,  50,  50,  50,  50,  50,  50,  50,
	0,   0,  10,  20,  20,  10,   0,   0,
	0,   0,  10,  20,  20,  10,   0,   0,
	0,   0,  10,  20,  20,  10,   0,   0,
	0,   0,  10,  20,  20,  10,   0,   0,
	0,   0,  10,  20,  20,  10,   0,   0,
	0,   0,   0,  20,  20,   30,   0,   0

	};

// king positional score
const int king_score[64] = {
	0,   0,     0,    0,    0,    0,    0,   0,
	0,   0,    -5,   -5,   -5,   -5,    0,   0,
	0,   -5,   -5,  -10,  -10,   -5,  -5,   0,
	0,   -5,  -10,  -20,  -20,   -10, -5,   0,
	0,   -5,  -10,  -20,  -20,   -10, -5,   0,
	0,   0,    -5,  -10,   -10,   -5,   0,   0,
	0,   -5,   -5,  -5,   -5,     0,  -5,   0,
	0,    0,    40,   0,  -15,    0,  50,   0
	};

// mirror positional score tables for opposite side
const int mirror_score[128] = {
	a1, b1, c1, d1, e1, f1, g1, h1,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a8, b8, c8, d8, e8, f8, g8, h8
	};

INLINE int evaluate( Board board) {

	int  square;
	int score = 0;
	for(int i = P; i <= k; i++) {
		U64 bitboard =  board.piece[i];
		while(bitboard) {
			square = LSB(bitboard);
			if (check_is_square_attacked(WHITE, square))
				score+=4;
			if(check_is_square_attacked(BLACK, square)) {
				score-=4;
				}

			score += evaluation_piece[i];
			switch(i) {
				case P:
					score+=pawn_score[square];
					break;
				case N:
					score+=knight_score[square];
					break;
				case B:
					score+=bishop_score[square];
					break;
				case R:
					score+=rook_score[square];
					break;
				case Q:
					score+=(rook_score[square] + bishop_score[square] + pawn_score[square]);
					break;
				case K:
					score+=king_score[square];
					break;

				case p:
					score-=pawn_score[mirror_score[square]];
					break;
				case n:
					score-=knight_score[mirror_score[square]];
					break;
				case b:
					score-=bishop_score[mirror_score[square]];
					break;
				case r:
					score-=rook_score[mirror_score[square]];
					break;
				case q:
					score-=(rook_score[mirror_score[square]] + bishop_score[mirror_score[square]] + pawn_score[mirror_score[square]]);
					break;
				case k:
					score-=king_score[mirror_score[square]];
					break;

				}

			POP(bitboard, square);
			}


		}
	if((board.side == white) && (board.piece[K] == 0))
		score-=inf;

	else if((board.side == black) && (board.piece[k] == 0))
		score+=inf;

//	for(Squeres square = a8; square <=h1; sqaare++ ){

//	}


	//store_position(hm, board, (board.side == white) ? score : -score);
//	return (board.side == white) ? score+rand()%20 : -score-rand()%20;
	return (board.side == white) ? score : -score;
	}

//TEMP MUST BE DECLARED
#define copy_board() memcpy(&temp,  board, sizeof(Board))
#define take_board() memcpy(board, &temp, sizeof(Board))

/**
* Evaluation subroutine suitable for chess engines.
* -------------------------------------------------
* Piece codes are
*     wking=1, wqueen=2, wrook=3, wbishop= 4, wknight= 5, wpawn= 6,
*     bking=7, bqueen=8, brook=9, bbishop=10, bknight=11, bpawn=12,
* Square are
*     A1=0, B1=1 ... H8=63
* Input format:
*     piece[0] is white king, square[0] is its location
*     piece[1] is black king, square[1] is its location
*     ..
*     piece[x], square[x] can be in any order
*     ..
*     piece[n+1] is set to 0 to represent end of array
*/

#ifdef NNUE
INLINE int evaluate_nn(Board *__restrict__ bo) {

	static int pieces[33];
	static int squares[33];

	const int wking=1, wqueen=2, wrook=3, wbishop= 4, wknight= 5, wpawn= 6;
	const int bking=7, bqueen=8, brook=9, bbishop=10, bknight=11, bpawn=12;
	int counter = 2;
	int square, score = 0;
	pieces[0]  = wking;
	squares[0] = 	mirror_score[LSB(bo->piece[K])];
	pieces[1]  = bking;
	squares[1] = 	mirror_score[LSB(bo->piece[k])];


	for(int i = P; i <= k; i++) {
		U64 bitboard =  bo->piece[i];
		while(bitboard) {
			square = LSB(bitboard);
#ifdef EVAL_SQUARE
			if (check_is_square_attacked(WHITE, square))
				score+=EVAL_SQUARE;
			if(check_is_square_attacked(BLACK, square)) {
				score-=EVAL_SQUARE;
				}
#endif
			//int squarea = mirror_score[square];
			int squarea = mirror_score[square];
			switch(i) {
				case P:
					pieces[counter] = wpawn;
					squares[counter] = squarea;
					break;
				case N:
					pieces[counter] = wknight;
					squares[counter] = squarea;
					break;
				case B:
					pieces[counter] = wbishop;
					squares[counter] = squarea;
					break;
				case R:
					pieces[counter] = wrook;
					squares[counter] = squarea;
					break;
				case Q:
					pieces[counter] = wqueen;
					squares[counter] = squarea;
					break;


				case p:
					pieces[counter] = bpawn;
					squares[counter] = squarea;
					break;
				case n:
					pieces[counter] = bknight;
					squares[counter] = squarea;
					break;
				case b:
					pieces[counter] = bbishop;
					squares[counter] = squarea;
					break;
				case r:
					pieces[counter] = brook;
					squares[counter] = squarea;
					break;
				case q:
					pieces[counter] = bqueen;
					squares[counter] = squarea;
					break;

				default:
					counter--;
					break;
				}
			counter++;
			POP(bitboard, square);
			}


		}

	pieces[counter]  = 0;
	squares[counter] = 0;
	score  += evaluate_nnue(bo->side, pieces, squares);
	if((bo->side == white) && (bo->piece[K] == 0))
		score = -inf;


	if((bo->side == black) && (bo->piece[k] == 0))
		score = -inf;
	if((bo->side == white) && (bo->piece[k] == 0))
		score = inf;


	if((bo->side == black) && (bo->piece[K] == 0))
		score = inf;
	//	return (bo->side == white) ? inf : -inf;

	//return (bo->side == white) ? score : -score;
	return score; //+ rand()%2 - 4;
	//return score;
	}
#endif

static int quiescence(Hashmap hm, Board *__restrict__ board, int alpha, int beta) {

	Board temp;
	Moves m;
	copy_board();



	int is_store = 0;
	int sc = return_score(hm, board, &is_store);
	if(is_store == 1)
		return sc;





	//int evaluation = evaluate(temp);
#ifdef NNUE
	int evaluation = evaluate_nn(board);
#endif
#ifndef NNUE
	int evaluation = evaluate(temp);
#endif
	if (evaluation >= beta) {
		store_position(hm, board, beta);
		return beta;
		}

	if (evaluation > alpha) {
		alpha = evaluation;
		}

	generate_posible_moves(&temp, &m,1,0);


	for (int i = 0; i < m.counter; i++) {

		board->ply++;
		make_move(board,m.moves[i]);
		int score = -quiescence(hm, board, -beta, -alpha);
		//score -= m.value[i];
		//store_position(hm, temp, score);
		board->ply--;

		if (score >= beta) {
			store_position(hm, board, beta);
			return beta;
			}
		take_board();
		if (score > alpha) {
			alpha = score;

			}

		//copy_
		store_position(hm, board, alpha);
		//else
		return alpha;
		}
	return alpha;
	}

static int negamax(Hashmap hm, Board *__restrict__ board, int alpha, int beta, int depth) {
	board->ply = 0;
	Board temp;
	copy_board();




	if(depth == 0) {


		int is_store = 0;
		int sc = return_score(hm, board, &is_store);
		if(is_store == 1)
			return sc;


		//	int score = quiescence(hm, board, alpha, beta);
		//store_position(hm, *board, score);
		//int is_store = 0;
		//int sc = return_score(hm, temp, &is_store);
		//if(is_store == 1)
		//	return sc;
		//int score = evaluate(temp);
		//store_position(hm, *board, score);
		//int score = evaluate_nn(board);
		//return score;

		return quiescence(hm, board, alpha, beta);


		}


	int best_sofar = 0;
	int old_alpha = alpha;

	Moves m;
	generate_posible_moves(&temp, &m,1,1);



	for(int i = 0; i < m.counter; i++) {

		make_move(board, m.moves[i]);



		//if(PIECE(m.moves[i]) )
		int score;
		score = -negamax(hm, board, -beta, -alpha, depth - 1);
		//score += m.value[i];

		board->ply--;
		take_board();
		if (score >= beta) {
			store_position(hm, board, beta);
			return beta;
			}

		if(score > alpha) {
			// PV node (move)
			alpha = score;
			if (board->ply == 0)
				best_sofar = m.moves[i];
			}

		}
	if (old_alpha != alpha)
		board->best_move = best_sofar;

	store_position(hm, board, alpha);
	return alpha;


	}


int negamax_advanced(Hashmap hm, Board *board, int alpha, int beta, int depth) {
	board->ply = 0;



	if(depth == 0) {
		//return evaluate(hm, temp);

//		else

		int score = quiescence(hm, board, -beta, -alpha);
		//store_position(hm, *board, score);
		return score;
		//return quiescence(hm, board, -inf, inf);
		//return evaluate(board);
		}

	Board temp;
	copy_board();
	int best_sofar = 0;
	int old_alpha = alpha;

	Moves m;
	generate_posible_moves(&temp, &m,1,1);

	for(int i = 0; i < m.counter; i++) {
		make_move(board, m.moves[i]);
		int score;
		if(CAPTURE(m.moves[i]))
			score = -negamax(hm, board, -beta, -alpha, 2);
		else
			score = -negamax(hm, board, -beta, -alpha, 2);
		board->ply--;
		take_board();
		if (score >= beta) {
			//store_position(hm, *board, beta);
			return beta;
			}

		if(score > alpha) {
			// PV node (move)
			alpha = score;
			if (board->ply == 0)
				best_sofar = m.moves[i];
			}

		}
	if (old_alpha != alpha)
		board->best_move = best_sofar;


	return alpha;

	}






extern inline int search_position(Hashmap hm, Board *board,int depth) {
	// find best move within a given position
	//int range = negamax(hm, board, -inf, inf, 2);
	//int range = evaluate_nn(board);
	
	int score;
	score = negamax(hm, board, -inf, inf, depth);
	
	
//	/printf("Score is %d\n", score);
	return score;
	}

#endif

