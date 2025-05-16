#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "background.h"
#include "perso.h"
#include <SDL/SDL_mixer.h>
#include "collision_parfaite.h"
#include "minimap.h"
#include <math.h>
#include "save_load_game.h"
int main(int argc, char *argv[])
{
    SDL_Surface *screen =NULL;
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Event event;
    screen=SDL_SetVideoMode(800,500, 32,SDL_HWSURFACE| SDL_DOUBLEBUF);
    SDL_WM_SetCaption("game",NULL);

    Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
    Mix_Music *musique=NULL;
    musique=Mix_LoadMUS("mario.mp3");
    Mix_PlayMusic(musique,-1);

    int continuer=1;
    SDL_EnableKeyRepeat(0,0);

    int right = 0,left = 0,detect_collision_bas = 0,detect_collision_haut=0;
    perso p;
    minimap mp;
    collision col;
    background bg;
	// Call the loading menu
	initPerso(&p);
	initBack(&bg);
	initmap(&mp);
	init_col(&col);
	int testLoading = loading_menu(&p, &mp, &bg, screen);

	if (!testLoading) {
		return 0;  // player chose to quit from the menu
	}


	// If player chose "New Game", initialize
	if (p.pos_perso.x == 0 && p.pos_perso.y == 0) {  // or some other flag
		
	}
	
    int test_scrolling_end_right = 0,test_scrolling_end_left = 0;
    SDL_WM_SetCaption("game",NULL);

    while(continuer == 1)
    {
        
        SDL_PollEvent(&event);
        switch(event.type)
        {
		case SDL_QUIT:
		    continuer=0;

		    break;

		case SDL_KEYDOWN:
		    switch(event.key.keysym.sym)
		    {
			    case SDLK_ESCAPE:
				continuer=0;

				break;

			    case SDLK_RIGHT :
			    {
			    	right = 1;
			    }
			    break;

			    case SDLK_LEFT :
			    {
			    	left = 1;
			    }
			    break;
			    
			    case SDLK_SPACE :
			    {
			    	p.persoisjumping = 1;
			    }
			    break;

				case SDLK_LSHIFT :
			    {
			    	acceleration(&p);
			    }
			    break;
				
		   
		    }
		    break;
		    
		    case SDL_KEYUP:
		    switch(event.key.keysym.sym)
		    {
			    case SDLK_ESCAPE:
				continuer=0;

				break;

			    case SDLK_RIGHT :
			    {
			    	right = 0;
			    }
			    break;
			    
			    case SDLK_LEFT :
			    {
			    	left = 0;
			    }
			    break;
			    
			    case SDLK_SPACE :
			    {
			    
			    }
			    break;

				case SDLK_LSHIFT :
			    {
			    	decceleration(&p);
			    }
			    break;
		   
		    }
		    break;

        }

		

		
		
		jump(&p,&(p.pos_perso_absolue));

		
		update_points_de_collision(&col, &(p.pos_perso_absolue));
		Read_Colors(&col);

		

		if ( collision_bas(&col) != -1  ){ 
			if ( collision_haut(&col) == -1 ){
				p.gravity = 1;
				jump(&p,&(p.pos_perso_absolue));
			}else{
				if ( detect_collision_bas == 1 ){
					if ( p.pos_perso.y != p.ground ){
						p.persoisjumping = 1;
						p.gravity = 1;
					}	
					detect_collision_bas = 0;
				}
			}
		}else{				    
				detect_collision_bas = 1;
				p.persoisjumping = 0;

		}

		

		if ( p.gravity== 0 && p.persoisjumping == 1 ){
			scrolling_up(&bg);
			if ( p.pos_perso_absolue.y > 160 ){
				p.pos_perso_absolue.y -=15;
			}
			dep_mini_hero (&(p.pos_perso_absolue),&mp,20,2);
		}
		if ( p.gravity== 1 && collision_bas(&col) != -1)
		{	
			scrolling_down(&bg);
			if ( p.pos_perso_absolue.y <= 365 ){ 
				p.pos_perso_absolue.y +=15;
			}
			dep_mini_hero (&(p.pos_perso_absolue),&mp,20,3);
		}
		

		
		

		if ( right == 1 ){
			if ( collision_droite(&col) != -1  ){
				scrolling_right(&bg,&test_scrolling_end_right,p.acceleration);
				if ( test_scrolling_end_right == 0 ){
					p.pos_perso_absolue.x+=(20*p.acceleration);
				}
				p.sens = 0;
				animationPerso(&p);
				dep_mini_hero (&(p.pos_perso_absolue),&mp,20,0);
			}
		}
		
		if ( left == 1 ){
			if ( collision_gauche(&col) != -1  ){
				scrolling_left(&bg, &test_scrolling_end_left,p.acceleration);
				if ( test_scrolling_end_left == 0 ){
					p.pos_perso_absolue.x-=(20*p.acceleration);
				}
				p.sens = 1;
				animationPerso(&p);
				dep_mini_hero (&(p.pos_perso_absolue),&mp,20,1);
			}
		}
		
		
		
		
		
		
		
		afficherBack(&bg,screen);
		afficherminimap(&mp,screen);
		
		afficherPerso(&p,screen);
		SDL_Flip(screen);
		

		SDL_Delay(100);
    } 

	save_game(&mp, &bg, &p, "progress.txt");
    Free_perso(&p);
    free_background(&bg);
    free_minimap(&mp);
    SDL_Quit();

    return EXIT_SUCCESS ;
}

