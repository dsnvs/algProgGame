#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

void menu();
char leOpcao();

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
  printw("Sokoban.");
  do {
    opcao = getch();
    switch(opcao) {
      case 'n':
      case 'N':
        printw("Iniciando um novo jogo!!\n");
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
