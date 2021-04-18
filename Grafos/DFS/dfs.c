#include <stdio.h>
#include <stdlib.h>
int main(){
    int **matAdja;
    int **vertexInfo;
    int n,i;
    int *pilha;
    n = 7;
    pilha = malloc(sizeof(int)*10);

    vertexInfo = (int **) malloc(sizeof(int*)*n);	
    for (i=0; i<n;i++){
        vertexInfo[i] = malloc(sizeof(int)*5);
        vertexInfo[i][0] = i;
        vertexInfo[i][1] = -1;
        vertexInfo[i][2] = 0;
        vertexInfo[i][3] = 0;
        vertexInfo[i][4] = 0;
    }

    matAdja = (int **) malloc(sizeof(int*)*n);	
    for (i=0; i<n;i++){
        matAdja[i] = malloc(sizeof(int)*n);
    }

    //Declaration of the adjacent matrix:
    matAdja[0][0] = -1; matAdja[0][1] =  1; matAdja[0][2] = -1; matAdja[0][3] = -1; matAdja[0][4] = -1; matAdja[0][5] = -1; matAdja[0][6] = -1; 
    matAdja[1][0] = -1; matAdja[1][1] = -1; matAdja[1][2] =  1; matAdja[1][3] =  1; matAdja[1][4] = -1; matAdja[1][5] = -1; matAdja[1][6] = -1; 
    matAdja[2][0] = -1; matAdja[2][1] = -1; matAdja[2][2] = -1; matAdja[2][3] = -1; matAdja[2][4] = -1; matAdja[2][5] =  1; matAdja[2][6] =  1; 
    matAdja[3][0] = -1; matAdja[3][1] = -1; matAdja[3][2] = -1; matAdja[3][3] = -1; matAdja[3][4] =  1; matAdja[3][5] = -1; matAdja[3][6] = -1; 
    matAdja[4][0] = -1; matAdja[4][1] = -1; matAdja[4][2] = -1; matAdja[4][3] = -1; matAdja[4][4] = -1; matAdja[4][5] = -1; matAdja[4][6] = -1;
    matAdja[5][0] = -1; matAdja[5][1] = -1; matAdja[5][2] = -1; matAdja[5][3] = -1; matAdja[5][4] = -1; matAdja[5][5] = -1; matAdja[5][6] = -1;
    matAdja[6][0] = -1; matAdja[6][1] = -1; matAdja[6][2] = -1; matAdja[6][3] = -1; matAdja[6][4] = -1; matAdja[6][5] = -1; matAdja[6][6] = -1;

    for(int i = 0; i <10; i++){
        pilha[i] = -1;
    }
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            printf("%d ", matAdja[i][j]);
        }
        printf("\n");
    }
    
    //Tratando o vértice inicial
    pilha[0] = 0;
    vertexInfo[0][3] = 1;
    

    int topo = 0;
    int tamanhoPilhaAux = 0;

    int passo = 1;
    int run = 1;
    while(run == 1){
        printf("\n--------------------------------------------Comeco do ciclo----------------------------------------------");
        printf("\nPasso: %d \n", passo);   
        printf("Pilha: ", passo);  
        for(int k = 0; k<10; k++){
            printf("%d ", pilha[k]);
        }
        printf("\n Nodo     Passo em que foi encontradoodo(cinza)       Passo em que ficou preto       pi     Cor:(0=branco, 1 = cinza, 2 = preto)    \n");
        for(int k = 0; k<n; k++){
            printf("  %d                        %d                                 %d                      %d                  %d\n", vertexInfo[k][0],
            vertexInfo[k][1], vertexInfo[k][4], vertexInfo[k][2],vertexInfo[k][3]);    
        }
        printf("\n");
        tamanhoPilhaAux = 0;
        int verificaSeExisteFilhoDisponivel = 0;
        printf("Topo: %d",topo);
        for(int j = 0; j<n; j++){
            if(matAdja[pilha[topo]][j] > -1 && vertexInfo[j][3] == 0){
                pilha[topo+tamanhoPilhaAux+1] = j;
                vertexInfo[j][3] = 1;
                vertexInfo[j][2] = pilha[topo];
                vertexInfo[j][1] = passo;
                topo++;
                verificaSeExisteFilhoDisponivel = 1;
                break;
            }
        }
        if(verificaSeExisteFilhoDisponivel == 0){
            vertexInfo[pilha[topo]][4] = passo;
            vertexInfo[pilha[topo]][3] = 2;
            topo--;
        }
        if(topo == -1){
            printf("\n\n\n            >>>>>>>>>Esta e a ultima iteracao, abaixo se encontram os resultados:<<<<<<<<<<");
            printf("\n Nodo     Passo em que foi encontradoodo(cinza)       Passo em que ficou preto       pi     Cor:(0=branco, 1 = cinza, 2 = preto)    \n");
            for(int k = 0; k<n; k++){
                printf("  %d                        %d                                 %d                      %d                  %d\n", vertexInfo[k][0],
                vertexInfo[k][1], vertexInfo[k][4], vertexInfo[k][2],vertexInfo[k][3]);    
            }
            run = 0;
        }
        
        //Tratando o vértice inicial
        vertexInfo[0][4] = passo+1;
        passo++;
        printf("\n--------------------------------------------Fim do ciclo--------------------------------------------\n\n\n");    
    }
    return 0;
}