#include "game.h"

int main() {
  initscr();
  raw();
  noecho();
  keypad(stdscr, TRUE);
  menu();
  endwin();
}

void menu() {
  char opcao;
  char filename[100];
  char playerName[100];
  int playerScore = -1, x, y;

  mvprintw(LINES - 1, 0, "RANDOM SOKOBAN"); 
  mvprintw(0, (COLS - 48) / 2,"[N]ew game, [S]ave, [P]ause, [H]ighscore, [Q]uit"); //print centralized menu
  do {
    opcao = getch();
    getyx(stdscr, y, x);
    move(LINES - 1, 0);
    clrtoeol();
    switch(opcao) {
      case 'n':
      case 'N':
        printw("Iniciando um novo jogo!!\n");
        getstr(playerName);
        playerScore = newGame(playerName);
        if (playerScore == -1) {

        }
        printw("%d", playerScore);
      break;
      case 's':
      case 'S':
        printw("Digite o nome do arquivo com o jogo a carregar: ");
        echo();
        getstr(filename);
        printw("Carregando o jogo salvo no arquivo %s!\n", strcat(filename,".txt"));
        noecho();
      break;
      case 'p':
      case 'P':
        printw("Pausando jogo. Progresso salvo em arquivo pausa.bin.\n");
      break;
      case 'h':
      case 'H':
        printw("Buscando os recordes registrados...\n");
      break;
      case 'q':
      case 'Q':
        printw("Ateh mais!!\n");
      break;
      default:
        printw("Ops! Opcao invalida! \n");
    }
    move(y, x);
  } while(opcao!= 'q' && opcao!='Q');
}

int newGame(char playerName[100]) {
  WINDOW *gameWindow;
  int x, y;
  x = 20; // X should be starting position X, which will be determined by the level file
  y = 20; // Y should be starting position Y, which will be determined by the level file
  gameWindow = newwin(LINES, COLS, 0, 0);
  topDisplay(gameWindow);
  wrefresh(gameWindow);
  topDisplay(stdscr);
  return 0;
}

void topDisplay(WINDOW *gameWindow) {
  box(gameWindow, 20, 2);
  printw("teste");
}
