#include "collision_parfaite.h"

void init_col( collision* c)
{
    c->bg_collision = IMG_Load("mask.png");
    c->x1 = 0;
    c->y1 = 0;
    c->x2 = 0;
    c->y2 = 0;
    c->x3 = 0;
    c->y3 = 0;
    c->x4 = 0;
    c->y4 = 0;
    c->x5 = 0;
    c->y5 = 0;
    c->x6 = 0;
    c->y6 = 0;
    c->x7 = 0;
    c->y7 = 0;
    c->x8 = 0;
    c->y8 = 0;
    c->color1.r=0;
    c->color1.g=0;
    c->color1.b=0;

    c->color2.r=0;
    c->color2.g=0;
    c->color2.b=0;

    c->color3.r=0;
    c->color3.g=0;
    c->color3.b=0;

    c->color4.r=0;
    c->color4.g=0;
    c->color4.b=0;

    c->color5.r=0;
    c->color5.g=0;
    c->color5.b=0;

    c->color6.r=0;
    c->color6.g=0;
    c->color6.b=0;

    c->color7.r=0;
    c->color7.g=0;
    c->color7.b=0;

    c->color8.r=0;
    c->color8.g=0;
    c->color8.b=0;

}

SDL_Color GetPixel (SDL_Surface *bg, int x, int y)
{

    SDL_Color color ;
    Uint32 col=0; 
    char* pPosition = (char*)bg->pixels ; 
    pPosition += (bg->pitch * y); 
    pPosition += (bg->format->BytesPerPixel * x); 
    memcpy(&col, pPosition, bg->format->BytesPerPixel); 
    SDL_GetRGB(col,bg->format, &color.r, &color.g,&color.b ); 

    return color ;

}

void Read_Colors( collision* c){

	c->color1=GetPixel (c->bg_collision, c->x1, c->y1) ;
	c->color2=GetPixel (c->bg_collision, c->x2, c->y2) ;
	c->color3=GetPixel (c->bg_collision, c->x3, c->y3) ;
	c->color4=GetPixel (c->bg_collision, c->x4, c->y4) ;
	c->color5=GetPixel (c->bg_collision, c->x5, c->y5) ;
	c->color6=GetPixel (c->bg_collision, c->x6, c->y6) ;
	c->color7=GetPixel (c->bg_collision, c->x7, c->y7) ;
	c->color8=GetPixel (c->bg_collision, c->x8, c->y8) ;
}


void update_points_de_collision(collision* c,  SDL_Rect *pos_perso)
{

    c->x1=pos_perso->x + 70 ;
    c->y1=pos_perso->y + 15 ;

    c->x2=pos_perso->x + 70 ;
    c->y2= pos_perso->y + 50  ;

    c->x3=  pos_perso->x + 70 ;
    c->y3= pos_perso->y + 85  ;


    c->x4=pos_perso->x + 25;
    c->y4= pos_perso->y + 15;


    c->x5=pos_perso->x  + 25;
    c->y5= pos_perso->y + 50  ;

    c->x6=pos_perso->x + 25;
    c->y6= pos_perso->y + 85  ;


    c->x7=pos_perso->x + 50 ;
    c->y7= pos_perso->y + 15;

    c->x8=pos_perso->x + 50;
    c->y8= pos_perso->y + 85  ;
    
    
    
       

}

int collision_droite(collision* col){
	if( (col->color1.r==0  &&  col->color1.g==0 &&  col->color1.b==0) && (col->color2.r==0  &&  col->color2.g==0 &&  col->color2.b==0) ||  (col->color2.r==0  &&  col->color2.g==0 &&  col->color2.b==0) && (col->color3.r==0  &&  col->color3.g==0 &&  col->color3.b==0)  )
        {
            return -1;
        }
        return 0;
}

int collision_gauche(collision* col){
	if( (col->color4.r==0  &&  col->color4.g==0 &&  col->color4.b==0) && (col->color5.r==0  &&  col->color5.g==0 &&  col->color5.b==0) || (col->color5.r==0 &&  col->color5.g==0 &&  col->color5.b==0) && (col->color6.r==0  &&  col->color6.g==0 &&  col->color6.b==0) )
        {
            return -1;
        }
        return 0;
}

int collision_haut(collision* col){
	if( (col->color1.r==0  &&  col->color1.g==0 &&  col->color1.b==0) && (col->color7.r==0  &&  col->color7.g==0 &&  col->color7.b==0) || (col->color4.r==0  &&  col->color4.g==0 &&  col->color4.b==0) && (col->color7.r==0  &&  col->color7.g==0 &&  col->color7.b==0) )
        {
            return -1;
        }
        return 0;
}

int collision_bas(collision* col){
	if( (col->color8.r==0 && col->color8.g==0 &&  col->color8.b==0) && (col->color6.r==0 &&  col->color6.g==0 &&  col->color6.b==0) || (col->color3.r==0 &&  col->color3.g==0 &&  col->color3.b==0) && (col->color8.r==0 &&  col->color8.g==0 &&  col->color8.b==0) )
        {
            return -1;
        }
        return 0;
}


