#include <stdio.h>
#include <stdlib.h>
int main(){
    int **matAdja;
    int **vertexInfo;
    int n,i;
    int *queue;
    n = 6;
    queue = malloc(sizeof(int)*10);

    //vertexInfo[i][1] = 0; é a distância até tal nodo

    //vertexInfo[i][2] = 0; = é o vértice que antecede tal vértice(para fazer o backtracking se necessário)

    //vertexInfo[i][3] = 0; = o vértice está pintado de branco(não foi visitado)
    //vertexInfo[i][3] = 1; = o vértice está pintado de cinza(foi visitado)
    //vertexInfo[i][3] = 2; = o vértice está pintado de preto(foi visitado e os nós adjacentes foram visitados)

    vertexInfo = (int **) malloc(sizeof(int*)*n);	
    for (i=0; i<n;i++){
        vertexInfo[i] = malloc(sizeof(int)*4);
        vertexInfo[i][0] = i;
        vertexInfo[i][1] = 0;
        vertexInfo[i][2] = 0;
        vertexInfo[i][3] = 0;
    }

    matAdja = (int **) malloc(sizeof(int*)*n);	
    for (i=0; i<n;i++){
        matAdja[i] = malloc(sizeof(int)*n);
    }

    //Declaration of the adjacent matrix:
    matAdja[0][0] = -1; matAdja[0][1] = 1; matAdja[0][2] = -1; matAdja[0][3] = 1; matAdja[0][4] = -1; matAdja[0][5] = -1;
    matAdja[1][0] = -1; matAdja[1][1] = -1; matAdja[1][2] = 1; matAdja[1][3] = -1; matAdja[1][4] = -1; matAdja[1][5] = -1;
    matAdja[2][0] = -1; matAdja[2][1] = -1; matAdja[2][2] = -1; matAdja[2][3] = -1; matAdja[2][4] = -1; matAdja[2][5] = -1;
    matAdja[3][0] = -1; matAdja[3][1] = -1; matAdja[3][2] = -1; matAdja[3][3] = -1; matAdja[3][4] = 1; matAdja[3][5] = 1;
    matAdja[4][0] = -1; matAdja[4][1] = -1; matAdja[4][2] = -1; matAdja[4][3] = -1; matAdja[4][4] = -1; matAdja[4][5] = -1;
    matAdja[5][0] = -1; matAdja[5][1] = -1; matAdja[5][2] = -1; matAdja[5][3] = -1; matAdja[5][4] = -1; matAdja[5][5] = -1;

    for(int i = 0; i <10; i++){
        queue[i] = 0;
    }


    
    int inicioFila = 0;
    int fimFila = 1;
    int tamanhoFila = 1;
    int tamanhoFilaTemp = 0;
    int fimFilaTemp = 1; 
    queue[0] = 0;
    int passo = 0;



    int run = 1;
    while(run == 1){
        fimFilaTemp = fimFila;
        int filaAuxInalt = inicioFila;
        for (int i = inicioFila; i < fimFila; i++){
            for(int j = 0; j < n; j++){
                if(matAdja[queue[i]][j] != -1 && vertexInfo[queue[i]][3] == 0){
                    tamanhoFilaTemp++;
                    vertexInfo[j][2] = queue[i];
                    queue[fimFilaTemp] = j;
                    fimFilaTemp++;
                }
            }
            vertexInfo[queue[i]][3] = 1;
            vertexInfo[queue[i]][1] = passo;
            printf("\n\n\n\n----------------------------------------------------------------------------------");
            printf("\nEsta sendo explorado o vertice: %d\n",queue[i]);
            printf("Vertex infos: \n");
            printf("Vertice | Distancia Acumulada | Vertice Anterior | Cor(0=branco,1=cinza,2=preto)       \n");
            for(int l = 0; l <n; l++){
                
                for(int c = 0; c <4; c++){
                    printf("%d                    ", vertexInfo[l][c]);
                }
                printf("\n");
            }
            printf("\nLista de nodos pretos: \n");
            for(int b = 0; b < n; b++){
                if(vertexInfo[b][3] == 2){
                    printf("| %d |", b);
                }
            }
            printf("\nLista de nodos brancos: \n");
            for(int b = 0; b < n; b++){
                if(vertexInfo[b][3] == 0){
                    printf("| %d |", b);
                }
            }
            printf("\nQueue:\n");
            for(int x = inicioFila; x < fimFila; x++){
                printf("| %d |", queue[x]);
            }
            
            
            if(vertexInfo[queue[i]][3] == 1){
                vertexInfo[queue[i]][3] = 2;
            }
            tamanhoFila--;
            inicioFila++;
        }


        fimFila = fimFilaTemp;
        tamanhoFila = tamanhoFilaTemp;
        tamanhoFilaTemp = 0;

        if(inicioFila == fimFila){
            printf("\n\n\n>>>>>>>>>>Ultima iteracao do algoritimo, resultados:<<<<<<<<<<<<<< \n");
            printf("Vertex infos: \n");
            printf("Vertice | Distancia Acumulada | Vertice Anterior | Cor(0=branco,1=cinza,2=preto)       \n");
            for(int l = 0; l <n; l++){
                
                for(int c = 0; c <4; c++){
                    printf("%d                    ", vertexInfo[l][c]);
                }
                printf("\n");
            }
             printf("\nLista de nodos pretos: \n");
            for(int b = 0; b < n; b++){
                if(vertexInfo[b][3] == 2){
                    printf("| %d |", b);
                }
            }
            printf("\nLista de nodos brancos: \n");
            for(int b = 0; b < n; b++){
                if(vertexInfo[b][3] == 0){
                    printf("| %d |", b);
                }
            }
            printf("\nQueue:\n");
            for(int x = inicioFila; x < fimFila; x++){
                printf("| %d |", queue[x]);
            }
            run = 0;
        }
        passo += 1;
    }
    
    return 0;
}