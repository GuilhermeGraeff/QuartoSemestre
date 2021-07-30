#include <stdio.h>
#include <string.h>
#include<math.h>

typedef struct
{
    int dados[4];
    char *destino;
    char *rotulo;
    char *deslocamento[4];                      
}MemP;

typedef struct{
    int dados[4];
    char *rotulo; 
    int validade;
    int escrita;
    int FIFO;
    int bloco;

}MemC;


int CovertToDec(int Binary){
    int decimal=0;
    
    for(int i=0; Binary>0; i++){
        decimal = decimal + pow(2,i)*(Binary % 10);
        Binary = Binary / 10;
       
    }
    
    return decimal;
}

void FillMP(MemP *MainMem){
    int DadosValue=1;
    int CountBinary=0;
    int Binary2=0;
    int Binary3=2;

    for(int i=0; i<32; i++){
        for(int j=0; j<4; j++){
            MainMem[i].dados[j]=DadosValue;
            DadosValue++;
            switch(j){
                case 0 :
                MainMem[i].deslocamento[j]="00";
                break;

                case 1 :
                MainMem[i].deslocamento[j]="01";
                break;

                case 2 :
                MainMem[i].deslocamento[j]="10";
                break;

                case 3 :
                MainMem[i].deslocamento[j]="11";
                break;
            }
        }
        if(Binary2==2){
            Binary2=0;
        }
        switch(Binary2){
                case 0 :
                MainMem[i].destino="0";
                break;

                case 1 :
                MainMem[i].destino="1";
                break;  
            }
        
        if(CountBinary==2){
            Binary3+=2;
            CountBinary=0;
        }
        switch(Binary3){
            case 2:
            MainMem[i].rotulo="0000";
            break;

            case 4:
            MainMem[i].rotulo="0001";
            break;

            case 6:
            MainMem[i].rotulo="0010";
            break;

            case 8:
            MainMem[i].rotulo="0011";
            break;

            case 10:
            MainMem[i].rotulo="0100";
            break;

            case 12:
            MainMem[i].rotulo="0101";
            break;

            case 14:
            MainMem[i].rotulo="0110";
            break;

            case 16:
            MainMem[i].rotulo="0111";
            break;

            case 18:
            MainMem[i].rotulo="1000";
            break;

            case 20:
            MainMem[i].rotulo="1001";
            break;

            case 22:
            MainMem[i].rotulo="1010";
            break;

            case 24:
            MainMem[i].rotulo="1011";
            break;

            case 26:
            MainMem[i].rotulo="1100";
            break;

            case 28:
            MainMem[i].rotulo="1101";
            break;

            case 30:
            MainMem[i].rotulo="1110";
            break;

            case 32:
            MainMem[i].rotulo="1111";
            break;
        }
        
        
        CountBinary++;
        Binary2++;
       
       
    }
    

    
}

PrintMainMemory(MemP *MainMem){
    
    printf("--------------------------Memoria Principal--------------------------");
    
    for(int i=0; i<32 ;i++){
        printf("\n------------Bloco %d------------", i);
        for(int j=0; j<4; j++){
            printf("\n|endereco:%s%s%s Dados:%d    |", MainMem[i].rotulo,MainMem[i].destino,MainMem[i].deslocamento[j], MainMem[i].dados[j]);
        }
    }
    printf("\n---------------------------------------------------------------------------");
}                                     

