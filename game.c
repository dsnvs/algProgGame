#include <stdlib.h>
#include <ncurses.h>
#include "highscores.h"
#include "inGame.h"
#include "save.h"

void game(gameState *save) {
    int move, remainingTime;
    clock_t initialTime;
    WINDOW * game = newwin(20, 50, 2, 2); // game window
    WINDOW * info = newwin(20, 25, 2, 53); // actual game info window
    nodelay(game, true);
    refresh();
    keypad(game, true);
    while (save->level <= 3) {
        if (save->level == 1) {
            remainingTime = 90;
        } else if (save->level == 2) {
            remainingTime = 60;
        } else if (save->level == 3) {
            remainingTime = 45;
        }
        initialTime = clock();
        startCharacter(&save->player, game);
        setWindow(game, save);
        wrefresh(game);
        wrefresh(info);
        box(info, 0, 0);
        infoUpdate(info, save);
        wrefresh(info);
        while (save->found < save->level + 2) {
            move = movePlayer(save, game);
            if (move == (int)'\t'){
                delwin(game);
                delwin(info);
                save->scenario[((save->player.y / 2) * 26) + save->player.x / 2] = '1';
                return;
            }
            if (((double)(clock() - initialTime) / CLOCKS_PER_SEC) > 1) {
                initialTime = clock();
                save->timeSpent[save->level - 1]++;
                remainingTime--;
            }
            infoUpdate(info, save);
            wrefresh(info);
        }
        wclear(info);
        save->level++;
        save->found = 0;
        createLevel(save);
    }
    werase(info);
    werase(game);
    delwin(game);
    delwin(info);
    save->score = transformToPlay (save->score.name, save->timeSpent[0] + save->timeSpent[1] + save->timeSpent[2], save->movement[0] + save->movement[1] + save->movement[2], save->level - 1);
    mvprintw(10, 15, "YOU WIN!!!!");
    mvprintw(11, 15, "%.2f POINTS!", save->score.score);
    refresh();
    return;
}

/*
    simple menu with do while loop for each option
*/

void menu() {
    char menuOption;
    gameState save;
    do {
        menuOption = getch();
        switch(menuOption) {
            case 'N':
            case 'n':
                newGame(&save);
                searchPlayer(&save.score);
                game(&save);
                break;
            case 'S':
            case 's':
                saveGame(save);
            break;
            case 'l':
            case 'L':
                loadGame(&save);
                game(&save);
            break;
            // I DON'T REALLY KNOW IF I'LL USE THIS P CASE;
            case 'P':
            case 'p':
                pauseGame(save);
                while (getch() != 'p');
                save = unpauseGame();
                break;
            case 'H':
            case 'h':
                showHighscores();
                refresh();
                break;
            case 'Q':
            case 'q':
                if (save.level == 3) {
                    save.score = transformToPlay (save.score.name, save.timeSpent[0] + save.timeSpent[1], save.movement[0] + save.movement[1], save.level - 1);
                } else if (save.level == 2) {
                    save.score = transformToPlay (save.score.name, save.timeSpent[0], save.movement[0], save.level - 1);
                }
                mvprintw(23, 1, "%f", save.score.score);
                appendPlay(save.score);
            break;
            case '\t':
                move(2, 0);
                clrtobot();
                game(&save);
            break;
            default:
            break;
        }
    } while(menuOption != 'q' && menuOption != 'Q');
}


int main() {
    initscr(); //initialize ncurses window
    cbreak(); // break program whenever we hit ctrl+c
    noecho(); // disable line buffering
    mvprintw(0, 11, "[N]ew game | [S]ave | [L]oad | [P]ause | [H]ighscore | [Q]uit");
    refresh(); // refresh ncurses window
    menu();
    endwin(); // end ncurses window
    return 0;
}
