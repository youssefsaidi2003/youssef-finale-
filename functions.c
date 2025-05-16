#include "header.h"

SDL_Surface* scaleSurface(SDL_Surface *surface, int width, int height) {
    SDL_Surface *scaled = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height,
        surface->format->BitsPerPixel,
        surface->format->Rmask,
        surface->format->Gmask,
        surface->format->Bmask,
        surface->format->Amask);

    if (!scaled) {
        printf("Failed to create scaled surface: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_SoftStretch(surface, NULL, scaled, NULL);
    return scaled;
}

void loadHighScore(GameState *game) {
    FILE *file = fopen("highscore.txt", "r");
    if (file) {
        fscanf(file, "%d %[^\n]", &game->bestScore, game->bestPlayerName);
        fclose(file);
    } else {
        game->bestScore = 0;
        strcpy(game->bestPlayerName, "None");
    }
}

void saveHighScore(GameState *game, const char* playerName) {
    if (game->score > game->bestScore) {
        game->bestScore = game->score;
        strncpy(game->bestPlayerName, playerName, sizeof(game->bestPlayerName) - 1);
        game->bestPlayerName[sizeof(game->bestPlayerName) - 1] = '\0';
        
        FILE *file = fopen("highscore.txt", "w");
        if (file) {
            fprintf(file, "%d %s\n", game->bestScore, game->bestPlayerName);
            fclose(file);
        }
    }
}

void getPlayerName(GameState *game) {
    SDL_StartTextInput();
    SDL_Event event;
    char inputBuffer[50] = "";
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color bgColor = {50, 50, 100, 255};
    int done = 0;

    while (!done) {
        SDL_FillRect(game->screen, NULL, SDL_MapRGB(game->screen->format, 50, 50, 100));

       
        SDL_Surface *title = TTF_RenderText_Shaded(game->font, "ENTER YOUR NAME", white, bgColor);
        if (title) {
            SDL_Rect pos = {game->screenWidth/2 - title->w/2, game->screenHeight/2 - 100};
            SDL_BlitSurface(title, NULL, game->screen, &pos);
            SDL_FreeSurface(title);
        }

        
        SDL_Rect inputBox = {game->screenWidth/2 - 200, game->screenHeight/2 - 20, 400, 40};
        SDL_FillRect(game->screen, &inputBox, SDL_MapRGB(game->screen->format, 30, 30, 80));

        
        SDL_Surface *inputSurface = TTF_RenderText_Shaded(game->font, inputBuffer, white, bgColor);
        if (inputSurface) {
            SDL_Rect pos = {game->screenWidth/2 - inputSurface->w/2, game->screenHeight/2 - inputSurface->h/2};
            SDL_BlitSurface(inputSurface, NULL, game->screen, &pos);
            SDL_FreeSurface(inputSurface);
        }

        SDL_Flip(game->screen);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = 1;
                game->running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RETURN) {
                    done = 1;
                } else if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    int len = strlen(inputBuffer);
                    if (len > 0) inputBuffer[len - 1] = '\0';
                }
            } else if (event.type == SDL_TEXTINPUT) {
                if (strlen(inputBuffer) + strlen(event.text.text) < sizeof(inputBuffer) - 1) {
                    strcat(inputBuffer, event.text.text);
                }
            }
        }
    }

    SDL_StopTextInput();

    if (strlen(inputBuffer) == 0) {
        strcpy(game->playerName, "Player1");
    } else {
        strncpy(game->playerName, inputBuffer, sizeof(game->playerName) - 1);
        game->playerName[sizeof(game->playerName) - 1] = '\0';
    }
}

int initGame(GameState *game) {
    game->screenWidth = 1280;
    game->screenHeight = 720;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 0;
    }

    if(TTF_Init() == -1) {
        printf("TTF initialization failed: %s\n", TTF_GetError());
        return 0;
    }

    game->screen = SDL_SetVideoMode(game->screenWidth, game->screenHeight, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if(!game->screen) {
        printf("Failed to create window: %s\n", SDL_GetError());
        return 0;
    }

    SDL_WM_SetCaption("Platform Game", NULL);

    game->font = TTF_OpenFont("arial.ttf", 28);
    if (!game->font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return 0;
    }

    loadHighScore(game);

    game->background = IMG_Load("bg.png");
    if(!game->background) {
        printf("Failed to load background: %s\n", IMG_GetError());
        return 0;
    }

    game->scaledBackground = scaleSurface(game->background, game->screenWidth, game->screenHeight);
    if(!game->scaledBackground) return 0;

    game->helpImage = IMG_Load("help.png");

    game->platformCount = 3;
    game->platforms = malloc(game->platformCount * sizeof(Platform));

    game->platforms[0].image = IMG_Load("platform1.png");
    game->platforms[0].position.x = 300;
    game->platforms[0].position.y = 600;
    game->platforms[0].isVisible = 1;

    game->platforms[1].image = IMG_Load("platform2.png");
    game->platforms[1].position.x = 650;
    game->platforms[1].position.y = 500;
    game->platforms[1].isVisible = 1;
    game->platforms[1].dir = 1;

    game->platforms[2].image = IMG_Load("platform1.png");
    game->platforms[2].position.x = 1000;
    game->platforms[2].position.y = 400;
    game->platforms[2].isVisible = 1;

    game->scrollX = 0;
    game->scrollY = 0;
    game->showHelp = 0;
    game->running = 1;
    game->score = 0;
    game->startTime = time(NULL);

    return 1;
}

