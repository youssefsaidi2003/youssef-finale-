#ifndef MINIMAP_H_INCLUDED
#define MINIMAP_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <math.h>
#include <time.h>
#include "string.h"
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>


struct minimap
{
	SDL_Surface* mini_map;
	SDL_Rect pos_minimap;
	SDL_Surface* mini_hero;
	SDL_Rect pos_minihero;
	
	SDL_Surface* AnimationEnigme;
	SDL_Rect pos_AnimationEnigme;
	int frameAnimation;
	
	
};
typedef struct minimap minimap; 


void initmap(minimap* mp);
void afficherminimap( minimap* mp,SDL_Surface *screen);
void dep_mini_hero (SDL_Rect* pos_perso,minimap *mp ,int redimensionnement,int sens);
void free_minimap(minimap* mp);
void animation_minimap(minimap* mp);


#endif 
