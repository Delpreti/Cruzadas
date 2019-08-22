#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#include "dicionario.h"

typedef struct {
	int x;
	int y;
	int size;
} coord;

//Variavel global do posicionamento atual do cursor
coord active;

int sair;

WINDOW *game;

// Funcao para verificar se uma ou mais teclas foram pressionadas
int key_pressed(int keyvar, int quant, ...) {
	va_list press;
	va_start(press, quant);
	for(int i = 0; i < quant; i++) {
		if(keyvar == va_arg(press, int)) {
			va_end(press);
			return 1;
		}
	}
	va_end(press);
	return 0;
}

int main(void){
	setlocale(LC_ALL, "");
	
	initscr();
	cbreak();
	noecho();
	curs_set(TRUE);
	set_escdelay(0);
	
	game = newwin(LINES, COLS, 0, 0);

	keypad(game, TRUE);
	srand(time(NULL));

	int maxy, maxx;
	getmaxyx(game, maxy, maxx);
	active.x = maxx/2;
	active.y = maxy/2;
	active.size = 0;
	sair = 0;

	while(!sair) {

		wmove(game, active.y, active.x);

		int tecla = wgetch(game);

		//Codigo que verifica a acao a ser tomada dependendo da tecla pressionada
		if(key_pressed(tecla, 1, KEY_UP)) {
			active.y--;
		} else if(key_pressed(tecla, 1, KEY_DOWN)) {
			active.y++;
		} else if(key_pressed(tecla, 1, KEY_LEFT)) {
			active.x--;
		} else if(key_pressed(tecla, 1, KEY_RIGHT)) {
			active.x++;
		} else if(key_pressed(tecla, 1, KEY_BACKSPACE)){
			//backspace e delete ambas bugadas, sobrescrever com barra de espaco
			active.x--;
			wmove(game, active.y, active.x);
			mvwaddch(game, active.y, active.x, ' ');
		} else if(key_pressed(tecla, 1, 27)) {
			sair = 1;
		} else {
			mvwaddch(game, active.y, active.x, tecla);
			active.x++;
			active.size++;
		}

		wrefresh(game);
	}
	endwin();

	return 0;
}