#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../include/game.h"

// Test helper functions
void print_test_result(const char* test_name, bool passed) {
    printf("%s: %s\n", test_name, passed ? "PASSED" : "FAILED");
}

void setup_game_state(GameState* game) {
    initializeGame(game);
}

// Test functions
void test_initialize_game() {
    GameState game;
    setup_game_state(&game);
    
    bool passed = true;
    passed &= (game.current_player == 0);
    passed &= (game.first_move == true);
    passed &= (game.active_board_row == 1);
    passed &= (game.active_board_col == 1);
    
    // Check all boards are empty
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            passed &= (game.big_board[i][j] == EMPTY);
            for (int k = 0; k < BOARD_SIZE; k++) {
                for (int l = 0; l < BOARD_SIZE; l++) {
                    passed &= (game.small_boards[i][j][k][l] == EMPTY);
                }
            }
        }
    }
    
    print_test_result("Initialize Game", passed);
}

void test_check_win_horizontal() {
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {'X', 'X', 'X'},
        {'O', 'O', ' '},
        {' ', ' ', ' '}
    };
    
    bool passed = true;
    passed &= checkWin(board, 'X') == true;
    passed &= checkWin(board, 'O') == false;
    
    print_test_result("Check Win Horizontal", passed);
}

void test_check_win_vertical() {
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {'X', 'O', ' '},
        {'X', 'O', ' '},
        {'X', ' ', ' '}
    };
    
    bool passed = true;
    passed &= checkWin(board, 'X') == true;
    passed &= checkWin(board, 'O') == false;
    
    print_test_result("Check Win Vertical", passed);
}

void test_check_win_diagonal() {
    char board1[BOARD_SIZE][BOARD_SIZE] = {
        {'X', 'O', ' '},
        {'O', 'X', ' '},
        {' ', ' ', 'X'}
    };
    
    char board2[BOARD_SIZE][BOARD_SIZE] = {
        {' ', 'O', 'X'},
        {'O', 'X', ' '},
        {'X', ' ', ' '}
    };
    
    bool passed = true;
    passed &= checkWin(board1, 'X') == true;
    passed &= checkWin(board1, 'O') == false;
    passed &= checkWin(board2, 'X') == true;
    passed &= checkWin(board2, 'O') == false;
    
    print_test_result("Check Win Diagonal", passed);
}

void test_board_full() {
    char full_board[BOARD_SIZE][BOARD_SIZE] = {
        {'X', 'O', 'X'},
        {'O', 'X', 'O'},
        {'O', 'X', 'O'}
    };
    
    char partial_board[BOARD_SIZE][BOARD_SIZE] = {
        {'X', 'O', 'X'},
        {'O', ' ', 'O'},
        {'O', 'X', 'O'}
    };
    
    bool passed = true;
    passed &= isBoardFull(full_board) == true;
    passed &= isBoardFull(partial_board) == false;
    
    print_test_result("Board Full Check", passed);
}

void test_valid_moves() {
    GameState game;
    setup_game_state(&game);
    
    bool passed = true;
    
    // First move should be valid anywhere
    passed &= isValidMove(&game) == true;
    
    // Make first move in center of center board
    game.small_boards[1][1][1][1] = 'X';
    game.first_move = false;
    game.current_player = 1;
    game.required_board_row = 1;  // Must play in center board
    game.required_board_col = 1;
    
    // Should be able to play in the required board
    game.active_board_row = 1;
    game.active_board_col = 1;
    game.cursor_row = 0;
    game.cursor_col = 0;
    passed &= isValidMove(&game) == true;
    
    // Should not be able to play in a different board
    game.active_board_row = 0;
    game.active_board_col = 0;
    passed &= isValidMove(&game) == false;
    
    // Should not be able to play in an already occupied cell
    game.active_board_row = 1;
    game.active_board_col = 1;
    game.cursor_row = 1;
    game.cursor_col = 1;
    passed &= isValidMove(&game) == false;
    
    print_test_result("Valid Moves", passed);
}

void test_current_player() {
    GameState game;
    setup_game_state(&game);
    
    bool passed = true;
    passed &= getCurrentPlayer(&game) == 'X';
    
    game.current_player = 1;
    passed &= getCurrentPlayer(&game) == 'O';
    
    print_test_result("Current Player", passed);
}

void test_game_over() {
    GameState game;
    setup_game_state(&game);
    
    bool passed = true;
    passed &= isGameOver(&game) == false;
    
    // Set up winning condition in big board
    for (int i = 0; i < BOARD_SIZE; i++) {
        game.big_board[0][i] = 'X';
    }
    
    passed &= isGameOver(&game) == true;
    
    print_test_result("Game Over", passed);
}

void test_make_move() {
    GameState game;
    setup_game_state(&game);
    
    bool passed = true;
    
    // Make first move
    game.active_board_row = 1;
    game.active_board_col = 1;
    game.cursor_row = 1;
    game.cursor_col = 1;
    
    passed &= makeMove(&game) == true;
    passed &= game.small_boards[1][1][1][1] == 'X';
    passed &= game.current_player == 1;
    passed &= game.first_move == false;
    
    print_test_result("Make Move", passed);
}

void test_update_active_board() {
    GameState game;
    setup_game_state(&game);
    
    bool passed = true;
    
    // Normal update
    game.cursor_row = 1;
    game.cursor_col = 2;
    updateActiveBoard(&game);
    passed &= game.active_board_row == 1;
    passed &= game.active_board_col == 2;
    
    // Update when target board is full
    game.big_board[1][2] = 'T';
    updateActiveBoard(&game);
    passed &= game.active_board_row == -1;
    passed &= game.active_board_col == -1;
    
    print_test_result("Update Active Board", passed);
}

int main() {
    printf("Running Ultimate Tic-tac-toe tests...\n\n");
    
    test_initialize_game();
    test_check_win_horizontal();
    test_check_win_vertical();
    test_check_win_diagonal();
    test_board_full();
    test_valid_moves();
    test_current_player();
    test_game_over();
    test_make_move();
    test_update_active_board();
    
    printf("\nAll tests completed.\n");
    return 0;
}
