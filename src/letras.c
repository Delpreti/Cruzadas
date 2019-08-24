#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#include "cruzadas.h"

#define HANDSIZE 8

typedef struct {
	char digito;
	int x;
	int y;
} letra;

typedef struct {
	letra letras[30];	
} palavra;

//palavra ativa;

letra mao[HANDSIZE];

int refill[HANDSIZE] = {0};

void letra_write(int choice){
	// Funcao que poe a letra no tabuleiro e tira a letra da mao
	void letra_add(){
		mvwaddch(game, active.y, active.x, mao[choice].digito);
		p_string[active.size] = mao[choice].digito;
		active.size++;
		if(direcao != 1){
			active.x++;
		} else if(direcao == 1){
			active.y++;
		}
		mvwprintw(panel_bottom, 5, choice*2 + 12, " ");
		wrefresh(panel_bottom);
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

void letra_select(){
	mvwprintw(panel_bottom, 2, 2, "Selecione uma letra:");
	wrefresh(panel_bottom);
	int choice;
	do{
		choice = wgetch(game);
	}while(choice < 49  || choice > 56);
	choice -= 49;
	refill[choice] = 1;

	letra_write(choice);
}

void letra_generate(letra mao[], int posicao){
	mao[posicao].digito = 97 + (rand() % 25);
	mvwprintw(panel_bottom, 5, posicao*2 + 12, "%c", mao[posicao].digito);
	wrefresh(panel_bottom);
}

void mao_init(){
	for(int i = 0; i < HANDSIZE; i++){
		letra_generate(mao, i);
		mvwprintw(panel_bottom, 6, i*2 + 12, "%d", i+1);
	}
	wrefresh(panel_bottom);
}

void mao_refill(){
	letra mao[HANDSIZE];
	for(int i = 0; i <= HANDSIZE; i++){
		if(refill[i] == 1){
			letra_generate(mao, i);
			refill[i] = 0;
		}
	}
	wrefresh(panel_bottom);
}