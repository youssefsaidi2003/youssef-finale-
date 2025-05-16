
prog:main.o personne.o
	gcc main.o personne.o -o prog -lSDL -lSDL_image -g -lSDL_ttf -lSDL_mixer


main.o:main.c
	gcc -c main.c -g


personne.o:personne.c personne.h
	gcc -c personne.c -g
