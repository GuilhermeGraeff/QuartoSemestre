#include <stdio.h>
#include <stdlib.h>
int main(){
	int **matAdja;
	int **infoCores;
	int n,i;
	printf("Informe o tamanho: \n");
	scanf("%d", &n);
	infoCores = (int **) malloc(sizeof(int*)*n);
    //infoCores 0 = Vértice 
    //infoCores 1 = cor(0 é sem cor, 1 é verde, 2 é azul, 3 é amarelo, e 4 é vermelho)	
	for (i=0; i<n;i++){
		infoCores[i] = malloc(sizeof(int)*2);
		infoCores[i][0] = i;
		infoCores[i][1] = 0;
	}
	matAdja = (int **) malloc(sizeof(int*)*n); 
	for (i=0; i<n;i++){
		matAdja[i] = malloc(sizeof(int)*n);
    }
	for (i=0; i<n;i++){
		for(int j=0; j<n; j++){
			printf("Lendo valor %d,%d: \n", i,j);
			scanf("%d", &matAdja[i][j]);
		}
	}

    int verticeAtual = 0;
    int run = 1;
    int numCores = 0;
    while(run == 1){
        int amarelo = 0;
        int verde = 0;
        int azul = 0;
        for(int i = 0; i<n; i++){
            if(matAdja[verticeAtual][i] != 0){
                if(infoCores[i][1] == 1){
                amarelo = 1;
                }
                if(infoCores[i][1] == 2){
                    verde = 1;
                }
                if(infoCores[i][1] == 3){
                    azul = 1;
                }
            }  
        }

        if(azul == 0 && verde == 0 && amarelo == 0 ){
            infoCores[verticeAtual][1] = 1;
            if(numCores < 1){
                numCores = 1;
            }
        }
        if(azul == 0 && verde == 0 && amarelo == 1 ){
            infoCores[verticeAtual][1] = 2;
            if(numCores < 2){
                numCores = 2;
            }
        }
        if(azul == 0 && verde == 1 && amarelo == 0 ){
            infoCores[verticeAtual][1] = 1;
            if(numCores < 2){
                numCores = 2;
            }
        }
        if(azul == 0 && verde == 1 && amarelo == 1 ){
            infoCores[verticeAtual][1] = 3;
            if(numCores < 3){
                numCores = 3;
            }
        }
        if(azul == 1 && verde == 0 && amarelo == 0 ){
            infoCores[verticeAtual][1] = 1;
            if(numCores < 2){
                numCores = 2;
            }
        }
        if(azul == 1 && verde == 0 && amarelo == 1 ){
            infoCores[verticeAtual][1] = 2;
            if(numCores < 3){
                numCores = 3;
            }
        }
        if(azul == 1 && verde == 1 && amarelo == 0 ){
            infoCores[verticeAtual][1] = 1;
            if(numCores < 2){
                numCores = 2;
            }
        }
        if(azul == 1 && verde == 1 && amarelo == 1 ){
            infoCores[verticeAtual][1] = 4;
            numCores = 4;
        }
        printf("\n****** Vertices info *****");
		printf("\nVertice |Cor\n");
		for (i=0; i<n;i++){
			for(int j=0; j<2; j++){
				printf("%d \t|", infoCores[i][j]);
			}	
			printf("\n");
		}
        printf("\n Numero de cores utilizado: %d\n",numCores);

        if(verticeAtual == n-1){
            run = 0;
        }
        verticeAtual++;
    }
	return 0;
}