void PrintCache(MemC *CacheMem){
    printf("\n\n\nMemoria Cache:\n");
    
    for(int i=0; i<8; i++){
        switch(i){
            case 0:
            printf("Bloco 0:\n");
            printf("------------------------------------------------------------------------");
            break;

            case 4:
            printf("\nBloco 1:\n");
            printf("------------------------------------------------------------------------");
            break;
        
        }
    
        printf("\nLinha:%d|",i);
        if(i<4){
            if(CacheMem[i].FIFO==4){
                printf("Escrita:%d |Validade:%d |Fifo: %d|Rotulo: %s |Dados: %d,%d,%d,%d|Proximo a ser substituido\n", CacheMem[i].escrita, CacheMem[i].validade, CacheMem[i].FIFO, CacheMem[i].rotulo, CacheMem[i].dados[0],CacheMem[i].dados[1],CacheMem[i].dados[2],CacheMem[i].dados[3]);
                printf("------------------------------------------------------------------------");
            }
            else{
                printf("Escrita:%d |Validade:%d |Fifo: %d|Rotulo: %s |Dados: %d,%d,%d,%d|\n", CacheMem[i].escrita, CacheMem[i].validade, CacheMem[i].FIFO, CacheMem[i].rotulo, CacheMem[i].dados[0],CacheMem[i].dados[1],CacheMem[i].dados[2],CacheMem[i].dados[3]);
                printf("------------------------------------------------------------------------");
            }
           
        }
        else{
            if(CacheMem[i].FIFO==4){
                printf("Escrita:%d |Validade:%d |Fifo: %d|Rotulo: %s |Dados: %d,%d,%d,%d|Proximo a ser substituido\n", CacheMem[i].escrita, CacheMem[i].validade, CacheMem[i].FIFO, CacheMem[i].rotulo, CacheMem[i].dados[0],CacheMem[i].dados[1],CacheMem[i].dados[2],CacheMem[i].dados[3]);
                printf("------------------------------------------------------------------------");
            }
            else{
                printf("Escrita:%d |Validade:%d |Fifo: %d|Rotulo: %s |Dados: %d,%d,%d,%d|\n", CacheMem[i].escrita, CacheMem[i].validade, CacheMem[i].FIFO, CacheMem[i].rotulo, CacheMem[i].dados[0],CacheMem[i].dados[1],CacheMem[i].dados[2],CacheMem[i].dados[3]);
                printf("------------------------------------------------------------------------");
            }
        }
    }
}

void VerifyCache(MemP *MainMem, MemC *CacheMem, char *Dest, char *Rot, int i, int leitura, char *Desl, int *MissLeitura, int *HitLeitura, int *BlocoCache, int *LinhaCache, int *DeslocamentoCache, int write, int dado, int *MissEscrita, int *HitEscrita, int *tava){
    int cacheBlock=atoi(Dest);
    int CheckIn=0;
    int CountFIFO=0;
    int CacheLine=0;
    int DeslCache=atoi(Desl);
    int CacheLinePrint=0;
    char BlockMN[]="00000";
    int BlockConvert;
    
    *tava=0;
    
    DeslCache=CovertToDec(DeslCache);
    *DeslocamentoCache= DeslCache;
    *BlocoCache= cacheBlock;
    
    switch(cacheBlock){
        
        case 0:
        for(int j=0;j<4;j++){
            if(strcmp(Rot, CacheMem[j].rotulo)==0){
                CacheLinePrint=j;
                j=4;
                CheckIn=1;
                if(leitura==1){
                    *HitLeitura+=1;
                    *tava=1;
                }          
            }
            if(CountFIFO<CacheMem[j].FIFO){
                CountFIFO=CacheMem[j].FIFO;
                CacheLine=j;
            }
        }
        if (CheckIn==0 && leitura==1){
            *MissLeitura+=1;
            *HitLeitura+=1;
        }
        if(CheckIn==1 && write==1){
            CacheMem[CacheLinePrint].dados[DeslCache]= dado;
            CacheMem[CacheLinePrint].escrita=1;
            *HitEscrita+=1;
        }
        if(CheckIn==0 && write==1){
            leitura=1;
            *HitEscrita+=1;
            *MissEscrita+=1;
        }
        
        if(CheckIn==0 && leitura==1){
            
            if(CacheMem[CacheLine].escrita==1){
                BlockMN[0]=CacheMem[CacheLine].rotulo[0];
                BlockMN[1]=CacheMem[CacheLine].rotulo[1];
                BlockMN[2]=CacheMem[CacheLine].rotulo[2];
                BlockMN[3]=CacheMem[CacheLine].rotulo[3];
                BlockMN[4]=Dest[0];
                BlockConvert=atoi(BlockMN);
                BlockConvert=CovertToDec(BlockConvert);
                for(int k=0; k<4; k++){
                    MainMem[BlockConvert].dados[k]=CacheMem[CacheLine].dados[k];
                }

            }
            CacheLinePrint=CacheLine;
            CacheMem[CacheLine].FIFO=0;
            CacheMem[CacheLine].rotulo=Rot;
            CacheMem[CacheLine].validade=1;
            CacheMem[CacheLine].escrita=0;
            CacheMem[CacheLine].bloco=0;
            for(int k=0; k<4; k++){
                CacheMem[CacheLine].dados[k]=MainMem[i].dados[k];
                CacheMem[k].FIFO+=1;
            }
           
            if(write==1){
                CacheMem[CacheLinePrint].dados[DeslCache]= dado;
                CacheMem[CacheLinePrint].escrita=1;
            }
             
             
        }
        break;
        
        case 1:
        for(int j=4;j<8;j++){
            if(strcmp(Rot, CacheMem[j].rotulo)==0){
                CacheLinePrint=j;
                j=8;
                CheckIn=1;
                if(leitura==1){
                    *HitLeitura+=1;
                }
                else{
                    *HitEscrita+=1;
                }
                
            }
            if(CountFIFO<CacheMem[j].FIFO){
                CountFIFO=CacheMem[j].FIFO;
                CacheLine=j;
            }
        
        }
        if (CheckIn==0 && leitura==1){
            *MissLeitura+=1;
            *HitLeitura+=1;
        }
        
      
        
        if(CheckIn==1 && write==1){
            CacheMem[CacheLinePrint].dados[DeslCache]= dado;
            CacheMem[CacheLinePrint].escrita=1;
            *HitEscrita+=1;
        }
        if(CheckIn==0 && write==1){
            leitura=1;
            *HitLeitura+=1;
            *MissLeitura+=1;
        }
        
        if(CheckIn==0 && leitura==1){
            
            if(CacheMem[CacheLine].escrita==1){
                BlockMN[0]=CacheMem[CacheLine].rotulo[0];
                BlockMN[1]=CacheMem[CacheLine].rotulo[1];
                BlockMN[2]=CacheMem[CacheLine].rotulo[2];
                BlockMN[3]=CacheMem[CacheLine].rotulo[3];
                BlockMN[4]=Dest[0];
                BlockConvert=atoi(BlockMN);
                BlockConvert=CovertToDec(BlockConvert);
                for(int k=0; k<4; k++){
                    MainMem[BlockConvert].dados[k]=CacheMem[CacheLine].dados[k];
                }

            }
            CacheLinePrint=CacheLine;
            CacheMem[CacheLine].FIFO=0;
            CacheMem[CacheLine].rotulo=Rot;
            CacheMem[CacheLine].validade=1;
            CacheMem[CacheLine].escrita=0;
            CacheMem[CacheLine].bloco=0;
            int positionCache=4; 
            for(int k=0; k<4; k++){
                CacheMem[CacheLine].dados[k]=MainMem[i].dados[k];
                CacheMem[positionCache].FIFO+=1;
                positionCache++;
            }
           
            if(write==1){
                CacheMem[CacheLinePrint].dados[DeslCache]= dado;
                CacheMem[CacheLinePrint].escrita=1;
            }
             
             
        }
        break;
    }
    *LinhaCache=CacheLinePrint;
       
        

}

