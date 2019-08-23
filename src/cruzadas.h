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

int sair;

// Janelas fixas
WINDOW *game;
WINDOW *sidepanel;