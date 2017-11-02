#include <stdio.h>
#include "arvore.h"


int alturaR(ARV *raiz){
	if (raiz == NULL){
		return 0;
	}
	else{
		int qtdE = alturaR(raiz->esq);
		int qtdD = alturaR(raiz->dir);
		if (qtdE < qtdD){
			return qtdD + 1;
		}
		else{
			return qtdE + 1;
		}
	}
}
int fator_balanceamento(ARV *raiz){
	if (raiz == NULL){
		return 0;
	}
	else{
		int qtdE = alturaR(raiz->esq);
		int qtdD = alturaR(raiz->dir);
		return qtdE - qtdD;
	}
}

ARV* criarNo(int num){
	ARV *no;
	no = (ARV*)malloc(sizeof(ARV));
	no->dir = NULL;
	no->esq = NULL;
	no->fb = 0;
	no->info = num;
	return no;
}

ARV * buscaR(ARV *raiz, int num){
	if (raiz != NULL){
		if (num == raiz->info){
			//se a raiz for o valor procurado
			return raiz;
		}
		if (raiz->esq != NULL){
			if (num == raiz->esq->info){
				//retorna o pai
				return raiz;
			}
		}
		else if (raiz->dir != NULL){
			if (num == raiz->dir->info){
				//retorna o pai
				return raiz;
			}	
		}
		else{
			//caso o valor procurado não conste no cadastro
			return NULL;
		}
		buscaR(raiz->esq, num);
		buscaR(raiz->dir, num);
	}
	return NULL;
}

void LSE(ARV **no){
	ARV *aux = (*no)->dir;
	(*no)->dir = aux->esq;
	aux->esq = *no;
	*no = aux;
}

void LSD(ARV **no){
	ARV *aux = (*no)->esq;
	(*no)->esq = aux->esq;
	aux->esq = *no;
	*no = aux;
}

void RL(ARV **no){
	LSD(&(*no)->dir);
	LSE(&(*no));
}

void LR(ARV **no){
	LSE(&(*no)->esq);
	LSD(&(*no));
}

void calcula_balanceamento(ARV **raiz){
	if (*raiz == NULL){
		return;
	}
	else{
		if ((*raiz)->fb == -2){
			if ((*raiz)->dir->fb == 1){
				RL(&(*raiz));
			}
			else{
				LSE(&(*raiz));
			}
			(*raiz)->fb = fator_balanceamento(*raiz);

		}
		if ((*raiz)->fb ==2){
			if ((*raiz)->esq->fb == -1){
				LR(&(*raiz));
			}
			else{
				LSD(&(*raiz));
			}
			(*raiz)->fb = fator_balanceamento(*raiz);
		}

		calcula_balanceamento(&(*raiz)->esq);
		calcula_balanceamento(&(*raiz)->dir);
	}
}

//inserir

void inserir(ARV **raiz, int num){
	if (*raiz == NULL){
		*raiz = criarNo(num);
		printf("numero %d inserido com sucesso!\n", num);
	}
	else{
		if (num < (*raiz)->info){
			inserir(&(*raiz)->esq, num);
			calcula_balanceamento(&(*raiz));
		}
		else{
			inserir(&(*raiz)->dir, num);
			calcula_balanceamento(&(*raiz));
		}
		
	}
	//Após inserir nó, recalcula o balanceamento e se necessário, balancea.
	


}

//remover

void exibir(ARV *raiz){
	if (raiz != NULL){
		exibir(raiz->esq);
		printf("%d ", raiz->info);
		exibir(raiz->dir);
	}
}
ARV * menor(ARV *raiz){
	if (raiz->esq != NULL){
		menor(raiz);
	}
	return raiz;
}

int remover(ARV **raiz, int num){
	ARV *aux, *del, *pos;
	printf("entra aq\n");
	aux = buscaR(*raiz, num);
	printf("sai aq \n");
	if (aux != NULL){
		printf("aq?\n");
		if (num == aux->info){//a raiz é o valor procurado.
			if (aux->esq == NULL && aux->dir == NULL){ //unico indice da arvore
				free(*raiz);
				*raiz = NULL;
			}
			else{
				if (aux->esq == NULL){//só tem filho no ramo à direita
					*raiz = aux->dir;
					free(*aux);
				}
				if (aux->dir == NULL){//só tem filho no ramo à esquerda
					*raiz = aux->esq;
					free(*aux);
				}
				else{//tem filho nos dois ramos
					pos = menor(aux->dir);
					pos->esq = aux->esq;
					free(*raiz);
					*raiz = aux;

				}
				calcula_balanceamento(&(*raiz));
			}
			return num;
			
		}
		else if (num == aux->esq->info){//o numero a ser removido é o número à esquerda da raiz
			del = aux->esq;
			if (del->esq == NULL && del->dir == NULL){
				free(*del);
				aux->esq = NULL;
			}
			if (del->esq == NULL){//só tem filho no ramo à direita
				aux->esq = del->dir;
				free(del);
			}
			if (del->dir == NULL){//só tem filho no ramo à esquerda
				aux->esq = del->esq;
				free(del);
			}
			else{//tem filho nos dois ramos
				pos = menor(del->dir);
				pos = del->esq;
				aux->esq = del->dir;
				free(del);
			}
			calcula_balanceamento(&(*raiz));
			return num;
		}
		else if (num == aux->dir->info){//o numero a ser removido é o número à direita da raiz
			del = aux->dir;
			if (del->esq == NULL && del->dir == NULL){
				free(*del);
				aux->dir = NULL;
			}
			if (del->esq == NULL){//só tem filho no ramo à direita
				aux->dir = del->dir;
				free(del);
			}
			if (del->dir == NULL){//só tem filho no ramo à esquerda
				aux->dir = del->esq;
				free(del);
			}
			else{//tem filho nos dois ramos
				pos = menor(del->dir);
				pos = del->esq;
				aux->dir = del->dir;
				free(del);
			}
			calcula_balanceamento(&(*raiz));
			return num;
		}
		
	}
	if (aux == NULL){
		if (*raiz == NULL){
			return -2;
		}
		else{
			return -1;
		}
	}
}

ARV *buscarNo(ARV *raiz, int num){
	
	if (raiz != NULL){
		buscarNo(raiz->esq, num);
		if (num == raiz->info){
			return raiz;
		}
		buscarNo(raiz->dir, num);
	}
}