#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#include "cruzadas.h"

typedef struct {
	char digito;
	coord where;
} letra;

typedef struct {
	letra letras[30];	
} palavra;

palavra ativa;

//ativa.letras[0].digito;