#include<stdint.h>
#include <string.h>

//MACRO USED FOR ARRAY SIZE
#define SIZE(x) sizeof(x) / sizeof(x[0])




typedef uint64_t U64;
typedef uint32_t U32;
enum {bishop, rook, knight, king, quean, pawn};        // REPRESENT PIECES
enum {white, black};  														// REPRESENT PIECES   COLORS
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
//GET NUMBER OF BITS IN BITBOARD
__attribute__((always_inline))
static inline int NUM(U64 bitboard) {

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
__attribute__((always_inline))
static inline int LSB(U64 bitboard) {
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
	else{
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
__attribute__((always_inline))
static inline U64 get_bishop_moves(int squere, U64 pieces) {

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
__attribute__((always_inline))
static inline U64 get_rook_moves(int squere, U64 pieces) {

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
__attribute__((always_inline))
static inline U64 get_quean_moves(int squere, U64 pieces) {

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
__attribute__((always_inline))
static inline U64 occupancy(int index, int bit_in_mask, U64 piece_attack_table) {

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
__attribute__((always_inline))
static inline U32 rand32() {

	U32 y  = rand() & 0xff;
	y |= (y & 0xFF) << 8;
	y |= (y & 0xFF) << 16;
	y |= (y & 0xFF) << 24;
	return y;

	}
__attribute__((always_inline))
static inline U64 rand64() {
	U64 a = rand32();
	U64 b = a << 32;
	a = rand();
	b |= a;
	return b;
	}

// MAYBE MACRO
static inline U64 magic_candidate() {

	return rand64() & rand64() & rand64();

	}

//MAGIC NUMBER INIT


__attribute__((always_inline))
U64 find_magic_number(int square, int relevant_bits, int what_piece) {
	// init occupancies
	U64 occupancies[4096];

	// init attack tables
	U64 attacks[4096];

	// init used attacks
	U64 used_attacks[4096];

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

static U64 rook_magic_numbers[64] = {

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
static U64 bishop_magic_numbers[64] = {

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




Trap init_magic_numbers() {
	for (int square = 0; square < 64; square++) {
		if((rook_magic_numbers[square] = find_magic_number(square, rook_relevant[square], rook)) == TRAP_MAGIC)
			return TRAP_MAGIC;
		}




	for (int square = 0; square < 64; square++) {

		if((bishop_magic_numbers[square] = find_magic_number(square, bishop_relevant[square], bishop)) == TRAP_MAGIC) {
			return TRAP_MAGIC;
			}
		}

	return TRAP_OK;

	}

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
__attribute__((always_inline))
static inline U64 get_bishop_moves_magic(int square, U64 occupancy) {
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