void printCacheDado(MemC *CacheMem, int BlocoCache, int LinhaCache, int DeslocamentoCache, int BlocoMain, int tava){
        if (tava==1){
            printf("\nEstava na cache");
            printf("\nBloco na principal:%d Bloco na Cache:%d Linha na Cache:%d Dado:%d \n", BlocoMain ,BlocoCache, LinhaCache, CacheMem[LinhaCache].dados[DeslocamentoCache]);
        }
        else{
            printf("\nNao Estava na cache");
            printf("\nBloco na principal:%d Bloco na Cache:%d Linha na Cache:%d Dado:%d \n", BlocoMain ,BlocoCache, LinhaCache, CacheMem[LinhaCache].dados[DeslocamentoCache]);

        }
}

void decode(char *endereco, char *blockNumberC, int *blockNumber){

    int numberToConvert;
    
    blockNumberC[0]=endereco[0];
    blockNumberC[1]=endereco[1];
    blockNumberC[2]=endereco[2];
    blockNumberC[3]=endereco[3];
    blockNumberC[4]=endereco[4];
    
    
    numberToConvert=atoi(blockNumberC);
    *blockNumber=CovertToDec(numberToConvert);
    
    
    
 
}


void FillTrash(MemC *CacheMem){
    for(int j=0; j<8; j++){
            CacheMem[j].rotulo="2512";
            CacheMem[j].validade=0;
            CacheMem[j].FIFO=1;
            CacheMem[j].escrita=0;
        }
}

void statistics(float MissLeitura, float HitLeitura, float MissEscrita, float HitEscrita){
    int a= (int)MissLeitura;
    int b= (int)HitLeitura;
    int c= (int)HitEscrita;
    int d= (int)MissEscrita;
    
    printf("\nAbsoluto:\n");
    printf("Leitura: Acertos=%d Faltas=%d\n", b, a);
    printf("Escrita: Acertos=%d Faltas=%d\n", c, d);
    printf("Geral: Acertos=%d Faltas=%d\n", c+b, a+d);

    
    
    printf("\nPercentual:\n");
    if(HitLeitura==0){
        printf("Leitura 0%% de acertos\n");
    }
    else{
        printf("Leitura %.2f%% de acertos\n", ((HitLeitura-MissLeitura)/HitLeitura)*100);
    }
    if(HitEscrita==0){
        printf("Escrita 0%% de acertos\n");
    }
    else{
        printf("Escrita %2.f%% de acertos\n", (HitEscrita-MissEscrita)/HitEscrita*100);
    }
    if(HitLeitura==0 || HitEscrita==0){
        printf("Geral 0%% de acertos\n");
    }
    else{
        printf("Geral: %.2f%% de acertos\n", ((HitEscrita+HitLeitura-MissEscrita-MissLeitura)/(HitEscrita+HitLeitura))*100);

    }


}

