/*
Implementar uma versão bem simplificada de um grafo utilizando listas encadeadas. 
A ideia é que possamos armazenar o conjunto de vértices e arestas.
Seu programa deve calcular o  grau de um nodo X (considerando grafos orientados e não orientados)

obs: O código base produzido em aula esta disponível no moodle.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int val;
} Vertice;


typedef struct {
	Vertice *origem;
	Vertice *destino;
} Aresta;

struct tp_list_vet {
	Vertice *v;
	struct tp_list_vet *ant;
	struct tp_list_vet *prox;
};
typedef struct tp_list_vet Vertices;

struct tp_list_edges {
	Aresta *e;
	struct tp_list_edges *prox;
	struct tp_list_edges *ant;
};
typedef struct tp_list_edges Arestas;

typedef struct {
	Vertices *primeiroV;
	Vertices *ultimoV;

	Arestas *primeiroA;
	Arestas *ultimoA;
} Grafo;


Grafo *inicializaGrafo(){
	Grafo *G = malloc(sizeof(Grafo));
	G->primeiroV = NULL;
	G->ultimoV = NULL;
	G->primeiroA = NULL;
	G->ultimoA = NULL;

	return G;
}

void liberaMemoria(Grafo *G){
	Vertices *auxV = G->primeiroV;
	Arestas *auxA = G->primeiroA;
	
	while(auxV != NULL){
		auxV = G->primeiroV->prox;
		free(G->primeiroV);
		G->primeiroV = auxV;
	}

	while(auxA != NULL){
		auxA=G->primeiroA->prox;
		free(G->primeiroA);
		G->primeiroA = auxA;
	}

	free(G);

	printf("\nMemoria liberada\n");
}

void imprimeVertices(Grafo *g){
	Vertices *aux = g->primeiroV;

	printf("****** Lista de Vértices ********\n\t{");
	while(aux != NULL){
		printf("%d", aux->v->val);
		if (aux != g->ultimoV){
			printf(", ");
		}
		aux=aux->prox;
	}
	printf("}\n");
}

void imprimeAresta(Grafo *g){
	Arestas *aux = g->primeiroA;

	printf("****** Lista de Arestas ********\n\t{");
	while(aux != NULL){
		printf("(%d,%d)", aux->e->origem->val, aux->e->destino->val);
		if (aux != g->ultimoA){
			printf(", ");
		}
		aux=aux->prox;
	}
	printf("}\n");
}

Vertice *getVertice(Grafo *g, int valor){
	Vertices *aux = g->primeiroV;

	while(aux != NULL){
		if (aux->v->val == valor){
			return aux->v;
		}
		aux=aux->prox;
	}

	return NULL;
} 

void insereVertice(Grafo *G, int val){
	Vertice *newV;
	Vertices *auxV;

	newV = malloc(sizeof(Vertice)); //nosso vértice
	newV->val = val;

	auxV = malloc(sizeof(Vertices));
	auxV->ant = NULL;
	auxV->prox = NULL;
	auxV->v = newV;

	if (G->primeiroV == NULL){ //lista Vazia
		G->primeiroV = auxV;
		G->ultimoV = auxV; 
	} else { //faz o encadeamento
		G->ultimoV->prox = auxV; //O proximo do ultimo ser o novo elemento
		auxV->ant = G->ultimoV; //anterior do novo elemento ser o ultimo
		G->ultimoV = auxV;  //o novo elemento vira o ultimo
	}
}
/**
 * Nesta função havia um erro, não haviamos criado a aresta com dois vértices, e sim com dois int. Foi corrigido e há uma observação.
 */
void insereAresta(Grafo *G, int origem, int destino){
	Aresta *newA;
	Arestas *auxA;
	Vertice *o, *d;
	newA = malloc(sizeof(Aresta)); //nosso vértice

	/**
	 * Perceba que aqui estamos criando um novo vértice para representar a origem, 
	 * 	poderiamos buscar um vértice já existente em nossa lista, e caso não encontrar apresentar um erro. 
	 * Nesta tarefa isso não faz diferença. A função getVertice busca um vertice, caso deseje utilizar.
	 * ex -> 
	 * 		o = getVertice(G ,origem);
	 *		newA->origem = o;
	 */
	o = malloc(sizeof(Vertice));
	o->val = origem;
	newA->origem = o;

	d = malloc(sizeof(Vertice));
	d->val = destino;
	newA->destino = d;

	auxA = malloc(sizeof(Arestas));
	auxA->ant = NULL;
	auxA->prox = NULL;
	auxA->e = newA;

	if (G->primeiroA == NULL){ //lista Vazia
		G->primeiroA = auxA;
		G->ultimoA = auxA; 
	} else { //faz o encadeamento
		//printf("Não é o primeiro\n");
		G->ultimoA->prox = auxA; //O proximo do ultimo ser o novo elemento
		auxA->ant = G->ultimoA; //anterior do novo elemento ser o ultimo
		G->ultimoA = auxA;  //o novo elemento vira o ultimo
		//printf("Feito\n");
	}
}

//val é o nome do nodo
int grauVertice(Grafo *g, int val){ 
	Arestas *aux = g->primeiroA;
	int grauVertice = 0;
	while(aux != NULL){
		printf("entrou no while!");
		if (aux->e->origem->val == val){
			grauVertice++;
		}
		if (aux->e->destino->val == val){
			grauVertice++;
		}	
		aux=aux->prox;
	}
	return grauVertice;
}


int grauEntradaVertice(Grafo *g, int val){ //todas as vezes que ele é destino
	Arestas *aux = g->primeiroA;
	int grauEntrada = 0;
	while(aux != NULL){
		if (aux->e->destino->val == val){
			grauEntrada++;
		}
		aux=aux->prox;
	}
	return grauEntrada;
}

int grauSaidaVertice(Grafo *g, int val){ //todas as vezes que ele origem
	Arestas *aux = g->primeiroA;
	int grauSaida = 0;
	while(aux != NULL){
		if (aux->e->origem->val == val){
			grauSaida++;
		}
		aux=aux->prox;
	}
	return grauSaida;
}


int main(){
	Grafo *G; //armazena o conjunto de vertices e arestas
	
	int i,n, val, origem, destino;

	//incializa o grafo
	G = inicializaGrafo();

	printf("Digite o número de vértices:");
	scanf("%d", &n); //numero de vertices.

	for(i=0;i<n;i++){
		scanf("%d", &val);
		insereVertice(G,val);
	}

	printf("\nDigite o número de Arestas:");
	scanf("%d", &n); //numero de arestas.

	printf("\nDigite as arestas nmo formato Origem,Destino\n");
	for(i=0;i<n;i++){
		scanf("%d,%d", &origem, &destino);
		insereAresta(G, origem,destino);
	}

	imprimeVertices(G);
	imprimeAresta(G);
//---------------------------------------------------------------------
	printf("\nDigite o valor do vértice para verificar seu grau\n");
	int valVerificar = 0;
	scanf("%d",&valVerificar);
	printf("\nO grau do vertice é: %d\n", grauVertice(G,valVerificar));
	printf("\nO grau de saída do vertice é: %d\n", grauSaidaVertice(G,valVerificar));
	printf("\nO grau de entrada do vertice é: %d\n", grauEntradaVertice(G,valVerificar));
//---------------------------------------------------------------------
	liberaMemoria(G);
	
	return 0;
}