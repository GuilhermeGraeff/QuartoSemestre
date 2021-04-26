#include <stdio.h>
#include <stdlib.h>
int main(){
	int **matAdja;
	int **djaTable;
	int n,i;
	printf("Informe o tamanho: \n");
	scanf("%d", &n);
	// [0] = Vértice, [1] = foi visitado, [2] = custo, [3] caminho.
	djaTable = (int **) malloc(sizeof(int*)*n);	
	for (i=0; i<n;i++){
		djaTable[i] = malloc(sizeof(int)*4);
		djaTable[i][0] = i;
		djaTable[i][1] = 0;
		djaTable[i][2] = 10000;
		djaTable[i][3] = -1;
	}
	matAdja = (int **) malloc(sizeof(int*)*n); //todas as linhas 	
	for (i=0; i<n;i++){
		matAdja[i] = malloc(sizeof(int)*n); //para cada posição inicial.
	}
	for (i=0; i<n;i++){
		for(int j=0; j<n; j++){
			printf("Lendo valor %d,%d: \n", i,j);
			scanf("%d", &matAdja[i][j]);
		}
	}
	printf("\n****** Matrix *****\n");
	for (i=0; i<n;i++){
		for(int j=0; j<n; j++){
			printf("%d \t|", matAdja[i][j]);
		}
		printf("\n");
	}
	//setando o vertice atual no começo
	int vertice_atual = 0; 
	djaTable[0][2] = 0; 
	//----------------------------
	int run = 1;
	for(int v = 0; v<n; v++){	
		djaTable[vertice_atual][1] = 1;
		printf("\n****** Vertices atual: %d  *****", vertice_atual);
		printf("\n****** Vertices info *****");
		printf("\nVertice |Visit. |Custo  |Caminh |\n");
		for (i=0; i<n;i++){
			for(int j=0; j<4; j++){
				printf("%d \t|", djaTable[i][j]);
			}	
			printf("\n");
		}
		for(int i = 0; i < n; i++){
			if(matAdja[vertice_atual][i] < djaTable[i][2] && djaTable[i][1] != 1 && matAdja[vertice_atual][i] !=0){
				djaTable[i][2] = matAdja[vertice_atual][i];
				djaTable[i][3] = vertice_atual;
			}
		}
		int menor_valor = 10001;
		int vertice_menor_valor = 0;
		for(int i = 0; i < n; i++){
			if(djaTable[i][1] == 0 ){
				if(djaTable[i][2] < menor_valor){
					menor_valor=djaTable[i][2];
					vertice_menor_valor = i;
				}
			}
		}
		vertice_atual = vertice_menor_valor;
	}
	int sum = 0;
	printf("\nResultados finais:\n");
	for(int z = 0;  z<n; z++){
		printf("(%d,%d, com peso:%d)\n",djaTable[z][0],djaTable[z][3],djaTable[z][2]);
		sum += djaTable[z][2];
    }
	printf("Somatorio final da árvore é: %d", sum);
	return 0;
}