#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int x;
	int y;
	int size;
} coord;

// Variavel global do posicionamento atual do cursor
coord active;

//Variaveis para as strings
coord inicio;
char *p_string;
int direcao;
int writing; //gamestate
int word_count;

int sair;

// Janelas fixas
WINDOW *game;
WINDOW *sidepanel;
WINDOW *panel_bottom;