#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "cruzadas.h"

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

void draw_border() {

	mvwaddch(game, mapa.bounds.upper, mapa.bounds.western, ACS_ULCORNER);
	mvwaddch(game, mapa.bounds.upper, mapa.bounds.eastern, ACS_URCORNER);
	mvwaddch(game, mapa.bounds.lower, mapa.bounds.western, ACS_LLCORNER);
	mvwaddch(game, mapa.bounds.lower, mapa.bounds.eastern, ACS_LRCORNER);

	for(int i = mapa.bounds.upper + 1; i < mapa.bounds.lower; i++) {
		mvwaddch(game, i, mapa.bounds.western, ACS_VLINE);
		mvwaddch(game, i, mapa.bounds.eastern, ACS_VLINE);
	}

	for(int j = mapa.bounds.western + 1; j < mapa.bounds.eastern; j++) {
		mvwaddch(game, mapa.bounds.upper, j, ACS_HLINE);
		mvwaddch(game, mapa.bounds.lower, j, ACS_HLINE);
	}

	wrefresh(game);
}