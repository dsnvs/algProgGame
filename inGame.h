#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

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
    character player;
    finalPosition positions[5];
    int level, found, timeSpent[3];
} gameState;

void deletePlayer (character player);
void createPlayer (character player);
int checkChar (int y, int x, WINDOW *game, char way);
void moveUp(gameState *save, WINDOW *game);
void moveDown(gameState *save, WINDOW *game);
void moveLeft(character *player);
void moveRight(character *player);
int movePlayer(gameState *save, WINDOW *game);
void startCharacter(character *player, WINDOW *gameWindow);
void blockCreator(char letter, WINDOW *game);
void createLevel (gameState *save);
void infoUpdate (WINDOW *info, float timeSpent, int foundPositions, int level);
gameState saveState(character *player, finalPosition positions[5], int level, int foundPositions, int timeSpent[3]);
void setWindow(WINDOW* game, gameState *save);

#endif
