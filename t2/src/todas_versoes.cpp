#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstdint>
#include <cstring>
#include <sys/time.h>
 
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

long int vertices;     //
int qtdObjetos;        //
int qtdPares;          //
int pesoMaximo;        //
int *escolhasAtuais;   // possui apenas 0s ou 1s
int *escolhasOtimas;   //
int lucroMaximo;       //
int pesoFinal;         // nao precisa
          
objeto_t *objetos;     //
par_t *pares;          //

/***********************/
/**      Funções      **/
/***********************/

objeto_t *alocaObjetos(int n){
    return (objeto_t *) malloc (n*sizeof(objeto_t));
}
void lerObjetos(int n, objeto_t *objetos){
    for (int i = 0; i < n; i++) scanf("%d", &objetos[i].peso);
    for (int i = 0; i < n; i++) scanf("%d", &objetos[i].valor);
    
}
void imprimeObjeto(objeto_t objeto){
    printf("peso: %d \t| valor: %d\n", objeto.peso, objeto.valor);
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

bool cmp (const objeto_t& objeto1, const objeto_t& objeto2){
    return((double)objeto1.valor/objeto1.peso) > ((double)objeto2.valor/objeto2.peso);
}

void copiaVetores(int *dst, int *scr){
    memcpy(dst, scr, sizeof(*dst));
}

void copiaEscolhas(){
    for (int i = 0; i < qtdObjetos; i++)
        escolhasOtimas[i] = escolhasAtuais[i];
}

double rational_knapsack(objeto_t *objetos, int inicio, int pesoRestante){

    int tamanhoAtual = qtdObjetos - inicio;
    double peso = 0;
    double valor = 0;


    objeto_t *copia = (objeto_t *) malloc (sizeof(objeto_t)*tamanhoAtual);
    for(int i = 0; i < tamanhoAtual; i++){
        copia[i].peso  = objetos[inicio+i].peso;
        copia[i].valor = objetos[inicio+i].valor;
    }

    sort(&copia[0], &copia[tamanhoAtual], &cmp);

    int i = 0;
    while((i < tamanhoAtual) && (peso < pesoRestante)){
        if(peso + copia[i].peso <= pesoRestante){
            peso += copia[i].peso;
            valor += copia[i].valor;
            i++;
        } else {
            double valorFracionado = (double) (pesoRestante - peso)/copia[i].peso;
            peso = pesoRestante;
            valor += (valorFracionado)*copia[i].valor;
            i++;
        }
    }
    return valor;
}

bool reage(int *estadoAtual, int itemTeste)
{

    for (int i = 0; i < qtdPares; i++)
    {   
        // checa se o item atual reage com:
        // 1. um item anterior na lsita
        // 2. que está na mochila 
        // e é necessário checar se a ordem do par não está trocada
        // por isso os dois if's
        if ((pares[i].b - 1 <= itemTeste) && (pares[i].a - 1 == itemTeste) && (estadoAtual[pares[i].b - 1] == 1))
        {
            return true;
        }
        if ((pares[i].a - 1 <= itemTeste) && (pares[i].b - 1 == itemTeste) && (estadoAtual[pares[i].a - 1] == 1))
        {
            return true;
        }
    }
    return false;
}

void mochila_quimica(int tamanhoAtual, int pesoAtual){
    
    vertices++;
    
    if (tamanhoAtual == qtdObjetos){
        int lucroAtual = 0;
        for(int i = 0; i < qtdObjetos; i++){
            lucroAtual += objetos[i].valor*escolhasAtuais[i];
        }
        if(lucroAtual > lucroMaximo){
            lucroMaximo = lucroAtual;
            pesoFinal = pesoAtual;
            copiaEscolhas();
        }
        
    } else {
        
        float lucroAtual = 0;

        for(int i = 0; i < tamanhoAtual; i++){
            lucroAtual += objetos[i].valor*escolhasAtuais[i];
        }
        int proxEscolha[2] = {0, 1};
        double proxLimite[2];
        
        proxLimite[0] = lucroAtual + rational_knapsack(objetos, tamanhoAtual+1, pesoMaximo - pesoAtual);
        double proximoLucro = objetos[tamanhoAtual].valor;
        int     proximoPeso = objetos[tamanhoAtual].peso;
        proxLimite[1]  = lucroAtual + proximoLucro + rational_knapsack(objetos, tamanhoAtual+1, pesoMaximo - pesoAtual - proximoPeso);

        if(proxLimite[1] > proxLimite[0]){
            swap(proxEscolha[0], proxEscolha[1]);
            swap(proxLimite[0], proxLimite[1]);
        }
         
        for (int i = 0; i < 2; i++){
            if (proxLimite[i] < lucroMaximo){
                return;
            }

            int pesoItemAtual = objetos[tamanhoAtual].peso;
            if (proxEscolha[i] == 1 && (reage(escolhasAtuais, tamanhoAtual) || (pesoAtual + pesoItemAtual > pesoMaximo))){
                continue;
            }
            escolhasAtuais[tamanhoAtual] = proxEscolha[i];
            mochila_quimica(tamanhoAtual+1, pesoAtual + pesoItemAtual*proxEscolha[i]);
        }

    }
}

void mochila_quimica_sem_ordenacao(int tamanhoAtual, int pesoAtual){
    
    vertices++;
    
    if (tamanhoAtual == qtdObjetos){
        int lucroAtual = 0;
        for(int i = 0; i < qtdObjetos; i++){
            lucroAtual += objetos[i].valor*escolhasAtuais[i];
        }
        if(lucroAtual > lucroMaximo){
            lucroMaximo = lucroAtual;
            pesoFinal = pesoAtual;
            copiaEscolhas();

        }
        
    } else {
    
        float lucroAtual = 0;

        for(int i = 0; i < tamanhoAtual; i++){
            lucroAtual += objetos[i].valor*escolhasAtuais[i];
        }

        double B = (float) lucroAtual + rational_knapsack(objetos, tamanhoAtual, pesoMaximo - pesoAtual);
        if (B <= lucroMaximo) {
            return;
        }
        

        int pesoItemAtual = objetos[tamanhoAtual].peso;
        if (!reage(escolhasAtuais, tamanhoAtual) && (pesoAtual + pesoItemAtual <= pesoMaximo)){
            escolhasAtuais[tamanhoAtual] = 1;
            mochila_quimica_sem_ordenacao(tamanhoAtual+1, pesoAtual + pesoItemAtual);
        }
        escolhasAtuais[tamanhoAtual] = 0;
        mochila_quimica_sem_ordenacao(tamanhoAtual+1, pesoAtual);
    }
}

void mochila_quimica_sem_bounding(int tamanhoAtual, int pesoAtual){
    
    vertices++;
    
    if (tamanhoAtual == qtdObjetos){
        int lucroAtual = 0;
        for(int i = 0; i < qtdObjetos; i++){
            lucroAtual += objetos[i].valor*escolhasAtuais[i];
        }
        if(lucroAtual > lucroMaximo){
            lucroMaximo = lucroAtual;
            pesoFinal = pesoAtual;
            copiaVetores(escolhasOtimas, escolhasAtuais);
        }
    } else {
        int pesoItemAtual = objetos[tamanhoAtual].peso;
        if (!reage(escolhasAtuais, tamanhoAtual) && (pesoAtual + pesoItemAtual <= pesoMaximo)){
            escolhasAtuais[tamanhoAtual] = 1;
            mochila_quimica_sem_bounding(tamanhoAtual+1, pesoAtual + pesoItemAtual);
        }
        escolhasAtuais[tamanhoAtual] = 0;
        mochila_quimica_sem_bounding(tamanhoAtual+1, pesoAtual);
    }
}

void mochila_quimica_ingenua(int tamanhoAtual, int pesoAtual){
    
    vertices++;
    
    if (tamanhoAtual == qtdObjetos){
        int somaPesos = 0;
        for(int i = 0; i < qtdObjetos; i++){
            somaPesos += objetos[i].peso*escolhasAtuais[i];
        }
        if(somaPesos <= pesoMaximo){
            int lucroAtual = 0;
            for(int i = 0; i < qtdObjetos; i++){
                lucroAtual += objetos[i].valor*escolhasAtuais[i];
            }
            if(lucroAtual > lucroMaximo){
                lucroMaximo = lucroAtual;
                pesoFinal = pesoAtual;
                copiaVetores(escolhasOtimas, escolhasAtuais);
            }
        }
    } else {
        int pesoItemAtual = objetos[tamanhoAtual].peso;
        if (!reage(escolhasAtuais, tamanhoAtual)){
            escolhasAtuais[tamanhoAtual] = 1;
            mochila_quimica_ingenua(tamanhoAtual+1, pesoAtual + pesoItemAtual);
        }
        escolhasAtuais[tamanhoAtual] = 0;
        mochila_quimica_ingenua(tamanhoAtual+1, pesoAtual);
    }
}

double timestamp(void)
{
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}

//--------------------------

int
main()
{

    double tempo;


    // Ler entradas
    scanf("%d %d %d", &qtdObjetos, &qtdPares, &pesoMaximo);

    objetos = alocaObjetos(qtdObjetos);
    pares   = alocaPares(qtdPares);

    escolhasAtuais = (int*) calloc (sizeof(int), qtdObjetos);
    escolhasOtimas = (int*) calloc (sizeof(int), qtdObjetos);

    lerObjetos(qtdObjetos ,objetos);
    lerPares(qtdPares, pares);

    cerr << "Pares  : "<< qtdPares << endl;

    lucroMaximo = 0;
    vertices = 0;
    cerr << "Ingenua" << endl;
    tempo = timestamp();
    mochila_quimica_ingenua(0,0);
    tempo = timestamp() - tempo;
    cerr << "Nós  : "<< vertices << endl;
    cerr << "Tempo: " << tempo  << endl;
    cerr << "==============" << endl;
    

    lucroMaximo = 0;
    vertices = 0;
    cerr << "Sem Bounding" << endl;
    tempo = timestamp();
    mochila_quimica_sem_bounding(0,0);
    tempo = timestamp() - tempo;
    cerr << "Nós  : "<< vertices << endl;
    cerr << "Tempo: " << tempo  << endl;
    cerr << "==============" << endl;


    lucroMaximo = 0;
    vertices = 0;
    cerr << "Sem Ordenacao" << endl;
    tempo = timestamp();
    mochila_quimica_sem_ordenacao(0, 0);
    tempo = timestamp() - tempo;
    cerr << "Nós  : "<< vertices << endl;
    cerr << "Tempo: " << tempo  << endl;
    cerr << "==============" << endl;


    lucroMaximo = 0;
    vertices = 0;
    tempo = timestamp();
    mochila_quimica(0,0);
    tempo = timestamp() - tempo;
    cerr << "Nós  : "<< vertices << endl;
    cerr << "Tempo: " << tempo  << endl;


    return 0;
}