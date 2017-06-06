#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

void menu();
int newGame(char playerName[100]);
void topDisplay(WINDOW *gameWindow);
