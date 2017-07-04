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

/*
    simple menu with do while loop for each option
*/

void menu() {
    char menuOption;
    scr_dump("temp.dump"); // dump current content of screen at a temporary file, in case player access highscore, but this will probably be removed to insert a new way of dealing with this issue
    do {
        menuOption = getch();
        switch(menuOption) {
            case 'N':
            case 'n':
                newGame();
                break;
            case 'S':
            case 's':
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
