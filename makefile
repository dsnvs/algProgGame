all: game

game: game.c
	gcc game.c inGame.c highscores.c -lncurses -lm -o game
