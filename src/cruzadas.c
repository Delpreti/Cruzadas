#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#include "dicionario.h"
#include "mapa.h"
#include "letras.h"

typedef struct {
	int x;
	int y;
	int size;
} coord;

//Variavel global do posicionamento atual do cursor
coord active;

int sair;

//Variaveis para as strings
coord inicio;
char *p_string;
int direcao;
int writing; //gamestate
int word_count;

int score; //Placar atual do jogo

WINDOW *game;
WINDOW *sidepanel;
WINDOW *panel_bottom;

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

void draw_line(int lin, int col) {
	for(int i = 0; i < lin; i++) {
		mvwaddch(sidepanel, i, 0, ACS_VLINE);
	}
	wrefresh(sidepanel);
	for(int j = 0; j <= col; j++) {
		mvwaddch(panel_bottom, 0, j, ACS_HLINE);
	}
	wrefresh(panel_bottom);
}

void palavra_init(){
	writing = 1; // True

	// Inicializa o tamanho da palavra
	active.size = 0;

	// Guarda a posicao inicial da primeira letra
	inicio.x = active.x;
	inicio.y = active.y;

	jogada.upper = inicio.y - 1;
	jogada.western = inicio.x - 1;

	// reserva espaco para guardar a palavra
	p_string = malloc(30*sizeof(char));

	// direcao qualquer ainda nao definida
	direcao = -1;
}

void palavra_write(char letra){
	if(writing == 0){
		return;
	}
	void letra_add(){
		mvwaddch(game, active.y, active.x, letra);
		if(letra >= 97 && letra <= 122){
			p_string[active.size] = letra;
		}
		active.size++;
		if(direcao != 1){
			active.x++;
		} else if(direcao == 1){
			active.y++;
		}
	}
	if(active.size == 0){
		letra_add();
	} else {
		if(inicio.x == active.x && direcao != 0){ //letra escrita na vertical
			letra_add();
			direcao = 1;
		}
		if(inicio.y == active.y && direcao != 1){ //letra escrita na horizontal
			letra_add();
			direcao = 0;
		}
	}
}

void palavra_end(){
	if(direcao == 0){
		jogada.lower = active.y + 1;
		jogada.eastern = active.x;
	} else if(direcao == 1){
		jogada.lower = active.y;
		jogada.eastern = active.x + 1;
	}
	if(word_count == 0){
		mapa.bounds = jogada;
		mapa.height = mapa.bounds.lower - mapa.bounds.upper;
		mapa.width = mapa.bounds.eastern - mapa.bounds.western;
		mapa.area = (mapa.width - 1) * (mapa.height - 1);
	}
	draw_border();

	dic_check();
	for(int k = 0; k < active.size; k++){
		mvwprintw(sidepanel, word_count+5, k+2, "%c", p_string[k]);
	}
	word_count++;
	score += active.size;
	mvwprintw(sidepanel, 1, 2, "Score: %d", score);
	mvwprintw(sidepanel, 2, 2, "Area: %d", mapa.area);
	mvwprintw(sidepanel, 3, 2, "palavras: %d", word_count);
	wrefresh(sidepanel);
	free(p_string);
	writing = 0; //false
}

int main(void){
	setlocale(LC_ALL, "");
	
	initscr();
	cbreak();
	noecho();
	curs_set(TRUE);
	set_escdelay(0);
	
	int linhas = LINES;
	int colunas = COLS;

	game = newwin(linhas*0.8, colunas*0.8, 0, 0);
	sidepanel = newwin(linhas, colunas*0.2, 0, colunas*0.8);
	panel_bottom = newwin(linhas*0.2, colunas*0.8, linhas*0.8, 0);
	draw_line(linhas, colunas);

	keypad(game, TRUE);
	srand(time(NULL));

	int maxy, maxx;
	getmaxyx(game, maxy, maxx);
	active.x = maxx/2;
	active.y = maxy/2;
	active.size = 0;
	sair = 0;
	writing = 0; //false
	word_count = 0;
	score = 0;

	mao_init();

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
		} else if(key_pressed(tecla, 1, 27)) { //Esc
			sair = 1;
		} else if(tecla == 46) { //Ponto
			if(writing == 1){
				palavra_end();
			} else if(writing == 0){
				palavra_init();
			}
		} else {
			palavra_write(tecla);
		}
		wrefresh(game);
	}
	// Finaliza o jogo
	endwin();
	return 0;
}