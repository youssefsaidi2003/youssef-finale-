#include "perso.h"


void initPerso(perso* h)
{
	int i = 0;

	h->perso= IMG_Load("perso.png");




	for ( i = 0 ; i < 4 ; i++ ){
		h->tab_perso[0][i].x = i*100;
		h->tab_perso[0][i].y = 0;
		h->tab_perso[0][i].w = 100;
		h->tab_perso[0][i].h = 100;
	}
	for ( i = 0 ; i < 4 ; i++ ){
		h->tab_perso[1][i].x = i*100;
		h->tab_perso[1][i].y = 100;
		h->tab_perso[1][i].w = 100;
		h->tab_perso[1][i].h = 100;
	}


	h->pos_perso.x = 10;
	h->pos_perso.y = 385;
	h->pos_perso_absolue.x = 10;
    h->pos_perso_absolue.y = 485;
    h->pos_perso_absolue.w = 100;
    h->pos_perso_absolue.h = 100;

	h->sens= 0;
	h->frame= 0;

	h->persoisjumping = 0;
	h->speedup = 0 ;
	h->speeddown = 10 ;
	h->directionjump = 1;
	h->ground = 385 ;
	h->gravity = 0;

	h->persospeed=0;
	h->acceleration = 1;

}


void afficherPerso( perso* h,SDL_Surface *screen)
{
	if ( h->sens == 0 )
	{
		SDL_BlitSurface(h->perso,&h->tab_perso[0][h->frame],screen,&h->pos_perso);
	}
	else
		SDL_BlitSurface(h->perso,&h->tab_perso[1][h->frame],screen,&h->pos_perso);
}


void animationPerso(perso* h)
{

	h->frame++;
	if ( h->frame > 3 )
	{
		h->frame = 0;
	}
}

void Free_perso(perso* h)
{
	SDL_FreeSurface(h->perso);

}


void deplacement(perso *h, SDL_Rect* camera, int right , int left )
{
	if ( right == 1 ){
		if ( h->sens == 0 && camera->x > 5999 )
		{
			if ( h->pos_perso.x <= 6980 ) 
			{
				h->pos_perso.x +=10;
			}
		}
	}

	if ( left == 1 ){
		if ( h->sens == 1 && camera->x > 6000 )
		{
			if ( h->pos_perso.x > 20 ) 
			{
				h->pos_perso.x -=10;
			}
		}
	}
}

void jump(perso* h,SDL_Rect* pos_abs)
{

    if ( h->persoisjumping == 1 )
    {
        if ( h->gravity == 0 )
        {
            h->pos_perso.y -= (h->pos_perso.y/8);
			pos_abs->y -= (h->pos_perso.y/8); 
			
            SDL_Delay(h->speedup);
			if( h->speedup <= 5)
			{
				h->speedup +=1;
			}

			if ( h->pos_perso.y <= 150 )
			{
				h->gravity = 1;
			}
        }
        
        if ( h->gravity == 1 )
        {
        
            SDL_Delay(h->speeddown);
            if ( h->speeddown >=1 )
            {
                h->speeddown -= 1;
            }
 	    	if ( h->pos_perso.y <= h->ground -10 )
            {
                h->pos_perso.y += (h->pos_perso.y/8);
				pos_abs->y += (h->pos_perso.y/8); 
            }
            if ( h->pos_perso.y >= h->ground -10 )
            {
                h->pos_perso.y = h->ground;
				h->pos_perso_absolue.y = h->ground+100; 
                restart_jump(h);
                h->persoisjumping = 0;
            }
           
        }
    }	
}


void restart_jump ( perso* h )
{
    h->speedup = 0;
    h->gravity = 0;
    h->speeddown = 20;
}


void acceleration(perso *h)
{
	if ( h->acceleration > 2.00){
		h->acceleration = 2.00;
	}else{
		h->acceleration+=0.1;
	}
}

void decceleration(perso *h)
{
	h->acceleration = 1.00;
}

