#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstdint>
#include <cstring>
 

using namespace std;

/****************/
/** ESTRUTURAS **/
/****************/

typedef struct objeto_s {
    int peso;
    int valor;
} objeto_t;

typedef struct par_s{
    int a;
    int b;
} par_t;

/***********************/
/** Variaveis Globais **/
/***********************/

int vertices;          //
int qtdObjetos;        //
int qtdPares;          //
int capacidadeMaxima;  //
int *escolhasAtuais;   // possui apenas 0s ou 1s
int *escolhasOtimas;   //
int lucroMaximo;       //
          
objeto_t *objetos;     //
par_t *pares;          //

/***********************/
/**      Funções      **/
/***********************/

void copiaVetores(int *dst, int *scr){
    memcpy(dst, scr, sizeof(*dst));
}

bool reage(int *estado_atual, int item_teste){
    
    for (int i = 0; i < qtdPares; i++){
        if ((pares[i].a == item_teste) && (estado_atual[pares[i].b] == 1)){
            return true;
        }
        if ((pares[i].b == item_teste) && (estado_atual[pares[i].a] == 1)){
            return true;
        }
    }
    return false;
}


void mochila_quimica(int tamanhoAtual){
    
    vertices++;
    
    if (tamanhoAtual == qtdObjetos){
        int somaPesos = 0;
        for(int i = 0; i < qtdObjetos; i++){
            somaPesos += objetos[i].peso*escolhasAtuais[i];
        }
        if(somaPesos <= capacidadeMaxima){
            int lucroAtual = 0;
            for(int i = 0; i < qtdObjetos; i++){
                lucroAtual += objetos[i].valor*escolhasAtuais[i];
            }
            if(lucroAtual > lucroMaximo){
                lucroMaximo = lucroAtual;
                copiaVetores(escolhasOtimas, escolhasAtuais);
            }
        }
    } else {
        // escolhe baseado na função reage(evitar de explodir a porra toda né)?
        if (!reage(escolhasAtuais, tamanhoAtual)){
            escolhasAtuais[tamanhoAtual] = 1;
            mochila_quimica(tamanhoAtual+1);
        }
        escolhasAtuais[tamanhoAtual] = 0;
        mochila_quimica(tamanhoAtual+1);
    }
}

//--------------------------

objeto_t *alocaObjetos(int n){
    return (objeto_t *) malloc (n*sizeof(objeto_t));
}
void lerObjetos(int n, objeto_t *objetos){
    for (int i = 0; i < n; i++) scanf("%d", &objetos[i].peso);
    for (int i = 0; i < n; i++) scanf("%d", &objetos[i].valor);
    
}
void imprimeObjeto(objeto_t objeto){
    printf("peso: %d | valor: %d\n", objeto.peso, objeto.valor);
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
    vertices = 1;

    // Ler entradas
    scanf("%d %d %d", &qtdObjetos, &qtdPares, &capacidadeMaxima);

    objetos = alocaObjetos(qtdObjetos);
    pares   = alocaPares(qtdPares);

    escolhasAtuais = (int*) calloc (sizeof(int), qtdObjetos);
    escolhasOtimas = (int*) calloc (sizeof(int), qtdObjetos);

    lerObjetos(qtdObjetos ,objetos);
    lerPares(qtdPares, pares);

    // Imprimir saída
    printf("CapMax : %d\n", capacidadeMaxima);
    for (int i = 0 ; i < qtdObjetos; i++) imprimeObjeto(objetos[i]);
    for (int i = 0 ; i < qtdPares;   i++) imprimePar(pares[i]);

    mochila_quimica(0);

    cout << "Vertices: " << vertices << endl;

    return 0;
}