#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ncurses.h>
#include <time.h>

struct play { // Structure used to store and maintain the score of each game.
    char name[21];
    float score;
};

/*
    transformToPlay receives player input and his data after a match, transforms it to a struct of type play and returns it;
*/

struct play transformToPlay (char name[21], int timeSpent, int moves, int completeLevels) {
    struct play temporary;
    strcpy(name, temporary.name);
    temporary.score = (pow(10, 3) * pow(completeLevels, 3) / (moves + (timeSpent / 2))); // Calculating player score;
    return temporary;
}

/*
    appendPlay receives a struct of type play and append it to the binary highscores file.
*/

void appendPlay (struct play temporary) {
    FILE *binaryFile = fopen("scores.bin", "ab");
    if (binaryFile == NULL) {
        printw("Unable to save.");
    }
    fwrite(&temporary, sizeof(struct play), 1, binaryFile);
}

/*
    showHighscores reads all the data from the binaryfile, sort the data and display it.
*/

void showHighscores() {
    FILE *binaryFileRead = fopen("scores.bin", "r");
    if (binaryFileRead == NULL) {
        printw("Unable to load.");
    }
    int i = sizeof(*binaryFileRead) / sizeof(struct play);
    struct play scores[i];
    fread(scores, sizeof(struct play), sizeof(binaryFileRead), binaryFileRead);
    for (int x = 0; (x < 10) && (x < i); x++) {
        printw("%s %.1f", scores[x].name, scores[x].score);
    }
}

int main() {
    char name[21];
    scanf("%s", name);
    srand(time(NULL));
    int x, y, z;
    x = (rand() % 200);
    y = (rand() % 200);
    z = (rand() % 200);
    appendPlay(transformToPlay(name, x, y, z));
    showHighscores();
    return 0;
}
