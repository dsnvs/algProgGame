#include <stdlib.h>
#include <ncurses.h>
#include "highscores.h"
#include "inGame.h"
#include "save.h"

void game(gameState *save) {
    int move;
    clock_t initialTime;
    WINDOW * game = newwin(20, 50, 2, 2); // game window
    WINDOW * info = newwin(20, 25, 2, 53); // actual game info window
    nodelay(game, true);
    box(info, 0, 0);
    refresh();
    keypad(game, true);
    while (save->level <= 3) {
        initialTime = clock();
        startCharacter(&save->player, game);
        setWindow(game, save);
        wrefresh(game);
        infoUpdate(info, save);
        while (save->found < save->level + 2) {
            move = movePlayer(save, game);
            if (move == (int)'\t'){
                delwin(game);
                delwin(info);
                save->scenario[((save->player.y / 2) * 26) + save->player.x / 2] = '1';
                return;
            }
            wrefresh(game);
            if (((double)(clock() - initialTime) / CLOCKS_PER_SEC) > 1) {
                initialTime = clock();
                save->timeSpent[save->level]++;
            }
            refresh();
            infoUpdate(info, save);
        }
        save->level++;
        save->found = 0;
        createLevel(save);
    }
    werase(info);
    werase(game);
    delwin(game);
    delwin(info);
    mvwprintw(stdscr, 15, 3, "PLAYER NAME: ");
    wrefresh(stdscr);
    echo();
    scanw("%s", save->score.name);
    noecho();
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
                game(&save);
                break;
            case 'S':
            case 's':
                break;
            // I DON'T REALLY KNOW IF I'LL USE THIS P CASE;
            case 'P':
            case 'p':
                pauseGame(save);
                while (getch() != 'p');
                save = unpauseGame();
                break;
            case 'E':
            case 'e':
                showHighscores();
                refresh();
                break;
            case 'Q':
            case 'q':
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
    mvprintw(0, 11, "[N]ovo jogo | [S]alvar | [P]ausar | [E]score | [Q]uit");
    refresh(); // refresh ncurses window
    menu();
    endwin(); // end ncurses window
    return 0;
}
