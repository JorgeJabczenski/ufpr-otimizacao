/**********************/
/*  Otimização -> T1  */
/* jlvj19 GRR20190372 */
/* vtvd19 GRR20190367 */
/**********************/

#include <stdio.h>
#include <stdlib.h>

/* Struct de uma matriz*/
struct matriz_s {
    int** m;
    int tamanho;
};
typedef struct matriz_s matriz_t;

/* Struct utilizada para gerar a entrada
     do LP solve                         */
struct lpSolve_s {
    matriz_t matriz;
    int origem;
    int destino;
    int demanda;
};
typedef struct lpSolve_s lpSolve_t;

int**
alocaMatriz(int n);

void
imprimeMatriz(matriz_t matriz);

void
montaMatrizDeAdjacencia(matriz_t *matriz, int quantidadeArestas);

void
criaEntradaLPSolve(matriz_t matriz, int origem, int destino, int demanda);
