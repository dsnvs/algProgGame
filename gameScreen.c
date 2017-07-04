
#include <ncurses.h>
#include <time.h>

typedef struct character {
    int x, y, width, height, xMax, yMax;
    char character;
    WINDOW *curwin;
} character;

void deletePlayer (character player) {
    mvwaddch(player.curwin, player.y, player.x, ' ');
    mvwaddch(player.curwin, player.y + 1, player.x, ' ');
    mvwaddch(player.curwin, player.y, player.x + 1, ' ');
    mvwaddch(player.curwin, player.y + 1, player.x + 1, ' ');
}

void createPlayer (character player) {
    mvwaddch(player.curwin, player.y, player.x, player.character);
    mvwaddch(player.curwin, player.y + 1, player.x, player.character);
    mvwaddch(player.curwin, player.y, player.x + 1, player.character);
    mvwaddch(player.curwin, player.y + 1, player.x + 1, player.character);
}

int checkChar (character player, WINDOW *game, char way) {
    char block;
    switch(way) {
        case 'u':
            block = mvwinch(game, player.y - 1, player.x);
            if (block == ' ')
                block = mvwinch(game, player.y - 1, player.x + 1);
        break;
        case 'd':
            block = mvwinch(game, player.y + 2, player.x);
            if (block == ' ')
                block = mvwinch(game, player.y + 2, player.x + 1);
        break;
        case 'l':
            block = mvwinch(game, player.y, player.x - 1);
            if (block == ' ')
                block = mvwinch(game, player.y + 1, player.x - 1);
        break;
        case 'r':
            block = mvwinch(game, player.y, player.x + 2);
            if (block == ' ')
                block = mvwinch(game, player.y + 1, player.x + 2);
        break;
    }
    return block;
}

void moveUp(character *player) {
    deletePlayer(*player);
    player->y--;
};

void moveDown(character *player) {
    deletePlayer(*player);
    player->y++;
};

void moveLeft(character *player) {
    deletePlayer(*player);
    player->x--;
};

void moveRight(character *player) {
    deletePlayer(*player);
    player->x++;
};

int movePlayer(character *player, WINDOW *game) {
    int option;
    char validMove;
    option = wgetch(player->curwin);
    switch (option) {
        case KEY_UP:
            validMove = checkChar(*player, game, 'u');
            if (validMove == ' ') {
                moveUp(player);
            } else if (validMove == '2') {

                moveUp(player);
            }
        break;
        case KEY_DOWN:
            validMove = checkChar(*player, game, 'd');
            if (validMove == ' ') {
                moveDown(player);
            }
        break;
        case KEY_LEFT:
            validMove = checkChar(*player, game, 'l');
            if (validMove == ' ') {
                moveLeft(player);
            }
        break;
        case KEY_RIGHT:
            validMove = checkChar(*player, game, 'r');
            if (validMove == ' ') {
                moveRight(player);
            }
        break;
        default:
        break;
    }
    createPlayer(*player);
    return option;
}

void startCurses() {
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

void startCharacter(character *player, WINDOW *gameWindow) {
    player->x = 1;
    player->y = 1;
    player->curwin = gameWindow;
    player->character = '+';
    getmaxyx(gameWindow, player->height, player->width);
}

void blockCreator(char letter, WINDOW *game) {
    int x, y;
    if (letter == '0') {
        letter = ' ';
    }
    getyx(game, y, x);
    waddch(game, letter);
    waddch(game, letter);
    mvwaddch(game, y + 1, x, letter);
    waddch(game, letter);
    wmove(game, y, x + 2);
}


void createLevel (int level, WINDOW *game, character *player) {
    FILE * textFile;
    char letter;
    int x, y;
    if (level == 3) {
        textFile = fopen("nivel1.txt", "r");
    } else if (level == 2) {
        textFile = fopen("nivel2.txt", "r");
    } else {
        textFile = fopen("nivel3.txt", "r");
    }
    if (textFile == NULL) {
        printf("erro na abertura do arquivo texto");
    } else {
        while (letter != EOF) {
            letter = fgetc(textFile);
            if (letter == 'x' || letter == '0' || letter == '2') {
                blockCreator(letter, game);
            } else if (letter == '\n') {
                getyx(game, y, x);
                wmove(game, y + 2, 0);
            } else if (letter == '1') {
                letter = player->character;
                getyx(game, player->y, player->x);
                blockCreator(letter, game);
            }
        }
    }
}

int main() {
    character player;
    startCurses();
    WINDOW * game = newwin(20, 50, 2, 2); // game window
    refresh();
    keypad(game, true);
    startCharacter(&player, game);
    createLevel(1, game, &player);
    while (movePlayer(&player, game) != 'x') {
        wrefresh(game);
    }
    endwin();
    return 0;
}
