#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "../include/ui.h"

static struct termios orig_termios;

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

char getChar() {
    char c;
    read(STDIN_FILENO, &c, 1);
    return c;
}

void drawBoard(const GameState* game) {
    printf("\033[2J\033[H");
    
    printf("   ");
    for (int i = 0; i < BOARD_SIZE * 3; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (int big_row = 0; big_row < BOARD_SIZE; big_row++) {
        for (int small_row = 0; small_row < BOARD_SIZE; small_row++) {
            printf("%2d ", big_row * 3 + small_row);
            
            for (int big_col = 0; big_col < BOARD_SIZE; big_col++) {
                for (int small_col = 0; small_col < BOARD_SIZE; small_col++) {
                    char symbol = game->small_boards[big_row][big_col][small_row][small_col];
                    
                    if (big_row == game->active_board_row && big_col == game->active_board_col &&
                        small_row == game->cursor_row && small_col == game->cursor_col) {
                        printf("\033[7m%c\033[0m", symbol);
                    } else if (big_row == game->active_board_row && big_col == game->active_board_col) {
                        printf("\033[1m%c\033[0m", symbol);
                    } else {
                        printf("%c", symbol);
                    }
                    printf(" ");
                }
                
                if (big_col < BOARD_SIZE - 1) printf("│");
            }
            printf("\n");
        }
        
        if (big_row < BOARD_SIZE - 1) {
            printf("   ");
            for (int i = 0; i < BOARD_SIZE * 11 - 1; i++) printf("─");
            printf("\n");
        }
    }
    
    printf("\nCurrent Player: %c\n", getCurrentPlayer(game));
    if (!game->first_move) {
        printf("Active Board: (%d,%d)\n", game->active_board_row, game->active_board_col);
    } else {
        printf("First move - play anywhere!\n");
    }
    printf("\nControls: WASD to move, Enter to place, ESC to quit\n");
}

bool handleQuit() {
    printf("\nDo you want to quit? (y/n): ");
    char response = getChar();
    return (response == 'y' || response == 'Y');
}

bool handleInput(GameState* game) {
    char c = getChar();
    
    if (c == KEY_ESC) {
        return handleQuit();
    }
    
    switch (c) {
        case KEY_W:
            if (game->cursor_row > 0) game->cursor_row--;
            break;
            
        case KEY_S:
            if (game->cursor_row < BOARD_SIZE - 1) game->cursor_row++;
            break;
            
        case KEY_A:
            if (game->cursor_col > 0) game->cursor_col--;
            break;
            
        case KEY_D:
            if (game->cursor_col < BOARD_SIZE - 1) game->cursor_col++;
            break;
            
        case KEY_ENTER:
            if (isValidMove(game)) {
                return makeMove(game);
            }
            break;
    }
    return true;
}
