#include <stdio.h>
#include <stdlib.h>
/*
Implementar um algoritmo guloso em C que tenta achar um caminho entre dois nodos através de uma matriz de adjacência.
O algoritmo pode não achar um caminho, mesmo que esse exista:

	se chegar em um ponto onde não consegue mais avançar deve retornar "Impossível com Guloso"
	Se fizer mais que N passos e não encontrar o caminho imprimir "Cansei, impossível fazer com Guloso".
	Verificar se a melhor opção não para o mesmo nodo, se for, pega a segunda melhor (Evita loops).

A cada passo o algoritmo deve mostrar as opções que possui e a opção escolhida.

(Em anexo um exemplo de matriz de adjacência)
*/
int main(){
	int **matAdja;
	int n,i;

	scanf("%d", &n);

	matAdja = (int **) malloc(sizeof(int*)*n); //todas as linhas 	
	for (i=0; i<n;i++){
		matAdja[i] = malloc(sizeof(int)*n); //para cada posição inicial.
	}
	//matriz[n][n]/
	 

	for (i=0; i<n;i++)
		for(int j=0; j<n; j++){
			printf("Lendo valor %d,%d: \n", i,j);
			scanf("%d", &matAdja[i][j]);
		}

	printf("\n****** Matrix *****\n");
	for (i=0; i<n;i++){
		for(int j=0; j<n; j++){
			printf("%d \t|", matAdja[i][j]);
		}
		printf("\n");
	}

	int naoEncontrouMenorAresta = 1; 
	int passos = 0;

	printf("Quer partir de que vertice? (0,1,2,...,n)");
	int verticeInicial = 0;
	scanf("%d", &verticeInicial);
	int linhaAtual = verticeInicial;

	printf("Qual vertice voce procura?  (0,1,2,...,n)");
	int verticeProcurado = 0;
	scanf("%d", &verticeProcurado);

	printf("Qual o valor minimo de passos para o algoritmo?");
	int minPassos = 0;
	scanf("%d", &minPassos);

	while(naoEncontrouMenorAresta == 1){
		int menorCaminho = 2000000000;
		if(passos > 1 && verticeInicial == linhaAtual){
			printf("O algorítmo encontrou em loop a partir do passo %d, impossível com guloso :(", linhaAtual);
			naoEncontrouMenorAresta = 0;
		}
		passos++;
		int auxlinhaAtual = 0;
		for(int i = 0; i<n; i++){
			//printf("\nColuna : %d\n",i);
			if (matAdja[linhaAtual][i] <= menorCaminho  && linhaAtual != i && matAdja[linhaAtual][i] != 0){
				//printf("\nEncontrou o nodo : %d\n",i);
				auxlinhaAtual = i;
				menorCaminho = matAdja[linhaAtual][i];
			}
		}
		linhaAtual = auxlinhaAtual;
		if(auxlinhaAtual == 0){
			printf("O algorítmo encontrou um sumidouro a partir do passo %d, impossível com guloso :(", linhaAtual);
			naoEncontrouMenorAresta = 0;
		}
		else {
			if(linhaAtual == verticeProcurado){
				printf("O algorítmo encontrou o vertice procurado em %d passos",passos);
				naoEncontrouMenorAresta = 0;
			}
		}	
		if(passos > minPassos){
			printf("Cansei, impossível fazer com Guloso :(", linhaAtual);
			naoEncontrouMenorAresta = 0;
		}

	}
	return 0;
}