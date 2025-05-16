#include "header.h"

int main(int argc, char *argv[]) {
    GameState game;

    if (!initGame(&game)) {
        printf("Game initialization failed!\n");
        return 1;
    }

    getPlayerName(&game);  

    while (game.running) {
        handleInput(&game);
        updateGame(&game);
        renderGame(&game);
        SDL_Delay(16); // 
    }

    cleanupGame(&game);
    return 0;
}
