#include "types.h"
int alturaR(ARV *raiz); 
int fator_balanceamento(ARV *raiz);
ARV* criarNo(int num);
ARV * buscaR(ARV *raiz, int num);
void LSE(ARV **no);
void LSD(ARV **no);
void RL(ARV **no);
void LR(ARV **no);
void LR(ARV **no);
void calcula_balanceamento(ARV **raiz);
void inserir(ARV **raiz, int num);
int remover(ARV **raiz, int num);
void exibir(ARV *raiz);
ARV *menor(ARV *raiz);