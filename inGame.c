#include "inGame.h"

void deletePlayer (character player) {
    mvwaddch(player.curwin, player.y, player.x, ' ');
    mvwaddch(player.curwin, player.y + 1, player.x, ' ');
    mvwaddch(player.curwin, player.y, player.x + 1, ' ');
    mvwaddch(player.curwin, player.y + 1, player.x + 1, ' ');
}

void moveBlock (WINDOW *game, int y, int x) {
    mvwaddch(game, y, x, '2');
    mvwaddch(game, y + 1, x, '2');
    mvwaddch(game, y, x + 1, '2');
    mvwaddch(game, y + 1, x + 1, '2');
}

void createPlayer (character player) {
    mvwaddch(player.curwin, player.y, player.x, player.character);
    mvwaddch(player.curwin, player.y + 1, player.x, player.character);
    mvwaddch(player.curwin, player.y, player.x + 1, player.character);
    mvwaddch(player.curwin, player.y + 1, player.x + 1, player.character);
}

int checkChar (int y, int x, WINDOW *game, char way) {
    char block;
    switch(way) {
        case 'u':
            block = mvwinch(game, y - 1, x);
            if (block == ' ')
                block = mvwinch(game, y - 1, x + 1);
        break;
        case 'd':
            block = mvwinch(game, y + 2, x);
            if (block == ' ')
                block = mvwinch(game, y + 2, x + 1);
        break;
        case 'l':
            block = mvwinch(game, y, x - 1);
            if (block == ' ')
                block = mvwinch(game, y + 1, x - 1);
        break;
        case 'r':
            block = mvwinch(game, y, x + 2);
            if (block == ' ')
                block = mvwinch(game, y + 1, x + 2);
        break;
    }
    return block;
}

void moveUp(character *player) {
    deletePlayer(*player);
    player->y -= 2;
};

void moveDown(character *player) {
    deletePlayer(*player);
    player->y += 2;
};

void moveLeft(character *player) {
    deletePlayer(*player);
    player->x -= 2;
};

void moveRight(character *player) {
    deletePlayer(*player);
    player->x += 2;
};


int randomPositionsGenerator(char *txt) {
    int randxy, aleatorios = 0;
    srand(time(NULL));
    for (int i = 0; i < 259; i++) {
        if (txt[i] == '2') {
            aleatorios++;
        }
    }
    for (int i = 0; i < aleatorios; i++) {
        do {
            randxy = rand() % 250;
        } while (txt[randxy] != '0');
        txt[randxy] = '*';
    }
    return aleatorios;
}

void foundPos (WINDOW *game,int y, int x) {
        mvwaddch(game, y, x, 'x');
        mvwaddch(game, y + 1, x, 'x');
        mvwaddch(game, y, x + 1, 'x');
        mvwaddch(game, y + 1, x + 1, 'x');
}

int movePlayer(character *player, WINDOW *game, finalPosition *positions, int level) {
    int option, x, y, encontrou = 0;
    char validMove;
    option = wgetch(player->curwin);
    switch (option) {
        case KEY_UP:
            validMove = checkChar(player->y, player->x, game, 'u');
            if (validMove == ' ') {
                moveUp(player);
            } else if (validMove == '2') {
                y = player->y - 4;
                x = player->x;
                validMove = checkChar(y + 2, x, game, 'u');
                if (validMove == ' ') {
                    moveBlock(game, y, x);
                    moveUp(player);
                }
                for (int i = 0; i < (level + 3); i++) {
                    if (positions[i].x == x && positions[i].y == y) {
                        foundPos(game, y, x);
                        encontrou++;
                    }
                }
            }
        break;
        case KEY_DOWN:
            validMove = checkChar(player->y, player->x, game, 'd');
            if (validMove == ' ') {
                moveDown(player);
            } else if (validMove == '2') {
                y = player->y + 4;
                x = player->x;
                validMove = checkChar(y + 2, x, game, 'u');
                if (validMove == ' ') {
                    moveBlock(game, y, x);
                    moveDown(player);
                }
                for (int i = 0; i < (level + 3); i++) {
                    if (positions[i].x == x && positions[i].y == y) {
                        foundPos(game, y, x);
                        encontrou++;
                    }
                }
            }
        break;
        case KEY_LEFT:
            validMove = checkChar(player->y, player->x, game, 'l');
            if (validMove == ' ') {
                moveLeft(player);
            } else if (validMove == '2') {
                y = player->y;
                x = player->x - 4;
                validMove = checkChar(y + 2, x, game, 'u');
                if (validMove == ' ') {
                    moveBlock(game, y, x);
                    moveLeft(player);
                }
                for (int i = 0; i < (level + 3); i++) {
                    if (positions[i].x == x && positions[i].y == y) {
                        foundPos(game, y, x);
                        encontrou++;
                    }
                }
            }
        break;
        case KEY_RIGHT:
            validMove = checkChar(player->y, player->x, game, 'r');
            if (validMove == ' ') {
                moveRight(player);
            } else if (validMove == '2') {
                y = player->y;
                x = player->x + 4;
                validMove = checkChar(y + 2, x, game, 'u');
                if (validMove == ' ') {
                    moveBlock(game, y, x);
                    moveRight(player);
                }
                for (int i = 0; i < (level + 3); i++) {
                    if (positions[i].x == x && positions[i].y == y) {
                        foundPos(game, y, x);
                        encontrou++;
                    }
                }
            }
        break;
        default:
        break;
    }
    createPlayer(*player);
    return encontrou;
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

void createLevel (int level, WINDOW *game, character *player, finalPosition *positions) {
    FILE * textFile;
    char txt[260];
    int x, y, arrayRunner = 0;
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
        for (int i = 0; i < 259; i++) {
            txt[i] = fgetc(textFile);
        }
        randomPositionsGenerator(txt);
        for (int i = 0; i < 259; i++) {
            if (txt[i] == 'x' || txt[i] == '0' || txt[i] == '2') {
                blockCreator(txt[i], game);
            } else if (txt[i] == '\n') {
                getyx(game, y, x);
                wmove(game, y + 2, 0);
            } else if (txt[i] == '1') {
                txt[i] = player->character;
                getyx(game, player->y, player->x);
                blockCreator(txt[i], game);
            } else if (txt[i] == '*') {
                getyx(game, positions[arrayRunner].y, positions[arrayRunner].x);
                arrayRunner++;
                blockCreator(' ', game);
            }
        }
    }
}

int newGame() {
    character player;
    int level = 1, posicoesEncontradas = 0;
    finalPosition positions[level + 3];
    WINDOW * game = newwin(20, 50, 2, 2); // game window
    WINDOW * info = newwin(20, 25, 2, 53); // actual game info window
    box(info, 0, 0);
    refresh();
    keypad(game, true);
    startCharacter(&player, game);
    createLevel(level, game, &player, positions);
    while (posicoesEncontradas < level + 3) {
        movePlayer(&player, game, positions, level);
        wrefresh(game);
    }
    return 0;
}

/*

MUDAR O checkChar PARA TRABALHAR COM X E Y, NÃO ESTRUTURA, CRIAR COLISAO PARA BLOCOS E CASO AS NOVAS COORDENADAS DO BLOCO SEJAM
IGUAIS A UMA POSICAO FINAL, TRANSFORMAR EM 0;

*/
