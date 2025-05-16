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

int loading_menu(perso* p, minimap* mp, background* bg, SDL_Surface* screen)
{

    // Load button images
    SDL_Surface* load_img = IMG_Load("loadgame.png");
    SDL_Surface* load_img_hover = IMG_Load("loadgamehover.png");
    SDL_Surface* new_img = IMG_Load("newgame.png");
    SDL_Surface* new_img_hover = IMG_Load("newgamehover.png");

    if (!load_img || !load_img_hover || !new_img || !new_img_hover) {
        fprintf(stderr, "Failed to load one or more button images.\n");
        return 0;
    }

    // Button positions (centered horizontally)
    SDL_Rect load_pos = { 150, 150, 436, 95 }; // left button
    SDL_Rect new_pos = { 150, 270, 436, 95 };      // right button

    // Init TTF for text rendering
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("police.ttf", 28);
    if (!font) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        return 0;
    }
    SDL_Color textColor = {255, 255, 255, 255};

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Choisir l'un des deux choix au dessous", textColor);
    SDL_Rect textPos = { 120, 30, textSurface->w, textSurface->h };

    SDL_Event event;
    int continuer = 1;

    int hover_load = 0;
    int hover_new = 0;

    while (continuer)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    continuer = 0;
                    break;

                case SDL_MOUSEMOTION:
                {
                    int x = event.motion.x;
                    int y = event.motion.y;

                    hover_load = (x >= load_pos.x && x <= load_pos.x + load_pos.w &&
                                  y >= load_pos.y && y <= load_pos.y + load_pos.h);

                    hover_new = (x >= new_pos.x && x <= new_pos.x + new_pos.w &&
                                 y >= new_pos.y && y <= new_pos.y + new_pos.h);
                }
                break;

                case SDL_MOUSEBUTTONDOWN:
                {
                    int x = event.button.x;
                    int y = event.button.y;

                    if (x >= load_pos.x && x <= load_pos.x + load_pos.w &&
                        y >= load_pos.y && y <= load_pos.y + load_pos.h)
                    {
                        // Load game
                        load_game(mp, bg, p, "progress.txt");  // Your load function
                        continuer = 0;
                        break;
                    }
                    else if (x >= new_pos.x && x <= new_pos.x + new_pos.w &&
                             y >= new_pos.y && y <= new_pos.y + new_pos.h)
                    {
                        // New game - just exit menu to start fresh
                        continuer = 0;
                    }
                }
                break;
            }
        }

        // Fill background with dark color
        SDL_FillRect(screen, NULL, SDL_MapRGB((screen)->format, 30, 30, 30));

        if(screen && textSurface) {
            SDL_BlitSurface(textSurface, NULL, screen, &textPos);
        }

        if (hover_load)
            SDL_BlitSurface(load_img_hover, NULL, screen, &load_pos);
        else
            SDL_BlitSurface(load_img, NULL, screen, &load_pos);

        if (hover_new)
            SDL_BlitSurface(new_img_hover, NULL, screen, &new_pos);
        else
            SDL_BlitSurface(new_img, NULL, screen, &new_pos);

        SDL_Flip(screen);

        SDL_Delay(16);
    }

    // Cleanup
    SDL_FreeSurface(load_img);
    SDL_FreeSurface(load_img_hover);
    SDL_FreeSurface(new_img);
    SDL_FreeSurface(new_img_hover);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);

    // Restore screen to original size for main game

    return 1;
}


void save_game(const minimap* mp, const background* bg, const perso* p, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        perror("Error opening save file");
        return;
    }

    // Save mini hero position
    fprintf(f, "%d %d\n", mp->pos_minihero.x, mp->pos_minihero.y);

    // Save background scrolling position
    fprintf(f, "%d %d\n", bg->pos_scrolling.x, bg->pos_scrolling.y);

    // Save perso absolute and relative positions
    fprintf(f, "%d %d\n", p->pos_perso.x, p->pos_perso.y);
    fprintf(f, "%d %d\n", p->pos_perso_absolue.x, p->pos_perso_absolue.y);

    fclose(f);
}


int load_game(minimap* mp, background* bg, perso* p, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        perror("Save file not found");
        return 0;
    }

    // Use %hd for Sint16 (short int)
    fscanf(f, "%hd %hd", &mp->pos_minihero.x, &mp->pos_minihero.y);
    fscanf(f, "%hd %hd", &bg->pos_scrolling.x, &bg->pos_scrolling.y);
    fscanf(f, "%hd %hd", &p->pos_perso.x, &p->pos_perso.y);
    fscanf(f, "%hd %hd", &p->pos_perso_absolue.x, &p->pos_perso_absolue.y);

    fclose(f);
    return 1;
}