#include <stdio.h>
#include <stdlib.h>

#include "cruzadas.h"

typedef struct {
	int index;
	char *value;
	int *left;
	int *right;
} abc;

void err_check(FILE *fp) {
	if (fp == NULL) {
       fprintf(stderr, "error opening file\n");
       exit(1);
	}
}

void palavra_add(FILE *dic){
	abc word;
	word.index = active.size;
	word.value = malloc(15*sizeof(char));
	word.left = NULL;
	word.right = NULL;
	printf("Escreva a palavra a ser adicionada ao dicionario:\n");
	fgets(word.value, 15, stdin);
	if(word.value[0] != ' ' && word.value[0] != '\n'){
		//Tira a quebra de linha do fgets
		int i = 0;
		for(i = 0; ; i++){
			if(word.value[i] == '\n'){
				word.value[i] = '\0';
				break;
			}
		}
		//Avanca o indice da palavra
		active.size++;
		//Guarda a palavra no arquivo
		fwrite(word.value, sizeof(char), i, dic);
		printf("Palavra %s adicionada!\n", word.value);
		free(word.value);
		return;
	}
	free(word.value);
	sair = 0;
}

//Inicializa um novo dicionario, usar com cautela
void dic_novo(){
	FILE *f = fopen("dicionario.bin", "wb");
	err_check(f);
	active.size = 0;
	//Necessario inserir uma palavra raiz
	palavra_add(f);
	fclose(f);
}

void palavra_delete(char* palavra){

}