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
    char fileName[100];
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
    do {
        stream = fopen(fileName, "r");
        if (stream != NULL) {
            fileName[i] = j;
            j++;
            putTxt(fileName, i + 1);
        }
    } while (stream != NULL);
    fclose(stream);
    stream = fopen(fileName, "w+");
    

}
