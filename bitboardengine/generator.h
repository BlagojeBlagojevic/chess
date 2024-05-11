#include "bitboard.h"

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
	size_t counter;

	} Moves;


// REPRESENTS BOARD STATE THER IS A 6 + 6 PIECES SO piece shoud have 12 bitboards witch represents state of the game
typedef struct {

	U64 piece[12];
	//MAYBE OTHER STATES
	} Board;

//INIT MAIN BOARD AS GENERATED FEN NOTATION IN PREVIOS PART OF THE ENGING
// P, N, B, R, Q, K, p, n, b, r, q, k
Trap init_board_state(Board *b) {

	b->piece[P] = white_pawn;
	b->piece[N] = white_knight;
	b->piece[R] = white_rook;
	b->piece[Q] = white_quean;
	b->piece[K] = white_king;
	b->piece[p] = black_pawn;
	b->piece[n] = black_knight;
	b->piece[r] = black_rook;
	b->piece[q] = black_quean;
	b->piece[k] = black_king;
	return TRAP_OK;

	};

Trap init_iternal_state(Board *b) {

	white_pawn   = b->piece[P];
	white_knight = b->piece[N];
	white_rook   = b->piece[R];
	white_quean  = b->piece[Q];
	white_king   = b->piece[K];
	black_pawn   = b->piece[p];
	black_knight = b->piece[n];
	black_rook   = b->piece[r];
	black_quean  = b->piece[q];
	black_king   = b->piece[k];
	return TRAP_OK;

	};



