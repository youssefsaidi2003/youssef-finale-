#ifndef PERSO_H_INCLUDED
#define PERSO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>



typedef struct perso
{
    SDL_Surface *spritesheet;
    SDL_Surface *heart1;
SDL_Surface *heart2;
SDL_Surface *heart3;

  char NVies[5];

SDL_Rect pheart1; 
SDL_Rect pheart2;
SDL_Rect pheart3;
    SDL_Rect position; 
    int vitesse;
    int collision;
    double acceleration;
    int direction;
    
    SDL_Rect pos_sprite;
    
    
    int jumpcount;
     
    int vitesseV;
    int up ;
    int isOnGround;
    int Attack;
    
    int NDeVies;

} perso;


typedef struct
{
    SDL_Surface *Background, *SelectionPersonnage, *SelectionMode, *BoutonChoose[2], *BoutonSingleplayer, *BoutonMultiplayer;
    SDL_Rect posBoutonChoose[2] ,pBoutonSingleplayer,pBoutonMultiplayer;

}Interface;

int initperso(perso *p, char *cheminSpritesheet);
void afficherPerso(perso *p, SDL_Surface *screen);
void deplacerPerso(perso *p);
void animerPerso(perso *p);
void saut(perso *p);
int chargerInterface(Interface *Interface);
int afficherMenuSelectionPersonnage(SDL_Surface *screen, Interface *Interface);

#endif
