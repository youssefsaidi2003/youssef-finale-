#ifndef HEADER_H
#define HEADER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <time.h>

typedef struct {
    SDL_Surface* image;
    SDL_Rect position;
    int isVisible;
    int dir;  
} Platform;

typedef struct {
    SDL_Surface* screen;
    SDL_Surface* background;
    SDL_Surface* scaledBackground;
    SDL_Surface* helpImage;
    Platform* platforms;
    int platformCount;
    int screenWidth, screenHeight;
    int scrollX, scrollY;
    time_t startTime;
    int running;
    int score;
    int bestScore;
    char bestPlayerName[50];
    char playerName[50];  
    TTF_Font* font;
    int showHelp;
} GameState;


int initGame(GameState *game);
void handleInput(GameState *game);
void renderGame(GameState *game);
void updateGame(GameState *game);
void cleanupGame(GameState *game);
void getPlayerName(GameState *game);
void loadHighScore(GameState *game);
void saveHighScore(GameState *game, const char* playerName);
SDL_Surface* scaleSurface(SDL_Surface *surface, int width, int height);

#endif 
