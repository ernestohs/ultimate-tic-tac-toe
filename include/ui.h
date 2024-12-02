#ifndef UI_H
#define UI_H

#include "game.h"

#define KEY_ESC 27
#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_ENTER 10

// UI functions
void drawBoard(const GameState* game);
bool handleInput(GameState* game);
bool handleQuit(void);
void enableRawMode(void);
void disableRawMode(void);
char getChar(void);

#endif // UI_H
