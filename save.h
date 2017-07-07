#include "inGame.h"
#include <unistd.h>
#include <stdlib.h>

#ifndef SAVE_H
#define SAVE_H

void pauseGame(gameState save);
gameState unpauseGame();
void saveGame(gameState save);
void loadGame(gameState *save);
#endif
