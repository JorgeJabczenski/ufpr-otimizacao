#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    srand(time(NULL));

    int n, m, c;

    if(argc == 2) n = atoi(argv[1]);
    else {
        fprintf(stderr,"usagem: ./a.out $n\n");
        exit(1);
    }

    m = rand()%(n/2) + 3;
    c = m*5;
    printf("%d %d %d\n", n, m, c);
    for(int i = 0; i < n; i++){
        printf("%d ", rand()%(c/2) + 1);
    }
    printf("\n");
    for(int i = 0; i < n; i++){
        printf("%d ", rand()%c + 1);
    }
    printf("\n");

    int i = 0;
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