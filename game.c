#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "highscores.h"
#include "inGame.h"

void startNcurses() {
    initscr(); //initialize ncurses window
    cbreak(); // break program whenever we hit ctrl+c
    noecho(); // disable line buffering
    if (has_colors() && can_change_color()) { // checks if termianl supports colors, and supports personalized colors
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK); // creates pair of colors
        init_pair(2, COLOR_BLUE, COLOR_BLACK);
        attron(COLOR_PAIR(1)); // turn's on pair of color number 1
        mvprintw(22, 3, "TEST");
        attroff(COLOR_PAIR(1)); // turn pair off
    } else {
        mvprintw(22, 3, "Terminal doesn't fully or partially support colors;");
    }
}

void newGame(gameState *save) {
    character player;
    save->level = 1;
    save->found = 0;
    for (int i = 0; i < 3; i++)
        save->timeSpent[i] = 0;
    createLevel(save);
    save->player = player;
}
/*
    character player = *save.player;
    int foundPositions = save.found, level = save.level, move;
    int timeSpent[3];
    for (int i = 0; i < level; i++)
        timeSpent[i] = save.timeSpent[i];
    clock_t initialTime;
    finalPosition positions[5];
    for (int i = 0; i < level + 2; i++)
        positions[i] = save.positions[i];
*/

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
        infoUpdate(info, save->timeSpent[save->level], save->found, save->level);
        while (save->found < save->level + 2) {
            move = movePlayer(save, game);
            if (move == (int)'p'){
                delwin(game);
                delwin(info);
                mvwprintw(stdscr, 22, 3, "y: %d x: %d formula: %d", save->player.y, save->player.x, ((save->player.y / 2) * 24) + save->player.x / 2);
                save->scenario[((save->player.y / 2) * 26) + save->player.x / 2] = '1';
                return;
            }
            wrefresh(game);
            save->timeSpent[save->level] = (double)(clock() - initialTime) / CLOCKS_PER_SEC;
            refresh();
            infoUpdate(info, save->timeSpent[save->level], save->found, save->level);
        }
        save->level++;
        save->found = 0;
        createLevel(save);
    }
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
                game(&save);
                break;
            // I DON'T REALLY KNOW IF I'LL USE THIS P CASE;
            case 'P':
            case 'p':
                //pausegame();
                break;
            case 'E':
            case 'e':
                showHighscores();
                scr_restore("temp.dump"); // restores screen from other dump;
                refresh();
                break;
            default:
                break;
        }
    } while(menuOption != 'q' && menuOption != 'Q');
}


int main() {
    startNcurses();
    mvprintw(0, 11, "[N]ovo jogo | [S]alvar | [P]ausar | [E]score | [Q]uit");
    refresh(); // refresh ncurses window
    menu();
    endwin(); // end ncurses window
    return 0;
}
