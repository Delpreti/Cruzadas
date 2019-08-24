#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

typedef struct {
	char digito;
	int x;
	int y;
} letra;

typedef struct {
	letra letras[30];	
} palavra;

// Permite ao usuario selecionar uma letra da mao
void letra_select();

// Gera uma letra na mao do jogador
void letra_generate(letra mao[], int posicao);

// Inicializa a mao do jogador
void mao_init();

// Repoe as letras que sairam da mao
void mao_refill();