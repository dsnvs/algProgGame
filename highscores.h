#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "inGame.h"


#ifndef HIGHSCORES_H
#define HIGHSCORES_H

/*
    transformToPlay receives player input and his data after a match, transforms it to a struct of type play and returns it;
*/

struct play transformToPlay (char name[21], int timeSpent, int moves, int completeLevels);

/*
    appendPlay receives a struct of type play and append it to the binary highscores file.
*/

void appendPlay (struct play temporary);

/*
    Simple bubble sort implementation used to sort the scores loaded from the binary file.
*/

void bubbleSort(struct play* array, int i);

/*
    showHighscores reads all the data from the binaryfile, sort the data and display it.
*/

void showHighscores();

/*
    Search scores.bin for the highest score with same play.name than the pointer passed by reference,
    after finding it, saves the score to the player->score.
    returns 0 if find a score, and -1 if not.
    also return -1 if can't open scores.bin.
*/

int searchPlayer(struct play *player);

/*
    If gameState.level is 2 or 3,
    uses a gameState passed through reference to create a score struct and appends it to the end of the file;
*/

void addUnfinishedPlay(gameState *save);

#endif
