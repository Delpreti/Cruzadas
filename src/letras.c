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

letra mao[HANDSIZE];
int choices[HANDSIZE];
letra played[HANDSIZE];
int refill[HANDSIZE] = {0};

void letra_write(int choice){
	// Funcao que poe a letra no tabuleiro e tira a letra da mao
	void letra_add(){
		mvwaddch(game, active.y, active.x, mao[choice].digito);
		p_string[active.size] = mao[choice].digito;
		played[active.size].digito = mao[choice].digito;
		played[active.size].x = active.x;
		played[active.size].y = active.y;
		active.size++;
		if(direcao != 1){
			active.x++;
		} else if(direcao == 1){
			active.y++;
		}
		mvwprintw(panel_bottom, 5, choice*2 + 12, " ");
		wrefresh(panel_bottom);
	}

	// Condicoes para a direcao de escrita da palavra
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
	mvwprintw(panel_bottom, 2, 2, "Letras disponiveis:");
	wrefresh(panel_bottom);

	// Aguarda o usuario selecionar uma letra ou cancelar a jogada
	int choice;
	do{
		choice = wgetch(game);
		if(choice == 46){
			return;
		}
	}while((choice < 49  || choice > 56) || refill[choice - 49] != 0);
	choice -= 49;

	// Vetores que guardam a informacao da letra escolhida para uso futuro;
	choices[active.size] = choice;
	refill[choice] = 1;

	letra_write(choice);
}

// Funcao para corrigir o fato de que as letras nao sao equiprovaveis
char letra_random(){
	// Vetor que guarda a quantidade de cada letra
	int amounts[26] = {9, 3, 5, 3, 7, 3, 3, 2, 7, 2, 0, 4, 4, 3, 7, 3, 1, 4, 5, 3, 6, 3, 0, 1, 0, 1};
	int sum = 0, i = 0, count = 0;

	void iterate(){
		if(i >= amounts[count]){
			i = 0;
			count++;
		} else {
			i++;
			sum++;
		}
	}

	// Loop para calcular a soma das quantidades
	while(count < 26){
		iterate();
	}

	// Randomizacao
	int intervalo = rand() % sum;

	sum = 0, i = 0, count = 0;

	// Loop para destacar a letra randomizada
	while(sum < intervalo){
		iterate();
	}

	return (count + 97);
}

void letra_generate(int posicao){
	mao[posicao].digito = letra_random();
	mvwprintw(panel_bottom, 5, posicao*2 + 12, "%c", mao[posicao].digito);
	wrefresh(panel_bottom);
}

void mao_init(){
	for(int i = 0; i < HANDSIZE; i++){
		letra_generate(i);
		mvwprintw(panel_bottom, 6, i*2 + 12, "%d", i+1);
	}
	wrefresh(panel_bottom);
}

void mao_refill(){
	for(int i = 0; i <= HANDSIZE; i++){
		if(refill[i] == 1){
			letra_generate(i);
			refill[i] = 0;
		}
	}
	wrefresh(panel_bottom);
}