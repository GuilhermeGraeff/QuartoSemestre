#include <stdio.h>
#include <stdlib.h>
int main(){
	int *campo;
	int *tela;
	int n,i;
	n=9*9;
	campo = malloc(sizeof(int)*n);
    tela = malloc(sizeof(int)*n);

	printf("\n****** Matrix *****\n");
	for (i=0; i<n;i++){
		for(int j=0; j<n; j++){
			printf("%d \t|", matAdja[i][j]);
		}
		printf("\n");
	}
	printf("\n****** Matrix *****\n");
	for (i=0; i<n;i++){
		for(int j=0; j<4; j++){
			printf("%d \t|", djaTable[i][j]);
		}
		printf("\n");
	}

	
	int vertice_atual = 0;
	int run = 1;
	int isFirstInteration = 1;
	djaTable[0][2] = 0;
	for(int j = 0; j < n; j++){
		if(matAdja[vertice_atual][j] != 0){
			djaTable[j][2] = matAdja[vertice_atual][j];
			djaTable[j][3] = vertice_atual;
		}
	}
	printf("\n****** Vértices info *****\n");
	for (i=0; i<n;i++){
		for(int j=0; j<4; j++){
			printf("%d \t|", djaTable[i][j]);
		}	
		printf("\n");
	}
	
	for(int v = 0; v<n; v++)
	{
		
		for(int i = 0; i < n; i++){
			int candidato = matAdja[vertice_atual][i];
			if (candidato != 0){
				if (djaTable[i][2] > (candidato + djaTable[vertice_atual][2])){
					djaTable[i][2] = (candidato + djaTable[vertice_atual][2]);
					djaTable[i][3] = vertice_atual;
				}
			}
		}
		djaTable[vertice_atual][1] = 1;
	
		int indexOfLeastWeight = NULL;
		for(int i = 0; i < n; i++)
		{
			if(i == vertice_atual)
				continue;

			if(djaTable[i][1] != 1 && (indexOfLeastWeight == NULL || (djaTable[i][2] < djaTable[indexOfLeastWeight][2])))
				indexOfLeastWeight = i;	
		}
		
		printf("\n****** Vertices atual: %d  *****\n", vertice_atual);
		printf("\n****** Vertices info *****\n");
		printf("\nVertice |Visit. |Valor  |Anterior|\n");
		for (i=0; i<n;i++){
			for(int j=0; j<4; j++){
				printf("%d \t|", djaTable[i][j]);
			}	
		printf("\n");	
		}
		vertice_atual = indexOfLeastWeight;
	}
	return 0;
}