/*	ARVORE BINARIA DE BUSCA COM NO PAI
	Arquivo: ArvoreBinariaBuscaComPai.c
	Autor: tokyyto
	Data: 03/11/2024 12:20
	Descricao: implementacao da lista de exercicios envolvendo Arvores Binarias de Busca, com o no pai
	Anotacoes: N/A
*/


//diretivas
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "PilhaPointer.h"
#include "FilaPointer.h"
#include "Booleano.h"

//definicoes de tipo
typedef struct No{
	int item;
	int size;
	struct No * pai;
	struct No * esq;
	struct No * dir;
} No;

typedef No * ABB;

//interface
ABB criarABBVazia(); //cria uma ABB vazia
ABB inserirNo_Recursao(ABB, int); //ex 11
void mostrarABB_ERD_SemRecursao(ABB); //ex 12
No * obterAncestral(ABB, No *, No *); //ex 13
No * obterAncestral_Recursao(ABB, No *, No *); //ex 14
ABB removerRaiz(ABB); //ex 15
No * buscarABB(ABB, int); //ex 16
ABB inserirNo_SemRecursao(ABB, int); //ex 17
int obterAltura_Recursao(ABB); //ex 18
void mostrarPrimeiro_ERD(ABB); //ex 20
void mostrarUltimo_ERD(ABB); //ex 21
No * obterSucessor_ERD(ABB, int); //ex 23
No * obterAnterior_ERD(ABB, int); //ex 24
ABB buscaInsere(ABB, int); //ex 26
No * select(ABB, int); //ex 27
int rank(ABB, int); //ex 28

void mostrarABB_ERD(ABB); //mostra uma ABB usando caminhamento ERD
void mostrarABB_BFS(ABB); //mostra uma BFS usando caminhamento BFS

int main(){
	ABB A;
	No * p;
	int n;
	A = criarABBVazia();
//	A = inserirNo_SemRecursao(A, 13);
//	A = inserirNo_SemRecursao(A, 10);
//	A = inserirNo_SemRecursao(A, 11);
//	A = inserirNo_SemRecursao(A, 9);
//	A = inserirNo_SemRecursao(A, 12);
//	A = inserirNo_SemRecursao(A, 14);
//	A = inserirNo_Recursao(A, 8);
	A = buscaInsere(A, 13);
	A = buscaInsere(A, 10);
	A = buscaInsere(A, 11);
	A = buscaInsere(A, 9);
	A = buscaInsere(A, 12);
	A = buscaInsere(A, 14);
	A = buscaInsere(A, 14);
	
	A = removerRaiz(A);
//	p = obterAncestral(A, A -> esq -> esq, A -> dir -> dir);
//	printf("\nitem do ancestral (sem recursao): %d", p -> item);
	p = select(A, 5);
	printf("\nselect: %d", p -> item);
	
	n = rank(A, 14);
	printf("\nrank: %d", n);
	
	printf("\nERD com recursao:\n");
	mostrarABB_ERD(A);
	printf("\nBFS:\n");
	mostrarABB_BFS(A);
	
	printf("\n\n%d", A -> dir -> pai -> item);
	
	
	return 0;
}


//implementacao
ABB criarABBVazia(){ //cria uma ABB vazia
	ABB A;
	A = NULL;
	return A;
}

ABB inserirNo_Recursao(ABB A, int n){ //ex 11
	No * p, * novo;
	if(A == NULL){
		novo = malloc(sizeof(No));
		novo -> item = n;
		novo -> size = 1;
		novo -> esq = NULL;
		novo -> dir = NULL;
		novo -> pai = NULL;
		A = novo;
	}
	else{
		A;
		if(A -> item > n){
			A -> esq = inserirNo_Recursao(A -> esq, n);
			p = A -> esq;
		}
		else{
			A -> dir = inserirNo_Recursao(A -> dir, n);
			p = A -> dir;
		}
		A -> size = A -> size + 1;
		p -> pai = A;
	}
	return A;
}

void mostrarABB_ERD_SemRecursao(ABB A){ //ex 12
	No * p;
	Pilha P;
	if(A != NULL){
		p = A;
		criarPilhaVazia(&P);
		do{
			while(p != NULL){
				pushPilha(&P, p);
				p = p -> esq;
			}
			if(verificarPilhaVazia(&P) == FALSE){
				p = acessarTopo(&P);
				printf(" %d ", p -> item);
				popPilha(&P);
				p = p -> dir;
			}
		} while((p != NULL) || (verificarPilhaVazia(&P) == FALSE));
	}
	else{
		printf("\nArvore vazia!");
	}
}

