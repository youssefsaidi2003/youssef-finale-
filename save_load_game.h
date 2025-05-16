#ifndef SAVE_LOAD_GAME_H_INCLUDED
#define SAVE_LOAD_GAME_H_INCLUDED
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "background.h"
#include "perso.h"
#include "collision_parfaite.h"
#include "minimap.h"
#include "save_load_game.h"
int loading_menu(perso *p, minimap *mp, background *bg, SDL_Surface *screen);
void save_game(const minimap* mp, const background* bg, const perso* p, const char* filename);
int load_game(minimap* mp, background* bg, perso* p, const char* filename);
#endif 
