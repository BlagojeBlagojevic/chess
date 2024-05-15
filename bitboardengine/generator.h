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

static inline void generate_posible_moves(Board bo, Moves *m) {

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
					if(source <= h2 && source >= a2 && (!GET((bo.position_alll), (target - 8)))) {
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
					m->moves[m->counter++] = ENCODE(source, target,P, Q, 1, 0,0,0);
					m->moves[m->counter++] = ENCODE(source, target,P, R, 1, 0,0,0);
					m->moves[m->counter++] = ENCODE(source, target,P, N, 1, 0,0,0);
					m->moves[m->counter++] = ENCODE(source, target,P, B, 1, 0,0,0);


					}

				//ONE AND TWO FORWARD MOVES
				else {
					//CHECK ON TOP
#if LOG_MOVES_PAWN
					printf("white pawn capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
//        ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
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
					m->moves[m->counter++] = ENCODE(source, target_en,P, 0, 1, 0, 1, 0);

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
				m->moves[m->counter++] = ENCODE(source, g1,K, 0, 0, 0,0,1);

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
					m->moves[m->counter++] = ENCODE(source, target,K, 0, 0, 0, 0, 0);

					}

				else { //CAPTURE
#if LOG_MOVES_KING
					printf("white king capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
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
					m->moves[m->counter++] = ENCODE(source, target, N, 0, 0, 0, 0, 0);

					}

				else { //CAPTURE
#if LOG_MOVES_KNIGHT
					printf("white knight capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
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
					m->moves[m->counter++] = ENCODE(source, target, B, 0, 0, 0, 0, 0);
					}

				else { //CAPTURE
#if LOG_MOVES_BISHOP
					printf("white bishop capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
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
					m->moves[m->counter++] = ENCODE(source, target, R, 0, 0, 0, 0, 0);
					}

				else { //CAPTURE
#if LOG_MOVES_ROOK
					printf("white rook capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
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
					m->moves[m->counter++] = ENCODE(source, target, Q, 0, 0, 0, 0, 0);
					}

				else { //CAPTURE
#if LOG_MOVES_QUEAN
					printf("white quean capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
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
					m->moves[m->counter++] = ENCODE(source, target, p, q, 0, 0, 0, 0);
					m->moves[m->counter++] = ENCODE(source, target, p, n, 0, 0, 0, 0);
					m->moves[m->counter++] = ENCODE(source, target, p, r, 0, 0, 0, 0);
					m->moves[m->counter++] = ENCODE(source, target, p, b, 0, 0, 0, 0);

					}

				//ONE AND TWO FORWARD MOVES
				else {
					//CHECK ON TOP
#if LOG_MOVES_PAWN
					printf("black pawn moved to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					m->moves[m->counter++] = ENCODE(source, target, p, 0, 0, 0, 0, 0);
					//CHECK IF TWO MOVES FORWARD IS POSIBLE
					if(source <= h7 && source >= a7 && (!GET((bo.position_alll), (target + 8)))) {
#if LOG_MOVES_PAWN
						printf("black pawn moved 2 to %s%s\n",squers_name[source], squers_name[target + 8]);
#endif
						//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
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
					m->moves[m->counter++] = ENCODE(source, target, p, q, 1, 0, 0, 0);
					m->moves[m->counter++] = ENCODE(source, target, p, n, 1, 0, 0, 0);
					m->moves[m->counter++] = ENCODE(source, target, p, r, 1, 0, 0, 0);
					m->moves[m->counter++] = ENCODE(source, target, p, b, 1, 0, 0, 0);
					}

				//ONE AND TWO FORWARD MOVES
				else {
					//CHECK ON TOP
#if LOG_MOVES_PAWN
					printf("black pawn capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
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
					m->moves[m->counter++] = ENCODE(source, target, k, 0, 0, 0, 0, 0);
					}

				else { //CAPTURE
#if LOG_MOVES_KING
					printf("black king capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
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
					m->moves[m->counter++] = ENCODE(source, target, n, 0, 0, 0, 0, 0);
					}

				else { //CAPTURE
#if LOG_MOVES_KNIGHT
					printf("black knight capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
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
					m->moves[m->counter++] = ENCODE(source, target, b, 0, 0, 0, 0, 0);
					}

				else { //CAPTURE
#if LOG_MOVES_BISHOP
					printf("black bishop capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					//b is alredy declared so bo
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
					m->moves[m->counter++] = ENCODE(source, target, r, 0, 0, 0, 0, 0);
					}

				else { //CAPTURE
#if LOG_MOVES_ROOK
					printf("black rook capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
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
					m->moves[m->counter++] = ENCODE(source, target, q, 0, 0, 0, 0, 0);
					}

				else { //CAPTURE
#if LOG_MOVES_QUEAN
					printf("black quean capture to %s%s\n",squers_name[source], squers_name[target]);
#endif
					//ENCODE(source, target, piece, promoted, capture, double, enpassant, castling)
					m->moves[m->counter++] = ENCODE(source, target, q, 0, 1, 0, 0, 0);
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


//SORT BEST MOVES 


static inline sort_moves(Moves *m){
	
	
	
	
}





#define LOG_MOVES 0
// FUNCTION USED TO GENARTES MOVE AND RETURN IT WE ACCEPT BOARD STRUCTURE AS INPUT
int make_move(Board *board, int move) {
	static Board temp;// = &board;
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
		static int start_piece, end_piece;   // we will loop over this pieces

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
				POP(board->piece[r], h1);
				SET(board->piece[r], d1);
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
	//if(!board->side == white && (check_is_square_attacked_board(!board->side, LSB(board->piece[K]), &board))) {
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
const float piece_value[] =  {1.0f, 3.1f, 3.3f, 5.0f, 10.0f, 10000.0f,
                              1.0f, 3.1f, 3.3f, 5.0f, 10.0f, 10000.0f
                             };

#define LOG_EVALUATION 0

#define inf 1000000.0f

__attribute__((always_inline))
static inline float evaluation(Board board) {

	float score = 0;
	//int num_pieces[12] = {0};
	for(int i = P; i <= K; i++) {
		score+=((float)NUM(board.piece[i]) * piece_value[i]);
		}
	for(int i = p; i <= k; i++) {
		score -= ((float)NUM(board.piece[i]) * piece_value[i] );
		}

//	if(board.piece[K] == 0)
//		score = 100000;
//	if(board.piece[k] == 0)
//		score = -100000;


	// WE WILL TAKE INTO  A CONSIDORATITION THAT WHITE WANTS TO MAX SCORE AND BLACK TO MIN
#if LOG_EVALUATION
	printf("Board Evaluation %f\n\n",score);
	//system("pause");
#endif
	float v = 2.0f * (float)rand() / (float)RAND_MAX - 1;
	//printf("v %f", v);
	//system("pause");
	//printf("score %f\n", score);
	return score + v;


	//if(board.side == white)
		//return -fabs(score + v);
	//else
		//return -1*fabs(score + v);

	}





static inline float  mini_max(Board board, int depth, int side) {

	Moves m;
	m.counter = 0;
	Board temp;
	memcpy(&temp, &board, sizeof(Board));
	generate_posible_moves(board, &m);
	if (depth == 0) return evaluation(board);

	int maxa = -inf;
	for (int i = 0; i < m.counter; i++)  {
		make_move(&board, m.moves[i]);
		float score = -1 * mini_max(board,depth - 1,board.side);
		memcpy(&board, &temp,sizeof(Board));
		if(score > maxa)
			maxa = score;
		}
	return maxa;

	}

__attribute__((always_inline))
static inline float max(float maxEval, float eval) {

	if(eval > maxEval)
		return eval;

	return maxEval;
	}

__attribute__((always_inline))
static inline float min(float minEval,float eval) {

	if(eval < minEval)
		return eval;

	return minEval;
	}

//__attribute__((always_inline))
static inline float  mini_max_alfa_beta(Board board, int depth,float alfa, float beta, int side) {

	
	
	//print_move_list(&m);
	//system("pause");

	if (depth == 0)
		return evaluation(board);
		
		

	Moves m;
	Board temp;
	generate_posible_moves(board, &m);
	memcpy(&temp, &board, sizeof(Board));

	if (side == white) {
		float maxEval = -inf;
		for (size_t i = 0; i < m.counter ; i++) {
			make_move(&board,m.moves[i]);
			float eval = mini_max_alfa_beta(board, depth - 1, alfa, beta,black);
			memcpy(&board, &temp, sizeof(Board));
			maxEval = max(maxEval, eval);
			alfa = max(alfa, eval);
			if (beta <= alfa)
				break;
				
			
			}
		return maxEval;
		}


	else {
		float minEval = inf;
		for (size_t i = 0; i < m.counter; i++) {
			make_move(&board,m.moves[i]);
			float eval = mini_max_alfa_beta(board, depth - 1, alfa, beta, white);
			memcpy(&board, &temp, sizeof(Board));
			minEval = min(minEval, eval);
			beta = min(beta, eval);
			if (beta <= alfa)
				break;
				
			
			}

		return minEval;
		}

	}


//DECLARING FUNCTIONS
static inline float mini(Board board, int depth,float alfa, float beta);
static inline float maxi(Board board, int depth,float alfa, float beta);

//__attribute__((always_inline))
static inline float maxi(Board board, int depth,float alfa, float beta){

	if (depth == 0)
		return evaluation(board);


		
	Moves m;
	//m.counter = 0;
	Board temp;
	
	generate_posible_moves(board, &m);
	memcpy(&temp, &board, sizeof(Board));
	float eval;
	
		float maxEval = -inf;
		for (size_t i = 0; i < m.counter ; i++) {
			make_move(&board,m.moves[i]);
			eval = mini(board, depth - 1, alfa, beta);
			memcpy(&board, &temp, sizeof(Board));
			maxEval = max(maxEval, eval);
			alfa = max(alfa, eval);
			if (beta <= alfa)
				break;
				
			
			}
		return maxEval;
	
}
//__attribute__((always_inline))
static inline float mini(Board board, int depth,float alfa, float beta){


	if (depth == 0)
		return evaluation(board);

		
	Moves m;
	Board temp;
	generate_posible_moves(board, &m);
	memcpy(&temp, &board, sizeof(Board));
	float eval;
		
		float minEval = inf;
		for (size_t i = 0; i < m.counter; i++) {
			make_move(&board,m.moves[i]);
			eval = maxi(board, depth - 1, alfa, beta);
			memcpy(&board, &temp, sizeof(Board));
			minEval = min(minEval, eval);
			beta = min(beta, eval);
			if (beta <= alfa)
				break;	
			
			}

		return minEval;

}



#define de 0

static inline int get_index_of_best_move(Board board, Moves m) {
	float score_white = -inf, score_black = inf;
	int index = 0;
	Board temp;
	float score = 0.0f;
	memcpy(&temp, &board, sizeof(Board));
	//printf("Counter %d",m.counter);
	//system("pause");

	if(board.side == white) {
		for(size_t i = 0; i < m.counter; i++) {

			make_move(&board,m.moves[i]);

			//float score = mini_max(board, 4, white);
			score = mini_max_alfa_beta(board, 4,-inf, inf,black);
			//score = maxi(board, 4,-inf, inf);
			memcpy(&board,&temp,sizeof(Board));
			//float score = mini_(board, 4, white);
#if de
			printf("White %f ", score);
			system("pause");
#endif
		
			if(score > score_white) {
				score_white  = score ;
				index = i;
#if de
				printf("White Change %f");
				system("pause");
#endif
				}
			}
		}

	else {
		for(size_t i = 0; i < m.counter; i++) {
			make_move(&board,m.moves[i]);
			//float score = mini_max(board, 3, black);
			score = mini_max_alfa_beta(board, 4,-inf, inf, white);
			//score = mini(board, 4,-inf, inf);
			memcpy(&board,&temp,sizeof(Board));
#if de
			printf("Black %f", score);
			system("pause");
#endif
			//printf("")
			if(score < score_black) {
				score_black = score;
				index = i;
#if de
				printf("%d\n", score);
				printf("Black Change");
				system("pause");
#endif
				}
			}
		}
	printf("Board Evaluation white %f black %f\n\n",score_white, score_black);
	return index;

	}