No * obterAncestral(ABB A, No * p, No * q){ //ex 13
	No * anc, * i;
	bool fim;
	anc = A;
	i = A;
	fim = FALSE;
	while((i != NULL) && (fim == FALSE)){
		if((p -> item < i -> item) && (q -> item < i -> item)){
			i = i -> esq;
		}
		else if((p -> item > i -> item) && (q -> item > i -> item)){
			i = i -> dir;
		}
		else{
			anc = i;
			fim = TRUE;
		}
	}
	return anc;
}

No * obterAncestral_Recursao(ABB A, No * p, No * q){ //ex 14
	No * anc, * i;
	anc = A;
	i = A;
	if(A != NULL){
		if((p -> item < i -> item) && (q -> item < i -> item)){
			anc = obterAncestral_Recursao(i -> dir, p, q);
		}
		else if((p -> item > i -> item) && (q -> item > i -> item)){
			anc = obterAncestral_Recursao(i -> esq, p, q);
		}
	}
	return anc;
}

ABB removerRaiz(ABB A){ //ex 15
	No * p, * sohn, * vater;
	if(A != NULL){
		p = A;
		if(p -> pai == NULL){ //se eh a raiz
			if((p -> esq == NULL) && (p -> dir == NULL)){ //eh raiz e nao tem filhos
				A = NULL;
			}
			else if(((p -> esq != NULL) && (p -> dir == NULL)) || ((p -> dir != NULL) && (p -> esq == NULL))){ //eh raiz e so tem um filho
				if((p -> esq != NULL) && (p -> dir == NULL)){
					sohn = p -> esq;
				}
				else{
					sohn = p -> dir;
				}
				sohn -> pai = NULL;
				A = sohn;
			}
			else{ //eh raiz e tem dois filhos
				sohn = p -> esq;
				while(sohn -> dir != NULL){ //pega o maior dos menores
					sohn -> size = sohn -> size - 1;
					sohn = sohn -> dir;
				}
				if(sohn -> pai != A){ //se o pai nao for a raiz
					vater = sohn -> pai;
					if(sohn -> esq != NULL){
						vater -> dir = sohn -> esq;
						sohn -> esq -> pai = vater;
					}
					else{
						vater -> dir = NULL;
					}
					sohn -> esq = p -> esq;
					p -> esq -> pai = sohn;
				}
				p -> dir -> pai = sohn;
				sohn -> size = p -> size - 1;
				sohn -> dir = p -> dir;
				sohn -> pai = NULL;
				A = sohn;
			}
		}
		free(p);
	}
	return A;
}

No * buscarABB(ABB A, int n){ //ex 16
	No * p;
	p = A;
	if(A != NULL){
		while((p != NULL) && (p -> item != n)){
			if(p -> item > n){
				p = p -> esq;
			}
			else{
				p = p -> dir;
			}
		}
	}
	return p;
}

ABB inserirNo_SemRecursao(ABB A, int n){ //ex 17
	No * novo, * p, * ant;
	novo = malloc(sizeof(No));
	novo -> item = n;
	novo -> size = 1;
	novo -> esq = NULL;
	novo -> dir = NULL;
	novo -> pai = NULL;
	if(A == NULL){
		A = novo;
	}
	else{
		p = A;
		while(p != NULL){
			ant = p;
			if(p -> item > n){
				p -> size = p -> size + 1;
				p = p -> esq;
			}
			else{
				p -> size = p -> size + 1;
				p = p -> dir;
			}
		}
		if(ant -> item > n){
			ant -> esq = novo;
		}
		else{
			ant -> dir = novo;
		}
		novo -> pai = ant;
	}
	return A;
}

int obterAltura_Recursao(ABB A){ //ex 18
	int alt, aE, aD;
	No * p;
	alt = -1;
	if(A != NULL){
		p = A;
		aE = obterAltura_Recursao(p -> esq);
		aD = obterAltura_Recursao(p -> dir);
		if(aE > aD){
			alt = aE + 1;
		}
		else{
			alt = aD + 1;
		}
	}
	return alt;
}

void mostrarPrimeiro_ERD(ABB A){ //ex 20
	No * p;
	if(A != NULL){
		p = A;
		while(p -> esq != NULL){
			p = p -> esq;
		}
		printf(" %d ", p -> item);
	}
}

void mostrarUltimo_ERD(ABB A){ //ex 21
	No * p;
	if(A != NULL){
		p = A;
		while(p -> dir != NULL){
			p = p -> dir;
		}
		printf(" %d ", p -> item);
	}
}

