#include<stdio.h>

#include "bitboard.h"
/*
	U64 a = 0;
	for(size_t y = 0; y < 8;y++){
		for(size_t x  = 0; x < 8;x++){
			if(y != 7)
				SET(a, (y*8 + x));
		}
	}
*/

#include<time.h>
// generating
int main() {
//	calculate_above();
	init_attack_table();
	if(init_masks() != TRAP_NONINIT) {

		}
	else return -1;

	//srand(time(0));
	//if(init_magic_numbers() == TRAP_MAGIC)
	//return -1;
	//print_magic();
	
	init_slider_attacks(bishop);
	init_slider_attacks(rook);
	init_utils();
	if(fen_loader(start_fen_full) == TRAP_FEN) {
		printf("FEN ERROR !!!\n");
		return -1;
		}

	
	side = black;
	//SET(position_white, f8);
	//SET(white_quean, d8);
	//SET(position_white, d8);
	print_board();
	generate_posible_moves();	
	
	return 0;
	}

