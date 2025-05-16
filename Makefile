prog:main.o functions.o
	gcc main.o functions.o -o prog -lSDL -g -lSDL_image -lSDL_mixer -lSDL_ttf
functions.o:functions.c
	gcc -c functions.c -g
main.o:main.c
	gcc -c main.c -g


