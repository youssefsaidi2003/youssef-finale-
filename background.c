

#include "collision_parfaite.h"
#include "background.h"


void initBack ( background* bg)
{
	bg->bg = IMG_Load("background.png");
	bg->pos_bg.x = 0;
	bg->pos_bg.y = 0;

	bg->pos_scrolling.x = 0;
	bg->pos_scrolling.y = 100;
	bg->pos_scrolling.w = 800;
	bg->pos_scrolling.h = 600;
}

void afficherBack(background* bg,SDL_Surface *screen)
{
	SDL_BlitSurface(bg->bg,&bg->pos_scrolling , screen , &bg->pos_bg );
}


void scrolling_right (background* bg, int* test_scrolling_end_right, double vitesse) 
{
	if ( bg->pos_scrolling.x < 1200 ) 
	{
		bg->pos_scrolling.x +=(20*vitesse);
		*test_scrolling_end_right = 0;
	}
	else{
		*test_scrolling_end_right = 1;
	}

}

void scrolling_left (background* bg , int* test_scrolling_end_left, double vitesse) 
{

	if ( bg->pos_scrolling.x > 0 )
	{
		bg->pos_scrolling.x -=(20*vitesse);
		*test_scrolling_end_left = 0;
	}
	else{
		*test_scrolling_end_left = 1;
	}
}

void scrolling_up (background* bg) 
{

	
	if ( bg->pos_scrolling.y >= 20 )
	{
		bg->pos_scrolling.y -=20;
	}
	else{
		bg->pos_scrolling.y=0;
	}
}

void scrolling_down(background* bg) 
{

	
	if ( bg->pos_scrolling.y < 100 )
	{
		bg->pos_scrolling.y +=20;
	}
	else{
		bg->pos_scrolling.y=100;
	}
}

void free_background(background* bg)
{
	SDL_FreeSurface(bg->bg);
}
