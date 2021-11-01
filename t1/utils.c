/**********************/
/*  Otimização -> T1  */
/* jlvj19 GRR20190372 */
/* vtvd19 GRR20190367 */
/**********************/

#include "utils.h"

/* Função genérica de alocação de matrizes */
int**
alocaMatriz(int n)
{
    int **m;
    m = (int**) calloc (n, sizeof(int*));
    for (int i = 0; i < n; i++){
        m[i] = (int *) calloc (n,sizeof(int));
    }
    return m;
}

/* Função genérica de impressão de matrizes */
void
imprimeMatriz(matriz_t matriz)
{
    for (int i = 0; i < matriz.tamanho; i++){
        for (int j = 0; j < matriz.tamanho; j++){
            printf("%d ", matriz.m[i][j]);
        }
        printf("\n");
    }
}

/* Lê a entrada e monta a matriz de ajdecencia */
void
montaMatrizDeAdjacencia(matriz_t *matriz, int quantidadeArestas)
{
    for (int i = 0; i < quantidadeArestas; i++){
        int a, b, peso;
        scanf("%d %d %d", &a, &b, &peso);
        matriz->m[a-1][b-1] = peso;
        matriz->m[b-1][a-1] = peso;
    }
}

/* Cria a entrada do lpSolve a martir da matriz de adjacencia */
void
criaEntradaLPSolve(matriz_t matriz, int origem, int destino, int demanda)
{

    /* indica que o objetivo deve ser minimizado */
    fprintf(stdout, "/* Função Objetiva*/\n");
    fprintf(stdout, "min: ");

    /* cria a função objetiva */
    for (int i = 0; i < matriz.tamanho; i++){
        for (int j = 0; j < i; j++){
            if (matriz.m[i][j] != 0){ 
                fprintf(stdout, "+ %dx%d%d ", matriz.m[j][i]*demanda,j+1,i+1);
                fprintf(stdout, "+ %dx%d%d ", matriz.m[i][j]*demanda,i+1,j+1);
            }
        }
    }
    fprintf(stdout,";\n\n");

    /* cria as restrições */

    fprintf(stdout, "/* Restrições */\n");
    for (int i = 0; i < matriz.tamanho; i++){
        fprintf(stdout, "/* Restrições da sede %d */\n", i);
        for (int j = 0; j < matriz.tamanho; j++)
        {
            if (matriz.m[i][j] != 0){ 
                fprintf(stdout, "+ x%d%d",i+1,j+1);
            }
            if (matriz.m[j][i] != 0){ 
                fprintf(stdout, "- x%d%d",j+1,i+1);
            }
        }
        if      (i+1 ==  origem) fprintf(stdout," =  1; \n");
        else if (i+1 == destino) fprintf(stdout," = -1; \n");
        else                     fprintf(stdout," =  0; \n");
    }
}