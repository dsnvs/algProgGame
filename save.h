#include "inGame.h"
#include <unistd.h>
#include <stdlib.h>

#ifndef SAVE_H
#define SAVE_H

/*
    pauseGame() takes a gameState struct as an argument and writes the content of the struct in a binary file named pause.bin.
    If the file already exists, overwrite the content in it.
    If the file doesn't exists, creates the file and write on it.
    pauseGame() prints an error message if the function have trouble opening/creating pause.bin.
*/

void pauseGame(gameState save);

/*
    unpauseGame() opens a pause.bin file and save the file content in a struct which is returned at the end of the function.
    unpauseGame() prints an error message if the function have trouble opening pause.bin.
*/

gameState unpauseGame();

/*
    saveGame() reads the player name, create a text file with the player name and save the  content of the struct passed as argument.
    if a file with the given name already exists, create puts a number before the ".txt".
    saveGame() prints an error message if the function have trouble opening/creating the text file.
*/

void saveGame(gameState save);

/*
    loadGame() reads a file name, open it and read the file content, saving it on the struct pointer passed through argument.
    loadGame() prints an error message if the file doesn't exists or function have any trouble reading it.
*/

void loadGame(gameState *save);


#endif
