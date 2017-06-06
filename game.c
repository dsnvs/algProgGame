#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

void menu();
int newGame(char playerName[100]);
void topDisplay(WINDOW *gameWindow);


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
  int playerScore = -1;

  printw("Sokoban.");


  do {
    opcao = getch();
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
      case 'e':
      case 'E':
        printw("Buscando os recordes registrados...\n");
      break;
      case 'q':
      case 'Q':
        printw("Ateh mais!!\n");
      break;
      default:
        printw("Ops! Opcao invalida! \n");
    }
  } while(opcao!= 'q' && opcao!='Q');
}

int newGame(char playerName[100]) {
  WINDOW *gameWindow;
  int x, y;
  x = 20; // X should be starting position X, which will be determined by the level file
  y = 20; // Y should be starting position Y, which will be determined by the level file
  gameWindow = newwin(LINES, COLS, x, y);
  topDisplay(gameWindow);
  wrefresh(gameWindow);
  return 0;
}

void topDisplay(WINDOW *gameWindow) {
  box(gameWindow, 0, 0);
  printw("teste");
}
