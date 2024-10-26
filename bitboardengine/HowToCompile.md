## COMPILER FLAGS 
To compile pass this flags to compiler: 
```c

gcc -O2  -lSDL2main -lSDL2   -lSDL2_image -Wall -Wextra  -Wno-format nnue_eval.c ./nnue/nnue.cpp ./nnue/misc.cpp -o main.exe  -DUSE_SSE41 -msse4.1 -DUSE_SSSE3 -mssse3 -DUSE_SSE2 -msse2 -DUSE_SSE -msse

```
There is a makefile if your system suport it.
