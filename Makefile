prog: main.o collision_parfaite.o background.o perso.o minimap.o save_load_game.o
	gcc main.o collision_parfaite.o background.o perso.o minimap.o save_load_game.o -o prog -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lm

main.o:main.c
	gcc -c main.c
	
collision_parfaite.o:collision_parfaite.c
	gcc -c collision_parfaite.c
background.o:background.c
	gcc -c background.c
perso.o:perso.c
	gcc -c perso.c
minimap.o:minimap.c
	gcc -c minimap.c
save_load_game.o:save_load_game.c
	gcc -c save_load_game.c
