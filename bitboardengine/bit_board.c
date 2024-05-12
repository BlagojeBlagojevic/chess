#include<stdio.h>

#include "generator.h"
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
	static Board board;
	static Moves m;
	m.counter = 0;
	while(1){
		print_board();
		system("pause");
		init_board_state(&board);
		generate_posible_moves(board, &m);
		while(1){
			int random = rand()%(m.counter - 1);
			Trap state = make_move(&board, m.moves[random]);
			if(state == TRAP_MOVE_OK)
				break;
				//printf("Nestoasdasdasdasdasdaf");
			
		}
		init_iternal_state(&board);
		
		if(board.piece[k] == 0 || board.piece[K] == 0)
			break;
		
	}
	return 0;
	}

