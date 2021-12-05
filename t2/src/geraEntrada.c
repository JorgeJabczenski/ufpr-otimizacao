#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    srand(time(NULL));

    int n, m, c;

    // pega da linha de comando quantos itens o problema vai ter
    if(argc == 2) n = atoi(argv[1]);
    else {
        fprintf(stderr,"usagem: ./a.out $n\n");
        exit(1);
    }
    // define o número de pares de acordo com o número de itens
    m = rand()%(n/2) + 3;
    // define a capacidade de acordo com o número de pares
    c = m*5;
    printf("%d %d %d\n", n, m, c);
    // gera os pesos dos itens de acordo com a capacidade
    for(int i = 0; i < n; i++){
        printf("%d ", rand()%(c/2) + 1);
    }
    printf("\n");
    // gera os valores dos itens de acordo com a capacidade
    for(int i = 0; i < n; i++){
        printf("%d ", rand()%c + 1);
    }
    printf("\n");

    int i = 0;
    // gera os pares proibidos de acordo com o número de itens
    // fazendo questão de não ter o mesmo item no par
    while(i < m){
        int a, b;
        a = rand()%n + 1;
        b = rand()%n + 1;
        if(a == b){
            continue;
        }
        printf("%d %d\n", a, b);
        i++;
    }

}