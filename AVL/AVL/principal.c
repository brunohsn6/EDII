#include <stdio.h>
#include "arvore.h"

int main(){
	ARV *raiz = NULL, *aux;
	int op, num, res;
	
	do{
		printf("1 - inserir\n2 - exibir\n3 - remover\n4 - sair\n digite a opcao: ");
		scanf("%d", &op);
		fflush(stdin);
		if (op == 1){
			printf("informe numero a ser inserido: ");
			scanf("%d", &num);
			fflush(stdin);
			inserir(&raiz, num);

		}
		if (op == 2){
			exibir(raiz);
		}
		if (op == 3){
			printf("Informe o valor a ser removido: ");
			scanf("%d", &num);
			fflush(stdin);
			res = remover(&raiz, num);
			if (res == -1){
				printf("Valor nao encontrado!\n");
			}
			else if (res == -2){
				printf("arvore vazia!\n");
			}
			else{
				printf("valor %d removido!\n", res);
			}
		}
		if (op == 4){
			printf("informe numero para busca: ");
			scanf("%d", &num);
			aux = buscarNo(raiz, num);
			if (aux != NULL){
				printf("%d", aux->info);
			}
		}
	} while (op != 5);
		
	return 0;
}