//MAYBE LIKE UCI
void print_move(int move) {

	int source_square = SOURCE(move);
	int target_square = TARGET(move);
	int piece = PIECE(move);
	int promoted_piece = PROMOTED(move);


	printf("source square: %s\n", squers_name[source_square]);
	printf("target square: %s\n", squers_name[target_square]);
	printf("capture flag: %d\n", CAPTURE(move) ? 1 : 0);
	printf("double pawn push flag: %d\n", DOUBLE(move) ? 1 : 0);
	printf("enpassant flag: %d\n", ENPESANT(move) ? 1 : 0);
	printf("castling flag: %d\n", CASTLING(move) ? 1 : 0);

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

static inline void generate_posible_moves(Board b, Moves *m) {

	static int target, source; // SQUER WITCH MOVE STARTS FROM AND WHER TO GO

	static U64 bitboard, attacks;

	//white pawn
	if(side == white) {

		bitboard = b.piece[P];
		while(bitboard) {
			//system("pause");
			source = LSB(bitboard);
			target = source - 8;   //ONE SQUARE FORWARD DIFERENCS IS 8
#if LOG_MOVES_PAWN
			//printf("source %s target %s\n",squers_name[source], squers_name[target]);
#endif
			//FORWARD MOVE
			//IF NOTING IS IN FORWARD SQUARE AND WE ARE NOT OUT OF BOARD
			if(!(target < 0)  && !GET((position_all), target)) {
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
					m->moves[m->counter++] = ENCODE(source, target,P, Q, 0, 0,0,0);
					m->moves[m->counter++] = ENCODE(source, target,P, R, 0, 0,0,0);
					m->moves[m->counter++] = ENCODE(source, target,P, N, 0, 0,0,0);
					m->moves[m->counter++] = ENCODE(source, target,P, B, 0, 0,0,0);
					}

				//ONE AND TWO FORWARD MOVES
				else {
					//CHECK ON TOP
#if LOG_MOVES_PAWN
					printf("white pawn moved to %s%s\n",squers_name[source], squers_name[target]);
#endif
					m->moves[m->counter++] = ENCODE(source, target,P,0,0,0,0,0);
					//CHECK IF TWO MOVES FORWARD IS POSIBLE
					if(source <= h2 && source >= a2 && (!GET((position_all), (target - 8)))){
					m->moves[m->counter++] = ENCODE(source, target+1,P,0,0,1,0,0);
#if LOG_MOVES_PAWN
					printf("white pawn moved 2 to %s%s\n",squers_name[source], squers_name[target - 8]);
#endif
						
					}

					}
				}
			// CAPTURES
			attacks  = white_pawn_attack_table[source] & position_black; // THIS IS CHECK IS THER A PIECE ON ATTACKED SQUERS
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
		
					}

				//ONE AND TWO FORWARD MOVES
				else {
					//CHECK ON TOP
#if LOG_MOVES_PAWN
					printf("white pawn capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					}
				POP(attacks, target);
				}

			//ENPESANT
			if(en_pesant != -1) {
				U64 en =  white_pawn_attack_table[source] & (1 << en_pesant);
				//print_bitboard(en);
				//system("pause");

				if(en) {
					int target_en = LSB(en);
#if LOG_MOVES_PAWN
					printf("white pawn capture_EN to %s%s\n",squers_name[source], squers_name[target_en]);
#endif
					}

				}
			POP(bitboard, source);
			}

		//white king

		bitboard = b.piece[K];
		source = LSB(bitboard);

		//CHECK IS CASTLING POSIBLE 0 2 K Q
		if(castle[0] && !GET(position_all, f1) && !GET(position_all, g1)) {
			//MAYBE CHECK IS CHECK BUT IF CHECK ONLY LEGAL MOVES ARE WITH KING
			if(check_is_square_attacked(black,f1) == 0 && check_is_square_attacked(black,g1) == 0) {
#if LOG_MOVES_KING
				printf("WHITE CASTLE KING\n");
#endif
				}
			}
		//QUEAN SIDE CASTLING
		if(castle[2] && !GET((position_all), d1)  && !GET(position_all, c1) && !GET(position_all, b1)) {
			if(check_is_square_attacked(black,d1) == 0 && check_is_square_attacked(black,c1) == 0
			    && check_is_square_attacked(black,b1) == 0) {
#if LOG_MOVES_KING
				printf("WHITE CASTLE QUEAN\n");
#endif
				}
			}

		//CHECK OTHER KING MOVES
		while(bitboard) {
			source = LSB(bitboard);
			//WHERE IS NO WHITE PIECE
			attacks = king_attack_table[source] & ~(position_white);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(position_black, target)) {  // NO
#if LOG_MOVES_KING
					printf("white king move to %s%s\n",squers_name[source], squers_name[target]);
#endif
					}

				else { //CAPTURE
#if LOG_MOVES_KING
					printf("white king capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					}

				POP(attacks,target);
				}

			POP(bitboard, source);
			}








		//white knight

		bitboard = b.piece[N];
		while(bitboard) {
			source = LSB(bitboard);
			//WHERE IS NO WHITE PIECE
			attacks = knight_attack_table[source] & ~(position_white);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(position_black, target)) {  // NO
#if LOG_MOVES_KNIGHT
					printf("white knight move to %s%s\n",squers_name[source], squers_name[target]);
#endif
					}

				else { //CAPTURE
#if LOG_MOVES_KNIGHT
					printf("white knight capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					}

				POP(attacks,target);
				}

			POP(bitboard, source);
			}


		//white bishop

		bitboard = b.piece[B];
		while(bitboard) {
			source = LSB(bitboard);
			//GET BISHOPS ATTACKS
			attacks = get_bishop_moves_magic(source, position_all) & ~(position_white);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(position_black, target)) {  // NO
#if LOG_MOVES_BISHOP
					printf("white bishop move to %s%s\n",squers_name[source], squers_name[target]);
#endif
					}

				else { //CAPTURE
#if LOG_MOVES_BISHOP
					printf("white bishop capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					}

				POP(attacks,target);
				}

			POP(bitboard, source);
			}




		//white rook

		bitboard = b.piece[R];
		while(bitboard) {
			source = LSB(bitboard);
			//GET ROOK ATTACKS
			attacks = get_rook_moves_magic(source, position_all) & ~(position_white);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(position_black, target)) {  // NO
#if LOG_MOVES_ROOK
					printf("white rook move to %s%s\n",squers_name[source], squers_name[target]);
#endif
					}

				else { //CAPTURE
#if LOG_MOVES_ROOK
					printf("white rook capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					}

				POP(attacks,target);
				}

			POP(bitboard, source);
			}




		//white quean

		bitboard = b.piece[Q];
		while(bitboard) {
			source = LSB(bitboard);
			//GET ROOK ATTACKS
			attacks = get_quean_moves_magic(source, position_all) & ~(position_white);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(position_black, target)) {  // NO
#if LOG_MOVES_QUEAN
					printf("white quean move to %s%s\n",squers_name[source], squers_name[target]);
#endif
					}

				else { //CAPTURE
#if LOG_MOVES_QUEAN
					printf("white quean capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					}

				POP(attacks,target);
				}

			POP(bitboard, source);
			}



		}

	//black pawn
	if(side == black) {

		bitboard = b.piece[p];
		while(bitboard) {

			source = LSB(bitboard);
			target = source + 8;   //ONE SQUARE FORWARD DIFERENCS IS 8
#if LOG_MOVES_PAWN
			//printf("source %s target %s\n",squers_name[source], squers_name[target]);
#endif
			//FORWARD MOVE
			//IF NOTING IS IN FORWARD SQUARE AND WE ARE NOT OUT OF BOARD
			if(!(target > 63)  && !GET((position_all), target)) {
				//printf("Nesto");

				// GENERATE PROMTION WE AS WHITE CAN PROMOTE PIECES IF THER ARE IN 7 RANK
				if(source <= h2 && source >= a2 ) {
#if LOG_MOVES_PAWN
					printf("black pawn promoted to q %s%s\n",squers_name[source], squers_name[target]);
					printf("black pawn promoted to n %s%s\n",squers_name[source], squers_name[target]);
					printf("black pawn promoted to r %s%s\n",squers_name[source], squers_name[target]);
					printf("white pawn promoted to b %s%s\n",squers_name[source], squers_name[target]);
#endif
					}

				//ONE AND TWO FORWARD MOVES
				else {
					//CHECK ON TOP
#if LOG_MOVES_PAWN
					printf("black pawn moved to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//CHECK IF TWO MOVES FORWARD IS POSIBLE
					if(source <= h7 && source >= a7 && (!GET((position_all), (target + 8))));
#if LOG_MOVES_PAWN
					printf("black pawn moved 2 to %s%s\n",squers_name[source], squers_name[target + 8]);
#endif
					}
				}
			// CAPTURES
			attacks  = black_pawn_attack_table[source] & position_white; // THIS IS CHECK IS THER A PIECE ON ATTACKED SQUERS
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
					}

				//ONE AND TWO FORWARD MOVES
				else {
					//CHECK ON TOP
#if LOG_MOVES_PAWN
					printf("black pawn capture to %s%s\n",squers_name[source], squers_name[target]);
#endif

					//ENPESANT
					}
				POP(attacks, target);
				}
			if(en_pesant != 0) {
				U64 en =  black_pawn_attack_table[source] & (1 << en_pesant);
				//print_bitboard(en);
				//system("pause");

				if(en) {
					int target_en = LSB(en);
#if LOG_MOVES_PAWN
					printf("black pawn capture_EN to %s%s\n",squers_name[source], squers_name[target_en]);
#endif
					}

				}

			POP(bitboard, source);
			}

		//black king

		bitboard = b.piece[k];

		source = LSB(bitboard);

		//CHECK IS CASTLING POSIBLE 1 3 k q
		if(castle[1] && !GET(position_all, f8) && !GET(position_all, g8)) {
			//MAYBE CHECK IS CHECK BUT IF CHECK ONLY LEGAL MOVES ARE WITH KING
			if(check_is_square_attacked(white,f8) == 0 && check_is_square_attacked(white,g8) == 0) {
#if LOG_MOVES_KING
				printf("BLACK CASTLE KING\n");
#endif
				}



			}
		//QUEAN SIDE CASTLING
		if(castle[3] && !GET((position_all), d8)  && !GET(position_all, c8) && !GET(position_all, b8)) {
			if(check_is_square_attacked(white,d8) == 0 && check_is_square_attacked(white,c8) == 0
			    && check_is_square_attacked(white,b8) == 0) {
#if LOG_MOVES_KING
				printf("BLACK CASTLE QUEAN\n");
#endif
				}
			}

		while(bitboard) {
			source = LSB(bitboard);
			//WHERE IS NO WHITE PIECE
			attacks = king_attack_table[source] & ~(position_black);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(position_white, target)) {  // NO
#if LOG_MOVES_KING
					printf("black king move to %s%s\n",squers_name[source], squers_name[target]);
#endif
					}

				else { //CAPTURE
#if LOG_MOVES_KING
					printf("black king capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					}

				POP(attacks,target);
				}

			POP(bitboard, source);
			}




		//black knight

		bitboard = b.piece[n];

		while(bitboard) {
			source = LSB(bitboard);
			//WHERE IS NO WHITE PIECE
			attacks = knight_attack_table[source] & ~(position_black);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(position_white, target)) {  // NO
#if LOG_MOVES_KNIGHT
					printf("black knight move to %s%s\n",squers_name[source], squers_name[target]);
#endif
					}

				else { //CAPTURE
#if LOG_MOVES_KNIGHT
					printf("black knight capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					}

				POP(attacks,target);
				}

			POP(bitboard, source);
			}





		//black bishop

		bitboard = black_bishop;
		while(bitboard) {
			source = LSB(bitboard);
			//GET BISHOPS ATTACKS
			attacks = get_bishop_moves_magic(source, position_all) & ~(position_black);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(position_white, target)) {  // NO
#if LOG_MOVES_BISHOP
					printf("black bishop move to %s%s\n",squers_name[source], squers_name[target]);
#endif
					}

				else { //CAPTURE
#if LOG_MOVES_BISHOP
					printf("black bishop capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					}

				POP(attacks,target);
				}

			POP(bitboard, source);
			}



		//black rook

		bitboard = b.piece[r];
		while(bitboard) {
			source = LSB(bitboard);
			//GET ROOK ATTACKS
			attacks = get_rook_moves_magic(source, position_all) & ~(position_black);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(position_white, target)) {  // NO
#if LOG_MOVES_ROOK
					printf("black rook move to %s%s\n",squers_name[source], squers_name[target]);
#endif
					}

				else { //CAPTURE
#if LOG_MOVES_ROOK
					printf("black rook capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					}

				POP(attacks,target);
				}

			POP(bitboard, source);
			}



		//black quean

		bitboard = b.piece[q];
		while(bitboard) {
			source = LSB(bitboard);
			//GET ROOK ATTACKS
			attacks = get_quean_moves_magic(source, position_all) & ~(position_black);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(position_white, target)) {  // NO
#if LOG_MOVES_QUEAN
					printf("black quean move to %s%s\n",squers_name[source], squers_name[target]);
#endif
					}

				else { //CAPTURE
#if LOG_MOVES_QUEAN
					printf("black quean capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					}

				POP(attacks,target);
				}

			POP(bitboard, source);
			}
		}
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





