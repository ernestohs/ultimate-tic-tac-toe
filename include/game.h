#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define BOARD_SIZE 3
#define EMPTY ' '
#define PLAYER_X 'X'
#define PLAYER_O 'O'

typedef struct {
    char small_boards[BOARD_SIZE][BOARD_SIZE][BOARD_SIZE][BOARD_SIZE];
    char big_board[BOARD_SIZE][BOARD_SIZE];
    int current_player;
    int active_board_row;
    int active_board_col;
    int cursor_row;
    int cursor_col;
    bool first_move;
    int required_board_row;    // The board row where the next move must be played
    int required_board_col;    // The board col where the next move must be played
} GameState;

// Core game logic functions
void initializeGame(GameState* game);
bool checkWin(const char board[BOARD_SIZE][BOARD_SIZE], char player);
bool isBoardFull(const char board[BOARD_SIZE][BOARD_SIZE]);
bool isValidMove(const GameState* game);
void updateActiveBoard(GameState* game);
bool isGameOver(const GameState* game);
char getCurrentPlayer(const GameState* game);
bool makeMove(GameState* game);

#endif // GAME_H
