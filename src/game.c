#include "../include/game.h"

void initializeGame(GameState* game) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            for (int k = 0; k < BOARD_SIZE; k++) {
                for (int l = 0; l < BOARD_SIZE; l++) {
                    game->small_boards[i][j][k][l] = EMPTY;
                }
            }
            game->big_board[i][j] = EMPTY;
        }
    }
    
    game->current_player = 0;
    game->active_board_row = 1;
    game->active_board_col = 1;
    game->cursor_row = 1;
    game->cursor_col = 1;
    game->first_move = true;
    game->required_board_row = -1;  // -1 means any board is valid
    game->required_board_col = -1;
}

bool checkWin(const char board[BOARD_SIZE][BOARD_SIZE], char player) {
    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
    }
    
    // Check columns
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true;
        }
    }
    
    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }
    
    return false;
}

bool isBoardFull(const char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

bool isValidMove(const GameState* game) {
    // If it's not the first move and we have a required board,
    // check if we're playing in the correct board
    if (!game->first_move && 
        game->required_board_row != -1 && 
        (game->active_board_row != game->required_board_row || 
         game->active_board_col != game->required_board_col)) {
        return false;
    }

    // Check if the target board is not won/full
    if (game->big_board[game->active_board_row][game->active_board_col] != EMPTY) {
        return false;
    }

    // Check if the target cell is empty
    return game->small_boards[game->active_board_row][game->active_board_col]
                           [game->cursor_row][game->cursor_col] == EMPTY;
}


void updateActiveBoard(GameState* game) {
    int next_row = game->cursor_row;
    int next_col = game->cursor_col;
    
    if (game->big_board[next_row][next_col] != EMPTY) {
        game->active_board_row = -1;
        game->active_board_col = -1;
    } else {
        game->active_board_row = next_row;
        game->active_board_col = next_col;
    }
}

char getCurrentPlayer(const GameState* game) {
    return (game->current_player == 0) ? PLAYER_X : PLAYER_O;
}

bool isGameOver(const GameState* game) {
    if (checkWin(game->big_board, PLAYER_X) || checkWin(game->big_board, PLAYER_O)) {
        return true;
    }
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game->big_board[i][j] == EMPTY) {
                return false;
            }
        }
    }
    
    return true;
}

bool makeMove(GameState* game) {
    char symbol = getCurrentPlayer(game);
    game->small_boards[game->active_board_row][game->active_board_col]
                     [game->cursor_row][game->cursor_col] = symbol;
    
    if (checkWin(game->small_boards[game->active_board_row][game->active_board_col], symbol)) {
        game->big_board[game->active_board_row][game->active_board_col] = symbol;
    } else if (isBoardFull(game->small_boards[game->active_board_row][game->active_board_col])) {
        game->big_board[game->active_board_row][game->active_board_col] = 'T';
    }
    
    // The next player must play in the board corresponding to the current move's position
    game->required_board_row = game->cursor_row;
    game->required_board_col = game->cursor_col;
    
    // If that board is won/full, allow playing anywhere
    if (game->big_board[game->required_board_row][game->required_board_col] != EMPTY) {
        game->required_board_row = -1;
        game->required_board_col = -1;
    }
    
    game->current_player = 1 - game->current_player;
    game->first_move = false;
    
    if (isGameOver(game)) {
        return false;
    }
    
    return true;
}
