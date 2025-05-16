#include "personne.h"


#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <math.h>



int initperso(perso *p, char *cheminSpritesheet)

{
    p->spritesheet = IMG_Load(cheminSpritesheet);
    p->heart1=IMG_Load("heart.png");
     p->heart2=IMG_Load("heart.png");
 p->heart3=IMG_Load("heart.png");	
    p->position.x = 180;
    p->position.y = 520;
    p->position.w = 210;
    p->position.h = 280;
    p->direction = 0;
  
    p->vitesse = 0;
    p->up = 0 ;
    p->vitesseV = 0;
    p->pos_sprite.x = 0;
    p->pos_sprite.y = 0;
    int spritew = 7320 ;
    int spriteh = 3540 ; 
    p->pos_sprite.h = spriteh / 11;
    p->pos_sprite.w = spritew / 20;
    p->isOnGround=1;
    p->Attack=0;
 

    p->pheart1.x=630;
    p->pheart1.y=-220;	
    p->pheart2.x=710;
    p->pheart2.y=-220;
    p->pheart3.x=790;
    p->pheart3.y=-220;
	p->NDeVies=3;
        p->jumpcount=0;
	
	return 1;

}

void afficherPerso(perso p, SDL_Surface *screen)
{
    SDL_BlitSurface(p.spritesheet, &p.pos_sprite, screen, &p.position);
if (p.NDeVies >= 1) {
    SDL_BlitSurface(p.heart1, NULL, screen, &p.pheart1);
}
if (p.NDeVies >= 2) {
    SDL_BlitSurface(p.heart2, NULL, screen, &p.pheart2);
}
if (p.NDeVies >= 3) {
    SDL_BlitSurface(p.heart3, NULL, screen, &p.pheart3);
}
}

void animerPerso(perso *p)
{ 
    int spritew = 7320 ;
    int spriteh = 3540 ; 
   
    if (p->Attack)
    {
        if (p->direction == 0)e
        {
            p->pos_sprite.y = 9 * spriteh / 11;
            p->pos_sprite.x += spritew / 20;
            if (p->pos_sprite.x >= spritew)
                p->pos_sprite.x = 0; 
        }
	
        else if (p->direction == 1)
        {   
		
            p->pos_sprite.y = 10 * spriteh / 11 ;
            p->pos_sprite.x += spritew / 20;
	     
            if (p->pos_sprite.x >= spritew-30)
                p->pos_sprite.x = 0-30; 
        }
    }
   
    else
    {
        if ((p->direction == 0)&&(p->up == 0)) 
    {
        p->pos_sprite.y = 0;
        p->pos_sprite.x = 0;
    }
    if ((p->direction == 1)&&(p->up == 0))
    {
        p->pos_sprite.y = 0;
        p->pos_sprite.x = spritew / 20 ;
    }
    if ((p->direction == 2)&&(p->up == 0))
    {
        p->pos_sprite.y = spriteh / 11;
        p->pos_sprite.x += spritew / 20 ;
    }
    if ((p->direction == 3)&&(p->up == 0))
    {
        p->pos_sprite.y = 2 * spriteh / 11;
        p->pos_sprite.x += spritew / 20;
    }
    if (((p->direction == 0)||(p->direction == 2))&&(p->up == 1))
    {
        p->pos_sprite.y = 3 * spriteh / 11;
        p->pos_sprite.x = 0;
	p->pos_sprite.x += spritew / 20; 

    }
    if (((p->direction == 1)||(p->direction == 3))&&(p->up == 1))
    {
        p->pos_sprite.y = 3 * spriteh / 11;
        p->pos_sprite.x = spritew / 20;
	p->pos_sprite.x += spritew / 20; 
    }
    if (p->pos_sprite.x >= spritew -50)
        p->pos_sprite.x = 0;

    }
    

}


void deplacerPerso(perso *p)
{
    p->vitesse=10;
    if (!p->Attack)
    {
        if ((p->direction == 2))
    {
        p->position.x += 5;
    }
   else if ((p->direction == 3))
        p->position.x -= 5;

    }
               
}

