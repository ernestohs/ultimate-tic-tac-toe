CC = gcc
CFLAGS = -Wall -Wextra -I./include
DEPS = include/game.h include/ui.h
OBJ = src/game.o src/ui.o src/main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

game: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test: src/game.o tests/test_game.o
	$(CC) -o test_game $^ $(CFLAGS)
	./test_game

clean:
	rm -f src/*.o tests/*.o game test_game
