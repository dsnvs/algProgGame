#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "highscores.h"

#ifndef INGAME_H
#define INGAME_H

typedef struct character {
    int y, x, width, height, xMax, yMax;
    char character;
    WINDOW *curwin;
} character;

typedef struct finalPosition {
    int x, y, found;
} finalPosition;

typedef struct gameState {
    char scenario[260];
    play score;
    character player;
    finalPosition positions[5];
    int level, found, timeSpent[3], movement;
} gameState;

void deletePlayer (character player);
void createPlayer (character player);
int checkChar (int y, int x, WINDOW *game, char way);
void moveUp(gameState *save, WINDOW *game);
void moveDown(gameState *save, WINDOW *game);
void moveLeft(gameState *save, WINDOW *game);
void moveRight(gameState *save, WINDOW *game);
int movePlayer(gameState *save, WINDOW *game);
void startCharacter(character *player, WINDOW *gameWindow);
void blockCreator(char letter, WINDOW *game);
void createLevel (gameState *save);
void infoUpdate (WINDOW *info, gameState *save);
gameState saveState(character *player, finalPosition positions[5], int level, int foundPositions, int timeSpent[3]);
void setWindow(WINDOW* game, gameState *save);
void newGame(gameState *save);
#endif
