#include "bitboard.h"
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
	size_t counter;

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
	int piece = PIECE(move);
	int promoted_piece = PROMOTED(move);


	printf("source square: %s\n", squers_name[source_square]);
	printf("target square: %s\n", squers_name[target_square]);
	printf("capture flag: %d\n", CAPTURE(move) ? 1 : 0);
	printf("double pawn push flag: %d\n", DOUBLE(move) ? 1 : 0);
	printf("enpassant flag: %d\n", ENPESANT(move) ? 1 : 0);
	printf("castling flag: %d\n", CASTLING(move) ? 1 : 0);

	}

//black,c1, &bo
static inline int check_is_square_attacked_board(int side, int square, Board *bo) {

	U64 white_pawna     = bo->piece[P];
	U64 white_knighta   = bo->piece[N];
	U64 white_bishopa   = bo->piece[B];
	U64 white_rooka     = bo->piece[R];
	U64 white_queana    = bo->piece[Q];
	U64 white_kinga     = bo->piece[K];
	U64 black_pawna     = bo->piece[p];
	U64 black_knighta   = bo->piece[n];
	U64 black_bishopa   = bo->piece[b];
	U64 black_rooka     = bo->piece[r];
	U64 black_queana    = bo->piece[q];
	U64 black_kinga     = bo->piece[k];
	U64 position_whitea = bo->position_white;
	U64 position_blacka = bo->position_black;
	U64 position_alll   = bo->position_white & bo->position_black;
	U64 en_pesanta      = bo->enpesant;
	//int side            = bo->side;
	//PROBOBLY NO THIS
	//if(square > 63 && square < 0) {
	//printf("OVERFLOW!!!\n");
	//return TRAP_OVERFLOW;
	//}



	if((side == white) && (black_pawn_attack_table[square] & white_pawna)) return 1;

	if((side == black) && (white_pawn_attack_table[square] & black_pawna)) return 1;

	if (knight_attack_table[square] & ((side == white) ? white_knighta : black_knighta)) return 1;

	if(get_bishop_moves_magic(square, position_alll) & ((side == white) ? white_bishopa : black_bishopa)) return 1;

	if(get_rook_moves_magic(square, position_alll) & ((side == white) ? white_rooka : black_rooka)) return 1;

	if(get_quean_moves_magic(square, position_alll) & ((side == white) ? white_queana : black_queana)) return 1;

	if(king_attack_table[square] & ((side == white) ? white_kinga : black_kinga)) return 1;

	return 0;
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

static inline void generate_posible_moves(Board bo, Moves *m, int is_capture, int is_quiet) {

	static int target, source; // SQUER WITCH MOVE STARTS FROM AND WHER TO GO

	static U64 bitboard, attacks;
	m->counter = 0;                //RESET COUNTER
	//white pawn
	if(bo.side == white) {

		bitboard = bo.piece[P];
		while(bitboard) {
			//system("pause");
			source = LSB(bitboard);
			target = source - 8;   //ONE SQUARE FORWARD DIFERENCS IS 8
#if LOG_MOVES_PAWN
			print_board();
#endif
			//FORWARD MOVE
			//IF NOTING IS IN FORWARD SQUARE AND WE ARE NOT OUT OF BOARD
			if(!(target < 0)  && !GET((bo.position_alll), target)) {
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
					if(source <= h2 && source >= a2 && (!GET((bo.position_alll), (target - 8)))) {
						if(is_quiet)
							m->moves[m->counter++] = ENCODE(source, (target-8),P,0,0,1,0,0);
#if LOG_MOVES_PAWN
						printf("white pawn moved 2 to %s%s\n",squers_name[source], squers_name[target - 8]);
#endif

						}

					}
				}
			// CAPTURES
			attacks  = white_pawn_attack_table[source] & bo.position_black; // THIS IS CHECK IS THER A PIECE ON ATTACKED SQUERS
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
			if(bo.enpesant != -1) {
				U64 en =  white_pawn_attack_table[source] & (1 << bo.enpesant);
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

		bitboard = bo.piece[K];
		source = LSB(bitboard);

		//CHECK IS CASTLING POSIBLE 0 2 K Q
		if(castle[0] && !GET(bo.position_alll, f1) && !GET(bo.position_alll, g1)) {
			//MAYBE CHECK IS CHECK BUT IF CHECK ONLY LEGAL MOVES ARE WITH KING
			if(check_is_square_attacked_board(black,f1, &bo) == 0 && check_is_square_attacked_board(black, g1, &bo) == 0) {
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
		if(castle[2] && !GET((bo.position_alll), d1)
		    && !GET(bo.position_alll, c1) && !GET(bo.position_alll, b1)) {
			if(check_is_square_attacked_board(black,d1, &bo) == 0
			    && check_is_square_attacked_board(black,c1, &bo) == 0
			    && check_is_square_attacked_board(black, b1, &bo) == 0) {
#if LOG_MOVES_KING
				printf("WHITE CASTLE QUEAN\n");
#endif
				//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
				if(is_quiet)
					m->moves[m->counter++] = ENCODE(source, b1,K, 0, 0, 0,0,1);

				}
			}

		//CHECK OTHER KING MOVES
		while(bitboard) {
			source = LSB(bitboard);
			//WHERE IS NO WHITE PIECE
			attacks = king_attack_table[source] & ~(bo.position_white);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(bo.position_black, target)) {  // NO
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

		bitboard = bo.piece[N];
		while(bitboard) {
			source = LSB(bitboard);
			//WHERE IS NO WHITE PIECE
			attacks = knight_attack_table[source] & ~(bo.position_white);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(bo.position_black, target)) {  // NO
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

		bitboard = bo.piece[B];
		while(bitboard) {
			source = LSB(bitboard);
			//GET BISHOPS ATTACKS
			attacks = get_bishop_moves_magic(source, bo.position_alll) & ~(bo.position_white);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(bo.position_black, target)) {  // NO
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

		bitboard = bo.piece[R];
		while(bitboard) {
			source = LSB(bitboard);
			//GET ROOK ATTACKS
			attacks = get_rook_moves_magic(source, bo.position_alll) & ~(bo.position_white);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(bo.position_black, target)) {  // NO
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

		bitboard = bo.piece[Q];
		while(bitboard) {
			source = LSB(bitboard);
			//GET ROOK ATTACKS
			attacks = get_quean_moves_magic(source, bo.position_alll) & ~(bo.position_white);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(bo.position_black, target)) {  // NO
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

	//black pawn
	if(bo.side == black) {

		bitboard = bo.piece[p];
		while(bitboard) {

			source = LSB(bitboard);
			target = source + 8;   //ONE SQUARE FORWARD DIFERENCS IS 8
#if LOG_MOVES_PAWN
			//print_board();
#endif
			//FORWARD MOVE
			//IF NOTING IS IN FORWARD SQUARE AND WE ARE NOT OUT OF BOARD
			if(!(target >= 63)  && !GET((bo.position_alll), target)) {
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
					if(source <= h7 && source >= a7 && (!GET((bo.position_alll), (target + 8)))) {
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
			attacks  = black_pawn_attack_table[source] & bo.position_white; // THIS IS CHECK IS THER A PIECE ON ATTACKED SQUERS

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
			if(bo.enpesant != -1) {
				U64 en =  black_pawn_attack_table[source] & (1 << bo.enpesant);
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

		bitboard = bo.piece[k];

		source = LSB(bitboard);

		//CHECK IS CASTLING POSIBLE 1 3 k q
		if(castle[1] && !GET(bo.position_alll, f8) && !GET(bo.position_alll, g8)) {
			//MAYBE CHECK IS CHECK BUT IF CHECK ONLY LEGAL MOVES ARE WITH KING
			if(check_is_square_attacked_board(white,f8, &bo) == 0 && check_is_square_attacked_board(white,g8, &bo) == 0) {
#if LOG_MOVES_KING
				printf("BLACK CASTLE KING\n");
#endif
				//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
				if(is_quiet)
					m->moves[m->counter++] = ENCODE(source, g8, k, 0, 0, 0, 0, 1);
				}



			}
		//QUEAN SIDE CASTLING
		if(castle[3] && !GET((bo.position_alll), d8)
		    && !GET(bo.position_alll, c8) && !GET(bo.position_alll, b8)) {
			if(check_is_square_attacked_board(white,d8, &bo) == 0 && check_is_square_attacked_board(white,c8, &bo) == 0
			    && check_is_square_attacked_board(white,b8, &bo) == 0) { //MAYBE NO B8
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
			attacks = king_attack_table[source] & ~(bo.position_black);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(bo.position_white, target)) {  // NO
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

		bitboard = bo.piece[n];

		while(bitboard) {
			source = LSB(bitboard);
			//WHERE IS NO WHITE PIECE
			attacks = knight_attack_table[source] & ~(bo.position_black);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(bo.position_white, target)) {  // NO
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

		bitboard = bo.piece[b];
		while(bitboard) {
			source = LSB(bitboard);
			//GET BISHOPS ATTACKS
			attacks = get_bishop_moves_magic(source, bo.position_alll) & ~(bo.position_black);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(bo.position_white, target)) {  // NO
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

		bitboard = bo.piece[r];
		while(bitboard) {
			source = LSB(bitboard);
			//GET ROOK ATTACKS
			attacks = get_rook_moves_magic(source, bo.position_alll) & ~(bo.position_black);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(bo.position_white, target)) {  // NO
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

		bitboard = bo.piece[q];
		while(bitboard) {
			source = LSB(bitboard);
			//GET ROOK ATTACKS
			attacks = get_quean_moves_magic(source, bo.position_alll) & ~(bo.position_black);
			//print_bitboard(attacks);
			while(attacks) {

				target = LSB(attacks);
				//DISTINGUISH BEATWEN CAPTURE AND NO
				if(!GET(bo.position_white, target)) {  // NO
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
/*
	for(int i = 0; i < m->counter; i++) {
		//IF IS CAPTURE FIRST
		if(CAPTURE(m->moves[i])) {
			int temp = m->moves[i];
			m->moves[i] = m->moves[0];
			m->moves[0] = temp;
			}
		// IF PIECE IS CAPTURED LAST

		if(check_is_square_attacked_board(bo.side,TARGET(m->moves[i]),&bo)
		    && (PIECE(m->moves[i]) == r ||  PIECE(m->moves[i]) == R
		        ||  PIECE(m->moves[i]) == Q ||  PIECE(m->moves[i]) == q )) {
			int temp = m->moves[m->counter - 1];
			m->moves[i] = m->moves[m->counter - 1];
			m->moves[m->counter - 1] = temp;

			}
		}
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


static inline sort_moves(Moves *m) {




	}





#define LOG_MOVES 0
// FUNCTION USED TO GENARTES MOVE AND RETURN IT WE ACCEPT BOARD STRUCTURE AS INPUT
static inline int make_move(Board *board, int move) {
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
				POP(board->piece[r], h8);
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

	if(!GET(board->piece[R], h1))
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


	int isincheck = check_is_square_attacked_board(board->side,sq, board);
	//if(isincheck == 1 && 0) {

	//printf("Is in Check %d!!!\n", isincheck);
	//printf("squere %s\n", squers_name[sq]);
	//print_board();
	//memcpy(board, &temp,sizeof(Board));
	//system("pause");
	//board = &temp;

	//return TRAP_ILEGAL;
	//}

	return TRAP_MOVE_OK;
	}
//enum { P, N, B, R, Q, K, p, n,  r, b, q, k };
const int piece_value[] =  {100, 300, 300, 500, 1000, 10000,
                            100, 300, 300, 500, 1000, 10000
                           };

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



__attribute__((always_inline))
static inline int max(int maxEval, int eval) {

	if(eval > maxEval)
		return eval;

	return maxEval;
	}

__attribute__((always_inline))
static inline int min(int minEval,int eval) {

	if(eval < minEval)
		return eval;

	return minEval;
	}

//
//MAKE HASH MAP STRUCTURE WITCH WILL STORE PREVIUSLY SEARCHED BOARDS
//IT WILL HAVE 100MB OF MEMORY(SIZE) AND USE ZOBRIST HASH FOR ACCESING BOARD VALUE

#define HASHSIZE 107374182
//#define HASHSIZE 10737418
//4157458668

typedef struct {

	int *score;
	U64 *zob;

	} Hashmap;


U64 zob_table[64][12];

void init_hashmap(Hashmap *m) {

	m->score = (int*)calloc(HASHSIZE,sizeof(int));
	m->zob = (U64*)calloc(HASHSIZE,sizeof(U64));
	for(size_t j = 0; j < 12; j++)
		for(size_t i = 0; i < 64; i++) {
			zob_table[i][j] = rand64();
			printf("%lu\n" , zob_table[i][j]);
			}
	}

__attribute__((always_inline))
static inline  U64 hash(Board b) {
	U64 key = 0;
	for(int i = P; i <= k ; i++) {
		U64 bitboard = b.piece[i];

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
__attribute__((always_inline))	
static inline void store_position(Hashmap m,Board b, int score) {

	U64 i = hash(b);
	m.zob[i%HASHSIZE] = i;
	m.score[i%HASHSIZE] = score;
	}
__attribute__((always_inline))
static inline int return_score(Hashmap m, Board b, int *is_store) {
	U64 a = hash(b);
	if(a == m.zob[a%HASHSIZE]) {
		*is_store = 1;
		}
	else {
		*is_store = 0;
		}

	return m.score[a%HASHSIZE];
	}


//NEW
//VALUE OF PIECES
const int evaluation_piece[] = {100,  300,  300,  500,  1000,  1000000,
                                -100, -300, -300, -500, -1000, -1000000,
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
	0,   0,   0,  20,  20,   0,   0,   0

	};

// king positional score
const int king_score[64] = {
	0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   5,   5,   5,   5,   0,   0,
	0,   5,   5,  10,  10,   5,   5,   0,
	0,   5,  10,  20,  20,  10,   5,   0,
	0,   5,  10,  20,  20,  10,   5,   0,
	0,   0,   5,  10,  10,   5,   0,   0,
	0,   5,   5,  -5,  -5,   0,   5,   0,
	0,   0,   20,   0, -15,   0,  30,   0
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

__attribute__((always_inline))
static inline int evaluate( Board board) {

	int piece, square;
	int score = 0;
	for(int i = P; i <= k; i++) {
		U64 bitboard =  board.piece[i];
		while(bitboard) {
			square = LSB(bitboard);
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
					score+=(rook_score[square] + bishop_score[square]);
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
					score-=(rook_score[mirror_score[square]] + bishop_score[mirror_score[square]]);
					break;
				case k:
					score-=king_score[mirror_score[square]];
					break;

				}

			POP(bitboard, square);
			}


		}
	if((board.side == white) && (board.piece[K] == 0))
		score-=100000;

	if((board.side == black) && (board.piece[k] == 0))
		score+=100000;


	//store_position(hm, board, (board.side == white) ? score : -score);
	return (board.side == white) ? score : -score;

	}

//TEMP MUST BE DECLARED
#define copy_board() memcpy(&temp,  board, sizeof(Board))
#define take_board() memcpy(board, &temp, sizeof(Board))



static inline int quiescence(Hashmap hm, Board *board, int alpha, int beta) {

	Board temp;
	Moves m;
	copy_board();

	int is_store;
	int sc = return_score(hm, temp, &is_store);
	if(is_store == 1)
		return sc;

	int evaluation = evaluate(temp);
	if (evaluation >= beta) {
		store_position(hm, temp, beta);
		return beta;
		}

	if (evaluation > alpha) {
		alpha = evaluation;
		}

	generate_posible_moves(temp, &m,1,0);

	
	for (int i = 0; i < m.counter; i++) {

		board->ply++;
		make_move(board,m.moves[i]);
		int score = -quiescence(hm, board, -beta, -alpha);
		board->ply--;
		
		if (score >= beta) {
			store_position(hm, temp, beta);
			return beta;
			}
		take_board();
		if (score > alpha) {
			alpha = score;

			}
		}
	//copy_
	//store_position(hm, *board, alpha);
	return alpha;
	}














static inline int negamax(Hashmap hm, Board *board, int alpha, int beta, int depth) {
	board->ply = 0;
	

	if(depth == 0) {
		//return evaluate(hm, temp);
		//int is_store;
		//int sc = return_score(hm, temp, &is_store);
		//if(is_store == 1)
	//		return sc;
//		else

			int score = quiescence(hm, board, alpha, beta);
			store_position(hm, *board, score);
			return score;
			//return quiescence(hm, board, -inf, inf);
			//return evaluate(board);
		}

	Board temp;
	copy_board();
	int best_sofar = 0;
	int old_alpha = alpha;

	Moves m;
	generate_posible_moves(temp, &m,1,1);

	for(size_t i = 0; i < m.counter; i++) {

		make_move(board, m.moves[i]);

		int score = -negamax(hm, board, -beta, -alpha, depth - 1);
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




static inline void search_position(Hashmap hm, Board *board,int depth) {
	// find best move within a given position
	//int score = negamax(hm, board, -inf, inf, depth);
	int score = negamax(hm, board, -inf, inf, depth);
	//for(int i = 3; i <= depth; i++ ){
//			score = negamax(hm, board, score, inf, i);
	printf("score is %d\n", score);
//	}

	}









