#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>

#ifndef HIGHSCORES_H
#define HIGHSCORES_H
typedef struct play { // Structure used to store and maintain the score of each game.
    char name[21];
    float score;
} play;

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

#endif