No * obterSucessor_ERD(ABB A, int n){ //ex 23
	No * p, * prox, * vater;
	p = A;
	prox = NULL;
	while((p != NULL) && (p -> item != n)){ //busca o no
		if(p -> item > n){
			p = p -> esq;
		}
		else{
			p = p -> dir;
		}
	}
	if(p != NULL){
		if(p -> dir != NULL){ //se tem filho direito
			prox = p -> dir;
			while(prox -> esq != NULL){
				prox = prox -> esq;
			}
		}
		else{ //se nao tem, inspeciona o pai
			vater = p -> pai;
			while((vater != NULL) && (vater -> dir == p)){
				p = vater;
				vater = p -> pai;
			}
			if(vater != NULL){
				prox = vater;
			}
		}
	}
	return prox;
}

No * obterAnterior_ERD(ABB A, int n){ //ex 24
	No * p, * ant, * vater;
	p = A;
	ant = NULL;
	while((p != NULL) && (p -> item != n)){
		if(p -> item > n){
			p = p -> esq;
		}
		else{
			p = p -> dir;
		}
	}
	if(p != NULL){
		if(p -> esq != NULL){ //se tem filho esquerdo
			ant = p -> dir;
			while(ant -> dir != NULL){
				ant = ant -> dir;
			}
		}
		else{
			vater = p -> pai;
			while((vater != NULL) && (vater -> esq == p)){
				p = vater;
				vater = p -> pai;
			}
			if(vater != NULL){
				ant = vater;
			}
		}
	}
	return ant;
}

ABB buscaInsere(ABB A, int n){ //ex 26
	No * p, * ant, * novo;
	if(A == NULL){
		novo = malloc(sizeof(No));
		novo -> item = n;
		novo -> size = 1;
		novo -> esq = NULL;
		novo -> dir = NULL;
		novo -> pai = NULL;
		A = novo;
	}
	else{
		p = A;
		while((p != NULL) && (p -> item != n)){
			ant = p;
			if(p -> item > n){
				p = p -> esq;
			}
			else{
				p = p -> dir;
			}
		}
		if(p == NULL){ //se nao encontrou, pode inserir
			novo = malloc(sizeof(No));
			novo -> item = n;
			novo -> size = 1;
			novo -> esq = NULL;
			novo -> dir = NULL;
			novo -> pai = ant;
			if(ant -> item > n){
				ant -> esq = novo;
			}
			else{
				ant -> dir = novo;
			}
			//atualizar sizes
			p = A;
			while(p -> item != n){
				p -> size = p -> size + 1;
				if(p -> item > n){
					p = p -> esq;
				}
				else{
					p = p -> dir;
				}
			}
		}
	}
	return A;
}

No * select(ABB A, int k){ //ex 27
	No * p, * ant, * out;
	Pilha P;
	int cont;
	out = NULL;
	cont = 0;
	if(A != NULL){
		criarPilhaVazia(&P);
		p = A;
		do{
			while(p != NULL){
				pushPilha(&P, p);
				p = p -> esq;
			}
			if(verificarPilhaVazia(&P) == FALSE){
				p = acessarTopo(&P);
				popPilha(&P);
				cont++;
				ant = p;
				p = p -> dir;
			}
		} while((cont < k) && ((p != NULL) || (verificarPilhaVazia(&P) == FALSE)));
		if(cont == k){
			out = ant;
		}
	}
	return out;
}

int rank(ABB A, int n){ //ex 28
	No * p, * ant;
	Pilha P;
	int cont, k;
	cont = 0;
	k = 0;
	if(A != NULL){
		p = A;
		criarPilhaVazia(&P);
		do{
			while(p != NULL){
				pushPilha(&P, p);
				p = p -> esq;
			}
			if(verificarPilhaVazia(&P) == FALSE){
				p = acessarTopo(&P);
				ant = p;
				cont++;
				popPilha(&P);
				p = p -> dir;
			}
		} while(((p != NULL) || (verificarPilhaVazia(&P) == FALSE)) && ((ant != NULL) && (ant -> item != n)));
		k = cont;
	}
	return k;
}

void mostrarABB_ERD(ABB A){ //mostra uma ABB usando caminhamento ERD
	No * p;
	if(A != NULL){
		p = A;
		mostrarABB_ERD(p -> esq);
		printf(" %d ", p -> item);
		mostrarABB_ERD(p -> dir);
	}
}
void mostrarABB_BFS(ABB A){ //mostra uma BFS usando caminhamento BFS
	No * p;
	Fila F;
	if(A != NULL){
		p = A;
		criarFilaVazia(&F);
		pushFila(&F, p);
		do{
			p = acessarFila(&F);
			printf(" %d/%d", p -> item, p -> size);
			popFila(&F);
			if(p -> esq != NULL){
				pushFila(&F, p -> esq);
			}
			if(p -> dir != NULL){
				pushFila(&F, p -> dir);
			}
		} while(verificarFilaVazia(&F) == FALSE);
	}
	else{
		printf("\nArvore vazia!");
	}
}


