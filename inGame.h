#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#ifndef INGAME_H
#define INGAME_H

typedef struct character {
    int y, x, width, height, xMax, yMax;
    char character;
    WINDOW *curwin;
} character;

typedef struct finalPosition {
    int y, x, found;
} finalPosition;

typedef struct play {
    char name[21];
    float score;
} play;

typedef struct block {
    int y, x, blocked;
} block;

typedef struct gameState {
    char scenario[260];
    play score;
    character player;
    finalPosition positions[5];
    int level, found, timeSpent[3], movement[3], blocked;
} gameState;

/*
    Delete player from screen;
*/

void deletePlayer (character player);

/*
    Create player on screen;
*/

void createPlayer (character player);

/*
    Return the character positioned in the place passed to the function through argument.
*/

int checkChar (int y, int x, WINDOW *game, char way);

/*
    Move player up/down/left/right.
*/

void moveUp(gameState *save, WINDOW *game);
void moveDown(gameState *save, WINDOW *game);
void moveLeft(gameState *save, WINDOW *game);
void moveRight(gameState *save, WINDOW *game);

/*
    Receives input from terminal and moves player according to the input.
*/

int movePlayer(gameState *save, WINDOW *game);

/*
    Initializes a character struct
*/

void startCharacter(character *player, WINDOW *gameWindow);

/*
    Create a 2x2 block with the letter passed through argument exactly where the cursor is pointed.
*/

void blockCreator(char letter, WINDOW *game);

/*
    Reads a new level from text files, randomize the box's final positions, and store the level on the gameState.
*/

void createLevel (gameState *save);

/*
    Updates on-screen information about the play according to the arguments.
*/

void infoUpdate (WINDOW *info, gameState *save);

/*
    Reads level from gameState and draws it on window;
*/

void setWindow(WINDOW* game, gameState *save);

/*
    Initializes a gameState struct.
*/

void newGame(gameState *save);

/*
    Check if moved block got stuck on the walls.
*/

int gotBlock(int y, int x, WINDOW *game);
#endif
