#include <stdio.h>
#include <stdlib.h>

struct matriz_s {
    int** m;
    int tamanho;
};
typedef struct matriz_s matriz_t;

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

void
montaMatrizDeAdjacencia(matriz_t *matriz)
{
    for (int i = 0; i < matriz->tamanho; i++){
        int a, b, peso;
        scanf("%d %d %d", &a, &b, &peso);
        matriz->m[a-1][b-1] = peso;
        matriz->m[b-1][a-1] = peso;
    }
}

void
criaEntradaLPSolve(matriz_t matriz, int origem, int destino, int demanda)
{

    fprintf(stdout, "min: ");

    for (int i = 0; i < matriz.tamanho; i++){
        for (int j = 0; j < matriz.tamanho; j++){
            if (matriz.m[i][j] != 0){ 
                fprintf(stdout, "+ %dx%d%d", matriz.m[i][j]*demanda,i+1,j+1);
            }
        }
    }
    fprintf(stdout,";\n\n");

    for (int i = 0; i < matriz.tamanho; i++){
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

int 
main()
{  
    matriz_t matriz;
    int quantidadeArestas;
    int origem;
    int destino;
    int demanda;

    scanf("%d %d", &matriz.tamanho, &quantidadeArestas);
    scanf("%d %d %d", &origem, &destino, &demanda);

    // ler entrada
    matriz.m = alocaMatriz(matriz.tamanho);

    // criar matriz de adjacencia
    montaMatrizDeAdjacencia(&matriz); 

    imprimeMatriz(matriz);
    
    // criar entrada lpSolve
    criaEntradaLPSolve(matriz, origem, destino, demanda);

    return 0;
}