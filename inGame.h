#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#ifndef INGAME_H
#define INGAME_H

typedef struct character {
    int x, y, width, height, xMax, yMax;
    char character;
    WINDOW *curwin;
} character;

typedef struct finalPosition {
    int x, y;
} finalPosition;

void deletePlayer (character player);
void createPlayer (character player);
int checkChar (int y, int x, WINDOW *game, char way);
void moveUp(character *player);
void moveDown(character *player);
void moveLeft(character *player);
void moveRight(character *player);
int movePlayer(character *player, WINDOW *game, finalPosition *positions, int level);
void startCharacter(character *player, WINDOW *gameWindow);
void blockCreator(char letter, WINDOW *game);
void createLevel (int level, WINDOW *game, character *player, finalPosition *positions);
int newGame();

#endif
