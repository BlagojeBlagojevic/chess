LIBS = -lSDL2 -lSDL2_image 
CFLAGS = -Wall -Wextra -Wno-format -march=native
all:
	gcc -Ofast main.c nnue_eval.c ./nnue/nnue.cpp ./nnue/misc.cpp -o chess $(LIBS) $(CFLAGS)
	#x86_64-w64-mingw32-gcc -Ofast main.c -o chess.exe


