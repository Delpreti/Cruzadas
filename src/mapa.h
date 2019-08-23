#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int upper;
	int lower;
	int eastern;
	int western;
} boundary;

typedef struct {
	boundary bounds;
	int height;
	int width;
	int area;
} map;

// Regiao escrita
map mapa;
boundary jogada;

//Desenha as bordas atuais do mapa na tela
void draw_border();