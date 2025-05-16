#ifndef COLLISION_PARFAITE_H_INCLUDED
#define COLLISION_PARFAITE_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>


struct collision
{
	SDL_Surface* bg_collision;
	float x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,x6,y6,x7,y7,x8,y8;
	SDL_Color color1,color2,color3,color4,color5,color6,color7,color8;
};
typedef struct collision collision; 

void init_col( collision* c);
SDL_Color GetPixel (SDL_Surface *bg, int x, int y);
void update_points_de_collision(collision* c,  SDL_Rect *pos_perso);
void Read_Colors( collision* c);
int collision_droite(collision* col);
int collision_gauche(collision* col);
int collision_haut(collision* col);
int collision_bas(collision* col);
#endif // COLLISION_H_INCLUDED
