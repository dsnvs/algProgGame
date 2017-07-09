#include <stdlib.h>
#include <ncurses.h>
#include "highscores.h"
#include "inGame.h"
#include "save.h"

void game(gameState *save) {
    int move, remainingTime;
    clock_t initialTime;
    WINDOW * game = newwin(20, 50, 2, 2);
    WINDOW * info = newwin(20, 25, 2, 53);
    nodelay(game, true);
    refresh();
    keypad(game, true);
    while (save->level <= 3) {
        if (save->level == 1)
            remainingTime = 90;
        else if (save->level == 2)
            remainingTime = 60;
        else if (save->level == 3)
            remainingTime = 45;
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
    appendPlay(save->score);
    mvprintw(10, 15, "YOU WIN!!!!");
    mvprintw(11, 15, "%.2f POINTS!", save->score.score);
    refresh();
    save->level = -1;
}

/*
    simple menu.
    loops until user type a key associated with one of the options;
*/


void menu() {
    char menuOption;
    gameState save;
    save.level = -1;
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
                addUnfinishedPlay(save);
            break;
            case '\t':
                if (save.level != -1) {
                    move(2, 0);
                    clrtobot();
                    game(&save);
                }
            break;
            default:
            break;
        }
    } while(menuOption != 'q' && menuOption != 'Q');
}


int main() {
    initscr(); // initializes ncurses screen
    cbreak(); // sets terminal to cbreak mode, a mode between raw and cooked which gives us instantly access to input, but still maintain some terminal processing features like ctrl+c.
    noecho(); // disables echoing of typed characters
    mvprintw(0, 11, "[N]ew game | [S]ave | [L]oad | [P]ause | [H]ighscore | [Q]uit");
    refresh();
    menu();
    endwin(); // end ncurses
    return 0;
}
