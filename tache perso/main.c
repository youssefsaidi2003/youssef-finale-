#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdbool.h>
#include "personne.h"

int main(int argc, char *argv[])
{
    SDL_Surface *screen = NULL;
    SDL_Event event;
    int running = 1;
   

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return 1;
    }

    screen = SDL_SetVideoMode(5000, 4000, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!screen)
    {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return 1;
    }

    

    Interface interface;
    chargerInterface(&interface);
    int selected = afficherMenuSelectionPersonnage(screen, &interface);
    printf("Selected character: %d\n", selected);

    perso p,p2;
   
      
	if (selected == 1) {  
    initperso(&p, "Spritesheet.png");
	}
	else if (selected == 2) { 
 	   initperso(&p, "Spritesheet 2.png");
	}
	else if (selected == 3) {  
    	initperso(&p,"Spritesheet.png");
    	initperso(&p2,"Spritesheet 2.png");
	}
	
   
    while (running)
    {
       

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
    	switch (event.type) {
        case SDL_QUIT:
            	 running = 0;
            	 break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
		case SDLK_h:
                    p.NDeVies--;
                    break;          
		case SDLK_ESCAPE:
                    running = 0;
                    break;
                case SDLK_RIGHT:
                    p.direction = 2;
                    break;
                case SDLK_LEFT:
                    p.direction = 3;
                    break;
                case SDLK_SPACE:
                    saut(&p);
                    p.up = 1;
                    break;
                case SDLK_k:
                    p.Attack = 1;
                    break;
                case SDLK_d:
                    if (selected == 3) p2.direction = 2;
                    break;
                case SDLK_a:
                    if (selected == 3) p2.direction = 3;
                    break;
                case SDLK_w:
                    if (selected == 3) {
                        saut(&p2);
                        p2.up = 1;
                    }
                    break;
                case SDLK_f:
                    if (selected == 3) p2.Attack = 1;
                    break;
                
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT:
		    p.direction = 0;
                    break;
                case SDLK_LEFT:
                    p.direction = 1;
                    break;
                case SDLK_SPACE:
                    p.up = 0;
                    break;
                case SDLK_k:
                    p.Attack = 0;
                    break;
               
                case SDLK_d:
		    if (selected == 3) p2.direction = 0;
                    break;
                case SDLK_a:
                    if (selected == 3) p2.direction = 1;
                    break;
                case SDLK_w:
                    if (selected == 3) p2.up = 0;
                    break;
                case SDLK_f:
                    if (selected == 3) p2.Attack = 0;
                    break;
               
            }
            break;
    }
}

	
     if (selected == 1 || selected == 2) {  
    deplacerPerso(&p);

    p.position.y += p.vitesseV;
    p.vitesseV += 2; 

    if (p.position.y >= 520) {
        p.position.y = 520;
        p.vitesseV = 0;
        p.isOnGround = 1;
        p.jumpcount = 0;
    }
}  
else if (selected == 3) {  
    deplacerPerso(&p);
    deplacerPerso(&p2);

    p.position.y += p.vitesseV;
    p.vitesseV += 2;
    if (p.position.y >= 520) {
        p.position.y = 520;
        p.vitesseV = 0;
        p.isOnGround = 1;
        p.jumpcount = 0;
    }
    p2.position.y += p2.vitesseV;
    p2.vitesseV += 2;
    if (p2.position.y >= 520) {
        p2.position.y = 520;
        p2.vitesseV = 0;
        p2.isOnGround = 1;
        p2.jumpcount = 0;
    }
}

        if (selected == 1 || selected == 2) {  
    animerPerso(&p);  
	}  
	else if (selected == 3) {  
    animerPerso(&p);  
    animerPerso(&p2);  
	}
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

        if (selected == 1 || selected == 2) {  
    afficherPerso(p, screen);  
	}  
	else if (selected == 3) {  
    afficherPerso(p, screen);  
    afficherPerso(p2, screen);  
	}

        SDL_Flip(screen);
        SDL_Delay(16);
    }

    SDL_Quit();
    return 0;
}