void saut(perso *p)
{	
    if (p->position.y ==520)
		{
		p->jumpcount=0;
    		}
    printf("jump %d\n",p->jumpcount);
			
    if ( p->jumpcount==0)
    {	
        p->vitesseV =-15;
	p->jumpcount++;
			
    }
   else 
	if ( p->jumpcount==1)
    {	
        p->vitesseV =-10;
	p->jumpcount++;
			
    }	
}
int chargerInterface(Interface *Interface)
{
   
    Interface->SelectionPersonnage=IMG_Load("Player Select Interface.png");
    Interface->SelectionMode=IMG_Load("Gaia_Selection_2.png");
    Interface->BoutonChoose[0]=IMG_Load("Gaia_Choose_Button.png");
    Interface->BoutonChoose[1]=IMG_Load("Gaia_Choose_Button_2.png");
		
    

}
		

}

int afficherMenuSelectionPersonnage(SDL_Surface *screen, Interface *Interface)
{
    
    int SelectionBouton1 = 0, SelectionBouton2 = 0, continuer2 = 1;
    int choixMode = 0;
    SDL_Rect positionimgmenup;
    SDL_Event event;

    
    positionimgmenup.x = 100;
    positionimgmenup.y = 100;

    Interface->BoutonSingleplayer = IMG_Load("p1.png");
    Interface->BoutonMultiplayer = IMG_Load("p2.png");

   
    Interface->pBoutonSingleplayer.x = 500;
    Interface->pBoutonSingleplayer.y = 500;
    Interface->pBoutonMultiplayer.x = 900;
    Interface->pBoutonMultiplayer.y = 500;

    while (continuer2) {
        
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

        
        SDL_BlitSurface(Interface->SelectionMode, NULL, screen, &positionimgmenup);
        SDL_BlitSurface(Interface->BoutonSingleplayer, NULL, screen, &Interface->pBoutonSingleplayer);
        SDL_BlitSurface(Interface->BoutonMultiplayer, NULL, screen, &Interface->pBoutonMultiplayer);

        SDL_Flip(screen);  

        
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT) {
            return 0; 
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x;
            int y = event.button.y;

            
            if (x >= 500 && x <= 650 && y >= 500 && y <= 600) {  
                choixMode = 1; 
                continuer2 = 0; 
            }
            
            else if (x >= 900 && x <= 1050 && y >= 500 && y <= 600) {  
                choixMode = 2;  
                continuer2 = 0; 
            }
        }
    }
    

	 



    if (choixMode==1){
    Interface->posBoutonChoose[0].x=500;
    Interface->posBoutonChoose[0].y=750;
    Interface->posBoutonChoose[1].x=Interface->posBoutonChoose[0].x+450;
    Interface->posBoutonChoose[1].y=Interface->posBoutonChoose[0].y;



    
   
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    
    SDL_BlitSurface(Interface->SelectionPersonnage, NULL, screen, &positionimgmenup);
    SDL_BlitSurface(Interface->BoutonChoose[SelectionBouton1], NULL, screen, &Interface->posBoutonChoose[0]);
    SDL_BlitSurface(Interface->BoutonChoose[SelectionBouton2], NULL, screen, &Interface->posBoutonChoose[1]);


    

    
    SDL_Flip(screen);

    SDL_Event event;
    int continuer = 1;
    int choixPersonnage = 0;
   while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
            if ((event.button.x >= Interface->posBoutonChoose[0].x) &&
                        (event.button.x < Interface->posBoutonChoose[0].x + Interface->BoutonChoose[0]->w) &&
                        (event.button.y >= Interface->posBoutonChoose[0].y) &&
                        (event.button.y < Interface->posBoutonChoose[0].y + Interface->BoutonChoose[0]->h))
                        {
                            choixPersonnage=1;
                            continuer=0;
                        }
                        if ((event.button.x >= Interface->posBoutonChoose[1].x) &&
                        (event.button.x < Interface->posBoutonChoose[1].x + Interface->BoutonChoose[0]->w) &&
                        (event.button.y >= Interface->posBoutonChoose[1].y) &&
                        (event.button.y < Interface->posBoutonChoose[1].y + Interface->BoutonChoose[0]->h))
                        {
                            choixPersonnage=2;
                            continuer=0;
                        }
            break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_u: 
                        choixPersonnage = 1;
                        continuer=0;
                        break;
                    case SDLK_t: 
                        choixPersonnage = 2;
			 continuer=0;
                        
                        break;
                }
                break;
        }
    }
	return choixPersonnage;
    }
    SDL_FreeSurface(Interface->SelectionPersonnage);
    
}