int main(){
    MemP MainMem[32];
    MemC CacheMem[8];
    FillMP(&MainMem);
    FillTrash(&CacheMem);
    PrintMainMemory(&MainMem);
    //---------------------------------Variaveis--------------------------------//
    char *Dest;
    char *rot;
    char* endereco;
    
    char blockNumberC[]="00000";
    char Deslocamento[]="00";
    int blockNumber;
    int option=1;

    int BlocoCache;
    int LinhaCache;
    int DeslocamentoCache=1;
    int Dados;
    int Tava;
    
    int MissLeitura=0;
    int HitLeitura=0;
    int MissEscrita=0;
    int HitEscrita=0;

    //--------------------------------------------------------------------------//
    
    for(int i=0; i<8;i++){
        Dest= MainMem[i].destino;
        rot=  MainMem[i].rotulo;
        VerifyCache(&MainMem, &CacheMem, Dest, rot, i, 1, "00",&MissLeitura, &HitLeitura, &BlocoCache, &LinhaCache, &DeslocamentoCache, 0, 0, &MissEscrita, &HitEscrita, &Tava);
        MissLeitura=0;
        HitLeitura=0;
    }
    PrintCache(&CacheMem);
   
    
    PrintMainMemory(&MainMem);
    PrintCache(&CacheMem);
    
   
    VerifyCache(&MainMem, &CacheMem, "0", "0111", 14, 1, "11",&MissLeitura, &HitLeitura, &BlocoCache, &LinhaCache, &DeslocamentoCache, 0, 0, &MissEscrita, &HitEscrita, &Tava);
    PrintCache(&CacheMem);
    VerifyCache(&MainMem, &CacheMem, "0", "1111", 30, 1, "10",&MissLeitura, &HitLeitura, &BlocoCache, &LinhaCache, &DeslocamentoCache, 0, 0, &MissEscrita, &HitEscrita, &Tava);
    PrintCache(&CacheMem);
    VerifyCache(&MainMem, &CacheMem, "0", "1000", 16, 1, "01",&MissLeitura, &HitLeitura, &BlocoCache, &LinhaCache, &DeslocamentoCache, 0, 0, &MissEscrita, &HitEscrita, &Tava);
    PrintCache(&CacheMem);
    VerifyCache(&MainMem, &CacheMem, "1", "0101", 11, 1, "10",&MissLeitura, &HitLeitura, &BlocoCache, &LinhaCache, &DeslocamentoCache, 0, 0, &MissEscrita, &HitEscrita, &Tava);
    PrintCache(&CacheMem);
    VerifyCache(&MainMem, &CacheMem, "1", "1111", 31, 1, "00",&MissLeitura, &HitLeitura, &BlocoCache, &LinhaCache, &DeslocamentoCache, 0, 0, &MissEscrita, &HitEscrita, &Tava);
    PrintCache(&CacheMem);
    VerifyCache(&MainMem, &CacheMem, "0", "1010", 20, 1, "01",&MissLeitura, &HitLeitura, &BlocoCache, &LinhaCache, &DeslocamentoCache, 0, 0, &MissEscrita, &HitEscrita, &Tava);
    PrintCache(&CacheMem);
    VerifyCache(&MainMem, &CacheMem, "1", "0000", 1, 1, "10",&MissLeitura, &HitLeitura, &BlocoCache, &LinhaCache, &DeslocamentoCache, 0, 0, &MissEscrita, &HitEscrita, &Tava);
    PrintCache(&CacheMem);

    // while(option!=4){
    //     printf("\n--------Digite---------\n");
    //     printf("1-Leitura\n");
    //     printf("2-Escrita\n");
    //     printf("3-Estatisticas\n");
    //     printf("4-Sair\n");        
    //     scanf("%d", &option);
        
    //     switch(option){
    //         case 1:
    //         printf("Digite:\n");
    //         printf("1- Exemplo: Leitura 1111011\n");
    //         printf("2- Exemplo: Leitura 0011011\n");
    //         printf("3- Exemplo: Leitura 0101101\n");
    //         scanf("%d",&option);
    //         switch(option){
    //             case 1:
    //                 endereco="1111011";
    //                 decode(endereco, blockNumberC, &blockNumber);
    //                 VerifyCache(&MainMem, &CacheMem, "0", "1111", 30, 1, "11",&MissLeitura, &HitLeitura, &BlocoCache, &LinhaCache, &DeslocamentoCache, 0, 0, &MissEscrita, &HitEscrita, &Tava);
    //                 PrintMainMemory(&MainMem);
    //                 PrintCache(&CacheMem);
    //                 printCacheDado(&CacheMem, BlocoCache, LinhaCache, DeslocamentoCache, blockNumber, Tava);
    //             break;
    //             case 2:
    //                 endereco="0011011";
    //                 decode(endereco, blockNumberC, &blockNumber);
    //                 VerifyCache(&MainMem, &CacheMem, "0", "0011", 6, 1, "11",&MissLeitura, &HitLeitura, &BlocoCache, &LinhaCache, &DeslocamentoCache, 0, 0, &MissEscrita, &HitEscrita, &Tava);
    //                 PrintMainMemory(&MainMem);
    //                 PrintCache(&CacheMem);
    //                 printCacheDado(&CacheMem, BlocoCache, LinhaCache, DeslocamentoCache, blockNumber, Tava);
    //             break;
    //             case 3:
    //                 endereco="0101101";
    //                 decode(endereco, blockNumberC, &blockNumber);
    //                 VerifyCache(&MainMem, &CacheMem, "1", "0101", 11, 1, "01",&MissLeitura, &HitLeitura, &BlocoCache, &LinhaCache, &DeslocamentoCache, 0, 0, &MissEscrita, &HitEscrita, &Tava);
    //                 PrintMainMemory(&MainMem);
    //                 PrintCache(&CacheMem);
    //                 printCacheDado(&CacheMem, BlocoCache, LinhaCache, DeslocamentoCache, blockNumber, Tava);
    //         }
    //         break;
    //         case 2:
    //         printf("Digite:\n");
    //         printf("1- Exemplo: Escrita 0000000 Dado:200\n");
    //         printf("2- Exemplo: Escrita 0111011 Dado:99\n");
    //         printf("3- Exemplo: Escrita 0101101 Dado:28\n");
    //         scanf("%d",&option);
    //         switch(option){
    //             case 1:
    //                 endereco="0000000";
    //                 decode(endereco, blockNumberC, &blockNumber);
    //                 VerifyCache(&MainMem, &CacheMem, "0", "0000", 0, 0, "00",&MissLeitura, &HitLeitura, &BlocoCache, &LinhaCache, &DeslocamentoCache, 1, 200, &MissEscrita, &HitEscrita, &Tava);
    //                 PrintMainMemory(&MainMem);
    //                 PrintCache(&CacheMem);
    //                 printCacheDado(&CacheMem, BlocoCache, LinhaCache, DeslocamentoCache, blockNumber, Tava);
    //             break;
    //             case 2:
    //                 endereco="0111011";
    //                 decode(endereco, blockNumberC, &blockNumber);
    //                 VerifyCache(&MainMem, &CacheMem, "0", "0111", 14, 0, "11",&MissLeitura, &HitLeitura, &BlocoCache, &LinhaCache, &DeslocamentoCache, 1, 99, &MissEscrita, &HitEscrita, &Tava);
    //                 PrintMainMemory(&MainMem);
    //                 PrintCache(&CacheMem);
    //                 printCacheDado(&CacheMem, BlocoCache, LinhaCache, DeslocamentoCache, blockNumber, Tava);
    //             break;
    //             case 3:
    //                 endereco="0101101";
    //                 decode(endereco, blockNumberC, &blockNumber);
    //                 VerifyCache(&MainMem, &CacheMem, "1", "0101", 11, 0, "01",&MissLeitura, &HitLeitura, &BlocoCache, &LinhaCache, &DeslocamentoCache, 1, 28, &MissEscrita, &HitEscrita, &Tava);
    //                 PrintMainMemory(&MainMem);
    //                 PrintCache(&CacheMem);
    //                 printCacheDado(&CacheMem, BlocoCache, LinhaCache, DeslocamentoCache, blockNumber, Tava);
    //         }
    //         break;
    //         case 3:
    //         statistics(MissLeitura, HitLeitura, MissEscrita, HitEscrita);
    //         break;
    //     }
    // }

   
   
    
  
    
}