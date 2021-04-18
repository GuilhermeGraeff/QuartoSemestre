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
        if(head->peso < pivot->peso) {
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

void kruskal (Lista *lista, int size_graph){
    ItemLista *aux;
    int *kruskTable = malloc(sizeof(int)*size_graph);
    for(int i =0; i<size_graph; i++){
        kruskTable[i] = -1;
    }
    

    for (aux = lista->head; aux != NULL; aux = aux->prox){
        int run = 1;
        while(run == 1){
            if(aux->origem < 0 && aux->destino < 0){
                if(aux->destino < aux->origem){

                }
                else if(aux->destino > aux->origem){

                }
                else{
                    
                }
            }
        }
    }

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
    
    kruskal(lista,7);
    
    return 0;
}