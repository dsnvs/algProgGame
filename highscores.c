#include "highscores.h"

struct play transformToPlay (char name[21], int timeSpent, int moves, int completeLevels) {
    struct play temporary;
    strcpy(temporary.name, name);
    temporary.score = (pow(10, 3) * pow(completeLevels, 3) / (moves + (timeSpent / 2)));
    return temporary;
}

void appendPlay (struct play temporary) {
    FILE *binaryFile = fopen("scores.bin", "ab");
    if (binaryFile == NULL) {
        mvprintw(23, 3, "Unable to save.");
    } else {
        fwrite(&temporary, sizeof(struct play), 1, binaryFile);
        fclose(binaryFile);
    }
}


int searchPlayer(struct play *player) {
    play score;
    int found = -1;
    FILE *binaryFile = fopen("scores.bin", "rb");
    if (binaryFile == NULL) {
        mvprintw(23, 3, "Unable to open scores.bin");
    } else {
        do {
            fread(&score, sizeof(struct play), 1, binaryFile);
        } while (strcmp(player->name, score.name) != 0 && !feof(binaryFile));
        if (strcmp(player->name, score.name) == 0) {
            player->score = score.score;
            found = 0;
        }
        fclose(binaryFile);
    }
    return found;
}

void bubbleSort(struct play* array, int i) {
    struct play x;
    for (int j = 0; j < i; j++) {
        for (int k = 0; k < (i - 1); k++) {
            if (array[k].score < array[k + 1].score) {
                x = array[k];
                array[k] = array[k + 1];
                array[k + 1] = x;
            }
        }
    }
}

void showHighscores() {
    char bufferString[80];
    int numberOfScores;
    play *scores;
    FILE *binFile = fopen("scores.bin", "rb");
    WINDOW *highscore = newwin(20, 76, 2, 2);
    box(highscore, 0, 0);
    if (binFile == NULL) {
        printw("Unable to load scores.bin.");
    }
    fseek(binFile, 0L, SEEK_END);
    numberOfScores = ftell(binFile) / sizeof(struct play);
    if (numberOfScores == 0) {
        printw("There aren't any highscores stored in scores.bin");
    } else {
        rewind(binFile);
        scores = malloc(sizeof(play) * numberOfScores);
        fread(scores, sizeof(struct play), numberOfScores, binFile);
        bubbleSort(scores, numberOfScores);
        mvwprintw(highscore, 2, 33, "Highscore");
        for (int y = 0; y < 10; y++) {
            snprintf(bufferString, 80, "Name: %s  Score: %f", scores[y].name, scores[y].score); // Prepare the string to be printed
            mvwprintw(highscore, 4 + y, (76 - strlen(bufferString)) / 2, "%s", bufferString); // Centralizes string before printing
        }
        free(scores);
    }
    fclose(binFile);
    wrefresh(highscore);
    delwin(highscore);
}

void addUnfinishedPlay(gameState *save) {
    if (save->level == 3) {
        save->score = transformToPlay (save->score.name, save->timeSpent[0] + save->timeSpent[1], save->movement[0] + save->movement[1], save->level - 1);
    } else if (save->level == 2) {
        save->score = transformToPlay (save->score.name, save->timeSpent[0], save->movement[0], save->level - 1);
    }
    if (save->level == 3 || save->level == 2)
        appendPlay(save->score);
}
