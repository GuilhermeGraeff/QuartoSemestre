#include <stdio.h>
#include <stdlib.h>

struct ItemLista {
    int origem;
    int destino;
    int peso;
    int posicao;

    struct ItemLista *prev;
    struct ItemLista *prox;
};
typedef struct ItemLista ItemLista;

typedef struct {
    ItemLista *head;
    ItemLista *tail;
} Lista;


Lista *criaLista(int size){
    Lista *lista = (Lista *) malloc( sizeof (Lista));
    
    ItemLista *first =  (ItemLista *) malloc( sizeof (ItemLista));
    first->prev = NULL;
    first->prox = NULL;
    printf("Digite a origem, o destino e o peso da aresta(o,d,p):");
    int o=0;
    int d=0;
    int p=0;
    scanf("%d,%d,%d",&o,&d,&p);
    first->origem = o;
    first->destino = d;
    first->peso = p;

    lista->head = first;

    first->posicao = 0;
    ItemLista *elemento = first;
    ItemLista *aux;
    int i = size-1;
    while(i > 0){
        aux = ( ItemLista *) malloc( sizeof (ItemLista));

        printf("Digite a origem, o destino e o peso da aresta(o,d,p):");
        int o=0;
        int d=0;
        int p=0;
        scanf("%d,%d,%d",&o,&d,&p);
        aux->origem = o;
        aux->destino = d;
        aux->peso = p;

        aux->posicao = elemento->posicao + 1;
        aux->prev = elemento; 
        aux->prox = NULL;
        elemento->prox = aux; 
        elemento = aux;
        i--;
    }
    lista->tail = aux;
    return lista;
}


void swap( ItemLista *a, ItemLista *b ){
    ItemLista *proximaA, *anteriorA;
    int posicaoA;

    if (a == b){
        return;
    }

    int origemAux = a->origem;
    int destinoAux = a->destino;
    int pesoAux = a->peso;
    a->origem = b->origem;
    a->destino = b->destino;
    a->peso = b->peso;
    b->origem = origemAux;
    b->destino = destinoAux;
    b->peso = pesoAux;
}

ItemLista *particiona( ItemLista *head, ItemLista *tail){
    ItemLista *pivot = tail;
    ItemLista *aux = head;

    while (head->posicao < tail->posicao) {
        if(head->peso <= pivot->peso) { //alterei de < para <=
            swap(head, aux);
            aux = aux->prox;
        }
        head = head->prox;
    }
    swap(aux, pivot);
    return aux;
}

void quickSort( ItemLista *head, ItemLista *tail){
    if (head->posicao < tail->posicao){
        ItemLista *pivot = particiona(head, tail);
        if(pivot->prev == NULL){
            quickSort(head, pivot);
            
        } else {
            quickSort(head, pivot->prev);
        }
        if(pivot->prox == NULL){
            quickSort(pivot, tail); 
        } else {
            quickSort(pivot->prox, tail); 
            
        }
    }
}

void printLista (Lista *lista){
    
    ItemLista *aux;
    printf("\n---- Lista ----\n\t");
    for (aux = lista->head; aux != NULL; aux = aux->prox){
        printf("(O=%d,D=%d),P=%d --->",aux->origem,aux->destino,aux->peso);
    }
    printf("\n------------\n");
}