void handleInput(GameState *game) {
    SDL_Event event;
    const Uint8 *keystates = SDL_GetKeyState(NULL);

    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            game->running = 0;
        }
        if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.sym == SDLK_ESCAPE) {
                game->running = 0;
            }
            if(event.key.keysym.sym == SDLK_h) {
                game->showHelp = !game->showHelp;
            }
        }
    }

    if (keystates[SDLK_LEFT]) {
        game->scrollX -= 10;
        if (game->scrollX < 0) game->scrollX = 0;
    }
    if (keystates[SDLK_RIGHT]) {
        game->scrollX += 10;
        if (game->scrollX > (game->background->w - game->screenWidth))
            game->scrollX = game->background->w - game->screenWidth;
    }
}

void updateGame(GameState *game) {
    
    if(game->platforms[1].dir == 1 && game->platforms[1].position.y < 600) {
        game->platforms[1].position.y += 2;
    } else if(game->platforms[1].dir == -1 && game->platforms[1].position.y > 400) {
        game->platforms[1].position.y -= 2;
    } else {
        game->platforms[1].dir *= -1;
    }

    
    game->score = game->scrollX;
}

void renderGame(GameState *game) {
    
    SDL_FillRect(game->screen, NULL, SDL_MapRGB(game->screen->format, 0, 0, 0));

    
    SDL_Rect srcRect = { game->scrollX, 0, game->screenWidth, game->screenHeight };
    SDL_Rect destRect = { 0, 0, game->screenWidth, game->screenHeight };
    SDL_BlitSurface(game->background, &srcRect, game->screen, &destRect);

    
    for (int i = 0; i < game->platformCount; i++) {
        if (game->platforms[i].isVisible) {
            SDL_Rect adjustedPos = game->platforms[i].position;
            adjustedPos.x -= game->scrollX;
            SDL_BlitSurface(game->platforms[i].image, NULL, game->screen, &adjustedPos);
        }
    }

    
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color gold = {255, 215, 0, 255};
    SDL_Color blue = {100, 100, 255, 255};

    
    char playerInfo[100];
    sprintf(playerInfo, "Player: %s", game->playerName);
    SDL_Surface *playerSurface = TTF_RenderText_Shaded(game->font, playerInfo, white, black);
    if (playerSurface) {
        SDL_Rect dst = {20, 20};
        SDL_BlitSurface(playerSurface, NULL, game->screen, &dst);
        SDL_FreeSurface(playerSurface);
    }

    
    char scoreText[100];
    sprintf(scoreText, "SCORE: %d", game->score);
    SDL_Surface *scoreSurface = TTF_RenderText_Shaded(game->font, scoreText, gold, black);
    if (scoreSurface) {
        SDL_Rect dst = {(game->screenWidth - scoreSurface->w)/2, 20};
        SDL_BlitSurface(scoreSurface, NULL, game->screen, &dst);
        SDL_FreeSurface(scoreSurface);
    }

    
    char bestScoreText[100];
    sprintf(bestScoreText, "HIGH SCORE: %d by %s", game->bestScore, game->bestPlayerName);
    SDL_Surface *bestScoreSurface = TTF_RenderText_Shaded(game->font, bestScoreText, white, black);
    if (bestScoreSurface) {
        SDL_Rect dst = {game->screenWidth - bestScoreSurface->w - 20, 20};
        SDL_BlitSurface(bestScoreSurface, NULL, game->screen, &dst);
        SDL_FreeSurface(bestScoreSurface);
    }

    /
    if (game->showHelp && game->helpImage) {
        SDL_Rect helpPos = { (game->screenWidth - game->helpImage->w)/2, 
                            (game->screenHeight - game->helpImage->h)/2 };
        SDL_BlitSurface(game->helpImage, NULL, game->screen, &helpPos);
    }

    SDL_Flip(game->screen);
}

void cleanupGame(GameState *game) {
    if(game->background) SDL_FreeSurface(game->background);
    if(game->scaledBackground) SDL_FreeSurface(game->scaledBackground);
    if(game->helpImage) SDL_FreeSurface(game->helpImage);

    for(int i = 0; i < game->platformCount; i++) {
        if(game->platforms[i].image) SDL_FreeSurface(game->platforms[i].image);
    }

    saveHighScore(game, game->playerName);

    free(game->platforms);
    TTF_CloseFont(game->font);
    TTF_Quit();
    SDL_Quit();
}
