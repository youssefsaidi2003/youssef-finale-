#ifndef PERSO_H_INCLUDED
#define PERSO_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <math.h>
#include <time.h>
#include "string.h"
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>


struct perso
{
	SDL_Surface *perso;
	SDL_Rect pos_perso;
	SDL_Rect pos_perso_absolue;
	SDL_Rect tab_perso[2][4];

	int sens,frame;
	int persoisjumping,gravity,speedup,speeddown,directionjump,ground,persospeed;
	double acceleration;
	
};
typedef struct perso perso; 

void initPerso(perso* h);
void afficherPerso( perso* h,SDL_Surface *screen);
void animationPerso (perso* h);
void Free_perso(perso* h);
void jump(perso* h,SDL_Rect* pos_abs);
void restart_jump ( perso* h );
void acceleration(perso *h);
void decceleration(perso *h);
void deplacement(perso *h, SDL_Rect* camera,int right , int left);
#endif 