int find_root_value(int *kruskTable, int nodo){
    int run = 1;
    while(run = 1){
        if(kruskTable[nodo] >= 0){
            if(nodo == kruskTable[nodo]){
                return kruskTable[nodo];
            }
            nodo = kruskTable[nodo];
        }
        else{
            return kruskTable[nodo];
        }
    }
}
int find_root(int *kruskTable, int nodo){
    int run = 1;
    while(run = 1){
        if(kruskTable[nodo] >= 0){
            if (nodo == kruskTable[nodo]){
                return nodo;
            }
            nodo = kruskTable[nodo];
        }
        else{
            return nodo;
        }
    }
}
void kruskal (Lista *lista, int size_graph, int size_edges){
    ItemLista *aux;
    int *kruskTable = malloc(sizeof(int)*size_graph);
    for(int i = 0; i<size_graph; i++){
        kruskTable[i] = -1;
    }
    int *caminho = malloc(sizeof(int)*(size_edges*2));
    size_edges = size_edges*2;
    for(int i = 0; i<size_edges; i++){
        caminho[i] = -1;
    }
    for(int i = 0; i<size_edges; i++){
        printf("%d",caminho[i]);
    }
    // kruskTable[0]=-6;
    // kruskTable[1]=2;
    // kruskTable[2]=3;
    // kruskTable[3]=4;
    // kruskTable[4]=0;
    //printf("Nodo raiz = %d, Valor do nodo raiz = %d", find_root(kruskTable, 1),find_root_value(kruskTable, 1));
    int passo = 0;
    int somatorio  = 0;

    for (aux = lista->head; aux != NULL; aux = aux->prox){
        printf("Explorando aresta (%d) <-%d-> (%d)\n", aux->origem, aux->peso, aux->destino);
        printf("      Vertice->");
        for(int i = 0; i < size_graph; i++ ){
            printf("| %2d ",i);
        }
        printf("|\n");
        printf("      raiz   ->");
        for(int i = 0; i < size_graph; i++ ){
            printf("| %2d ",kruskTable[i]);
        }
        printf("|\n");
        if(kruskTable[aux->origem] < 0 && kruskTable[aux->destino] < 0){
            //printf("a :  %d    %d   ", kruskTable[aux->origem], kruskTable[aux->destino]);
            if(kruskTable[aux->origem] < kruskTable[aux->destino]){
                kruskTable[aux->origem]--;
                kruskTable[aux->destino]=aux->origem;
                somatorio+=aux->peso;
                caminho[passo]= aux->origem;
                caminho[passo+1]= aux->destino;
            }else{
                kruskTable[aux->destino]--;
                kruskTable[aux->origem]=aux->destino;
                somatorio+=aux->peso;
            }
            caminho[passo]= aux->origem;
            caminho[passo+1]= aux->destino;
            passo+=2;
        }
        else if(kruskTable[aux->origem] < 0 && kruskTable[aux->destino] >= 0){

            //printf("b     %d,     %d",kruskTable[aux->origem] ,kruskTable[aux->destino] );
            if(aux->origem == find_root(kruskTable,kruskTable[aux->destino])){
                printf("");
            }
            else{
                if(kruskTable[aux->origem] < find_root_value(kruskTable,kruskTable[aux->destino])){
                    kruskTable[aux->origem]+=find_root_value(kruskTable,aux->destino);
                    kruskTable[find_root(kruskTable,aux->destino)]=aux->origem;
                    somatorio+=aux->peso;
                }else{
                    kruskTable[find_root(kruskTable,aux->destino)]+= kruskTable[aux->origem];
                    kruskTable[aux->origem]=find_root(kruskTable,aux->destino);
                    somatorio+=aux->peso;
                }
                caminho[passo]= aux->origem;
                caminho[passo+1]= aux->destino;
                passo+=2;
            }
        }
        else if(kruskTable[aux->origem] >= 0 && kruskTable[aux->destino] < 0){
            //printf("c :  %d    %d   ", kruskTable[aux->origem], kruskTable[aux->destino]);
            if(find_root(kruskTable,kruskTable[aux->origem]) == aux->destino){
                printf("");
            }
            else{
                if(find_root_value(kruskTable,kruskTable[aux->origem]) < kruskTable[aux->destino]){
                    kruskTable[find_root(kruskTable,aux->origem)]+=kruskTable[aux->destino];
                    kruskTable[aux->destino]=find_root(kruskTable,aux->origem);
                    somatorio+=aux->peso;
                }else{
                    kruskTable[find_root(kruskTable,aux->destino)]+=find_root_value(kruskTable,aux->origem);
                    kruskTable[find_root(kruskTable,aux->origem)]=aux->destino;
                    somatorio+=aux->peso;
                }
                caminho[passo]= aux->origem;
                caminho[passo+1]= aux->destino;
                passo+=2;
            }
        }
        else if( kruskTable[aux->origem] >= 0 && kruskTable[aux->destino] >= 0){
            //printf("d :  %d    %d   ", kruskTable[aux->origem], kruskTable[aux->destino]);
            if(find_root(kruskTable,kruskTable[aux->origem]) == find_root(kruskTable,kruskTable[aux->destino])){
                printf("");
            }
            else{
                if(find_root_value(kruskTable,kruskTable[aux->origem])  < find_root_value(kruskTable,kruskTable[aux->destino])){
                    kruskTable[find_root(kruskTable,aux->origem)]+=find_root_value(kruskTable,aux->destino);
                    kruskTable[find_root(kruskTable,aux->destino)]=find_root(kruskTable,aux->origem);
                    somatorio+=aux->peso;
                }else{
                    kruskTable[find_root(kruskTable,aux->destino)]+=find_root_value(kruskTable,aux->origem);
                    kruskTable[find_root(kruskTable,aux->origem)]=find_root(kruskTable,aux->destino);
                    somatorio+=aux->peso;
                }
                caminho[passo]= aux->origem;
                caminho[passo+1]= aux->destino;
                passo+=2;
            }
        }
        printf("\n      Caminho atual:\n");
        printf("      ");
        // for(int i = 0; i<size_edges; i++){
        //     printf("%d",caminho[i]);
        //}
        for(int z = 0;  z<size_edges; z+=2){
            if(caminho[z]==-1){
                break;
            }
            else{
                printf("(%d,%d)",caminho[z],caminho[z+1]);
            }
        }
        printf("\n\n\n");
    }
    printf("O resultado da soma das arestas da arv min spn e: %d ",somatorio);

}

int main(){
    Lista *lista;
    int size_graph = 0; 
    int size_edges = 0;
    printf("E o seguinte, insere o tamanho do grafo ai por favor, lembrando: Os nomes dos vertices serao criados a partir do tamanho, entao se o tamanho do grafo e 5, os vertices criados sao 0,1,2,3,4:\n");
    scanf("%d", &size_graph);
    printf("Insiea a quantidade de arestas ai por favor: \n");
    scanf("%d", &size_edges);

    lista = criaLista(size_edges);
    
    printLista(lista);

    quickSort(lista->head, lista->tail);

    printLista(lista);
    
    kruskal(lista, size_graph,size_edges);
    
    return 0;
}