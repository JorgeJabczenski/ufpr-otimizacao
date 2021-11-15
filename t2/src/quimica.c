#include <stdio.h>
#include <stdlib.h>

typedef struct objeto_s {
    int peso;
    int ganho;
} objeto_t;

typedef struct par_s{
    int a;
    int b;
} par_t;

objeto_t *alocaObjetos(int n){
    return (objeto_t *) malloc (n*sizeof(objeto_t));
}
void lerObjetos(int n, objeto_t *objetos){
    for (int i = 0; i < n; i++) scanf("%d", &objetos[i].peso);
    for (int i = 0; i < n; i++) scanf("%d", &objetos[i].ganho);
    
}
void imprimeObjeto(objeto_t objeto){
    printf("peso: %d | ganho: %d\n", objeto.peso, objeto.ganho);
}


par_t *alocaPares(int n){
    return (par_t *) malloc (n*sizeof(par_t));
}
void lerPares(int n, par_t *pares){
    for (int i = 0; i < n; i++) scanf("%d %d",&pares[i].a, &pares[i].b);
}
void imprimePar(par_t par){
    printf("a: %d | b: %d\n", par.a, par.b);
}




int
main()
{
    int qtdObjetos;
    int qtdPares;
    int capacidadeMaxima;
    objeto_t *objetos;
    par_t *pares;

    // Ler entradas
    scanf("%d %d %d", &qtdObjetos, &qtdPares, &capacidadeMaxima);

    objetos = alocaObjetos(qtdObjetos);
    pares   = alocaPares(qtdPares);

    lerObjetos(qtdObjetos ,objetos);
    lerPares(qtdPares, pares);

    // Imprimir saída
    printf("CapMax : %d\n", capacidadeMaxima);
    for (int i = 0 ; i < qtdObjetos; i++) imprimeObjeto(objetos[i]);
    for (int i = 0 ; i < qtdPares;   i++) imprimePar(pares[i]);


    return 0;
}