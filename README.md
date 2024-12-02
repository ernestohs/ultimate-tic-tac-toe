# Ultimate Tic-tac-toe

A terminal-based implementation of Ultimate Tic-tac-toe in C.

## Game Rules

Ultimate Tic-tac-toe is played on a 3×3 grid of 3×3 Tic-tac-toe boards. Players take turns playing in the smaller boards, but with a twist: the position of each move determines which board the next player must play in.

### Basic Rules
- Players take turns placing their mark (X or O) in one of the small boards
- To win a small board, get three marks in a row (horizontally, vertically, or diagonally)
- Win the game by winning three small boards in a row
- Your move determines which board your opponent must play in next
- If directed to a board that is full or won, the opponent can play in any board

## Building and Running

### Prerequisites
- GCC compiler
- Make
- Unix-like environment (Linux, macOS, WSL)

### Build
```bash
make
```

### Run
```bash
./game
```

### Run Tests
```bash
make test
```

### Clean
```bash
make clean
```

## Controls
- WASD or Arrow keys: Move cursor
- Enter: Place mark
- ESC: Quit game

## Project Structure
```
.
├── include/         # Header files
│   ├── game.h      # Game logic declarations
│   └── ui.h        # UI-related declarations
├── src/            # Source files
│   ├── game.c      # Game logic implementation
│   ├── ui.c        # UI implementation
│   └── main.c      # Main program
└── tests/          # Test files
    └── test_game.c # Game logic tests
```
