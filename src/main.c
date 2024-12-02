#include "../include/game.h"
#include "../include/ui.h"

int main() {
    GameState game;
    initializeGame(&game);
    
    enableRawMode();
    
    bool running = true;
    while (running) {
        drawBoard(&game);
        running = handleInput(&game);
    }
    
    disableRawMode();
    printf("\nGame Over!\n");
    return 0;
}
