#ifndef ARVORE
#define ARVORE

typedef struct arvore{
	int info;
	int fb;
	struct arvore *esq, *dir;
}ARV;

#endif