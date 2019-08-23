#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#include "cruzadas.h"

#define HANDSIZE 9

typedef struct {
	char digito;
	int x;
	int y;
} letra;

typedef struct {
	letra letras[30];	
} palavra;

//palavra ativa;

void letra_generate(letra mao[], int posicao){
	mao[posicao].digito = 97 + (rand() % 25);
	mvwprintw(panel_bottom, 5, posicao*2 + 12, "%c", mao[posicao].digito);
	wrefresh(panel_bottom);
}

void mao_init(){
	letra mao[HANDSIZE];
	for(int i = 0; i < HANDSIZE; i++){
		letra_generate(mao, i);
	}
}