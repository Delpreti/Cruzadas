#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int index;
	char *value;
	int *left;
	int *right;
} abc;

//funcao chamada para adicionar uma palavra ao dicionario
void palavra_add(FILE *dic);