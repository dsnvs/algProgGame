#include "save.h"

void pauseGame(gameState save) {
    FILE *stream = fopen("pause.bin", "w+b");
    if (stream == NULL) {
        mvprintw(23, 3, "ERROR OPENING PAUSE.BIN");
        refresh();
    }
    fwrite(&save, sizeof(gameState), 1, stream);
    fclose(stream);
}

gameState unpauseGame() {
    gameState save;
    FILE *stream = fopen("pause.bin", "rb");
    if (stream == NULL) {
        mvprintw(23, 3, "ERROR OPENING PAUSE.BIN");
        refresh();
    }
    fread(&save, sizeof(gameState), 1, stream);
    fclose(stream);
    return save;
}
void putTxt(char *fileName, int i) {
    fileName[i] = '.';
    fileName[i + 1] = 't';
    fileName[i + 2] = 'x';
    fileName[i + 3] = 't';
}

void saveGame(gameState save) {
    FILE *stream;
    char fileName[100], jChar;
    int i, j = 1;
    mvprintw(23, 3, "Player name: ");
    refresh();
    echo();
    scanw("%s", fileName);
    noecho();
    move(23, 0);
    clrtoeol();
    i = strlen(fileName);
    putTxt(fileName, i);
    while (access(fileName, F_OK) != -1) {
        jChar = j + '0';
        fileName[i] = jChar;
        j++;
        putTxt(fileName, i + 1);
    }
    stream = fopen(fileName, "w+");
    if (stream == NULL) {
        mvprintw(23, 3, "ERROR OPENING TEXT FILE");
    } else {
        fprintf(stream, "%s,%s,%f,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i", save.scenario, save.score.name, save.score.score, save.positions[0].y, save.positions[0].found, save.positions[0].x, save.positions[1].y, save.positions[1].x, save.positions[1].found, save.positions[2].y, save.positions[2].x, save.positions[2].found, save.positions[3].y, save.positions[3].x, save.positions[3].found, save.positions[4].y, save.positions[4].x, save.positions[4].found, save.level, save.found, save.timeSpent[0], save.timeSpent[1], save.timeSpent[2], save.movement[0], save.movement[1], save.movement[2]);
    }
    fclose(stream);
}

void loadGame(gameState *save) {
    FILE *stream;
    char fileName[100];
    mvprintw(23, 3, "File name: ");
    refresh();
    echo();
    scanw("%s", fileName);
    noecho();
    move(23, 0);
    clrtoeol();
    stream = fopen(fileName, "r");
    if (stream == NULL) {
        mvprintw(23, 3, "ERROR OPENING TEXT FILE");
    } else {
        fscanf(stream, "%260[^,],%21[^,],%f,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i", save->scenario, save->score.name, &save->score.score, &save->positions[0].y, &save->positions[0].found, &save->positions[0].x, &save->positions[1].y, &save->positions[1].x, &save->positions[1].found, &save->positions[2].y, &save->positions[2].x, &save->positions[2].found, &save->positions[3].y, &save->positions[3].x, &save->positions[3].found, &save->positions[4].y, &save->positions[4].x, &save->positions[4].found, &save->level, &save->found, &save->timeSpent[0], &save->timeSpent[1], &save->timeSpent[2], &save->movement[0], &save->movement[1], &save->movement[2]);
        fclose(stream);
        refresh();
    }
}
