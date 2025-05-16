#include "minimap.h"
#include <math.h>

void initmap(minimap* mp)
{
	mp->mini_map = IMG_Load("minimap.png");
	mp->pos_minimap.x = 300;
	mp->pos_minimap.y = 20;
	mp->mini_hero = IMG_Load("mini_perso.png");
	mp->pos_minihero.x = 300;
	mp->pos_minihero.y = 100;
	
}

void afficherminimap( minimap* mp,SDL_Surface *screen)
{
	SDL_BlitSurface(mp->mini_map,NULL,screen,&mp->pos_minimap);
	SDL_BlitSurface(mp->mini_hero,NULL,screen,&mp->pos_minihero);
}


void dep_mini_hero(SDL_Rect* pos_perso,minimap *mp ,int redimensionnement,int sens)
{
	SDL_Rect temp;
	temp.x =( (*pos_perso).x*redimensionnement )/100;
	temp.y =( ((*pos_perso).y)*redimensionnement )/110;
    printf("temp.y = %d \n ",temp.y );
	if ( sens == 0 )
	{
		if (mp->pos_minihero.x <= 610 )
			mp->pos_minihero.x = 300 + temp.x;
	}
	else if ( sens == 1 )
	{
		if (mp->pos_minihero.x > 300 )
			mp->pos_minihero.x = 300 + temp.x ;
	}
	else if ( sens == 2 )
	{
		if (mp->pos_minihero.y > 55 )
			mp->pos_minihero.y = 20 + temp.y;
	}
	else if ( sens == 3 )
	{
		if (mp->pos_minihero.y <= 200 )
			mp->pos_minihero.y = 30 + temp.y;
	}
}

void free_minimap(minimap* mp)
{
	SDL_FreeSurface(mp->mini_map);
	SDL_FreeSurface(mp->mini_hero);
}
