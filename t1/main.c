/**********************/
/*  Otimização -> T1  */
/* jlvj19 GRR20190372 */
/* vtvd19 GRR20190367 */
/**********************/

#include "utils.h"

int 
main()
{  
    matriz_t matriz;
    int origem;
    int destino;
    int demanda;
    int quantidadeArestas;

    scanf("%d %d", &matriz.tamanho, &quantidadeArestas);
    scanf("%d %d %d", &origem, &destino, &demanda);

    // lê a entrada
    matriz.m = alocaMatriz(matriz.tamanho);

    // cria a matriz de adjacencia
    montaMatrizDeAdjacencia(&matriz, quantidadeArestas); 
    
    // cria a entrada lpSolve
    criaEntradaLPSolve(matriz, origem, destino, demanda);

    return 0;
}