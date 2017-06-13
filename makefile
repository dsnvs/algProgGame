all: game

game: newGame.c
	gcc newGame.c -lncurses -lm
