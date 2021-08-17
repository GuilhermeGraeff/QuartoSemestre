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

int ConcatRot_and_Dest(char *Dest, char *Rot){
    char end[5];
    int MPblock=0;
    end[0]=Rot[0];
    end[1]=Rot[1];
    end[2]=Rot[2];
    end[3]=Dest[0];
    end[4]=Dest[1];
    MPblock=atoi(end);
    MPblock=CovertToDec(MPblock);

    return MPblock;


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
    printf("\nMemoria Cache:\n");
    
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

void VerifyCache(MemP *MainMem, MemC *CacheMem, char *Dest, char *Rot, int *Block, int leitura, char *Desl, int *MissLeitura, int *HitLeitura, int *BlocoCache, int *LinhaCache, int *DeslocamentoCache){
    int cacheBlock=atoi(Dest);
    int CheckIn=0;
    int CountFIFO=0;
    int CacheLine=0;
    int DeslCache=atoi(Desl);
    int CacheLinePrint=0;
    int i= Block;
    
    
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
                }
                
            }
            
            
        
        }
        if(CheckIn==0){
            
            for(int l=0; l<4; l++){
                if(CountFIFO<CacheMem[l].FIFO){
                    CountFIFO=CacheMem[l].FIFO;
                    CacheLine=l;
                }
            }
            
            
            if(leitura==1){
                *HitLeitura+=1;
                *MissLeitura+=1;
            }
            
            if(CacheMem[CacheLine].escrita==1){

            }
            else{
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
                
            }
           
        }
        if(CheckIn==0){
            
            for(int l=4; l<8; l++){
                if(CountFIFO<CacheMem[l].FIFO){
                    CountFIFO=CacheMem[l].FIFO;
                    CacheLine=l;
                }
            }
            
            
            if(leitura==1){
                *HitLeitura+=1;
                *MissLeitura+=1;
            }
            if(CacheMem[CacheLine].escrita==1){

            }
            else{
                 CacheLinePrint=CacheLine;
                 CacheMem[CacheLine].FIFO=0;
                 CacheMem[CacheLine].rotulo=Rot;
                 CacheMem[CacheLine].validade=1;
                 CacheMem[CacheLine].escrita=0;
                 CacheMem[CacheLine].bloco=1;
                 int positionCache=4;
                 for(int k=0; k<4; k++){
                     CacheMem[CacheLine].dados[k]=MainMem[i].dados[k];
                     CacheMem[positionCache].FIFO+=1;
                     positionCache++;
                 }

             }
             
        }
        break;
    }
    *LinhaCache=CacheLinePrint;
       
        

}

void printCacheDado(MemC *CacheMem, int BlocoCache, int LinhaCache, int DeslocamentoCache){
        printf("\nBloco:%d Linha:%d Dado:%d \n", BlocoCache, LinhaCache, CacheMem[LinhaCache].dados[DeslocamentoCache]);
}

void FillTrash(MemC *CacheMem){
    for(int j=0; j<8; j++){
            CacheMem[j].rotulo="2512";
            CacheMem[j].validade=0;
            CacheMem[j].FIFO=1;
            CacheMem[j].escrita=0;
        }
}

void decode(char *endereco ,char *Rotulo, char *Destino, char *blockNumberC, int *blockNumber, char *Deslocamento){

    int numberToConvert;
    
    Rotulo[0]=endereco[0];
    Rotulo[1]=endereco[1];
    Rotulo[2]=endereco[2];      //Desculpa professor mas por algum motivo os For bugavam td
    Rotulo[3]=endereco[3];
    
   
    Destino[0]=endereco[4];
   
    
    Deslocamento[0]= endereco[5];
    Deslocamento[1]= endereco[6];
    
   
    blockNumberC[0]=endereco[0];
    blockNumberC[1]=endereco[1];
    blockNumberC[2]=endereco[2];
    blockNumberC[3]=endereco[3];
    blockNumberC[4]=endereco[4];
    
    
    numberToConvert=atoi(blockNumberC);
    *blockNumber=CovertToDec(numberToConvert);
    
    
    
 
}

void statistics(int MissLeitura, int HitLeitura, int MissEscrita, int HitEscrita){
    printf("\nAbsoluto:\n");
    printf("Leitura: Acertos=%d Faltas=%d\n", HitLeitura, MissLeitura);
    printf("Escrita: Acertos=%d Faltas=%d\n", HitEscrita, MissEscrita);
    printf("Geral: Acertos=%d Faltas=%d\n", HitEscrita+HitLeitura, MissEscrita+MissLeitura);


}

int main(){
    MemP MainMem[32];
    MemC CacheMem[8];
    FillMP(&MainMem);
    FillTrash(&CacheMem);
    //PrintMainMemory(&MainMem);
    //---------------------------------Variaveis--------------------------------//
    char *Dest;
    char *rot;
    
    char endereco[8];
    char teste[8];
    
    char Rotulo[] = "0000";
    char Destino[] = "0";
    char blockNumberC[] = "00000";
    char Deslocamento[] = "00";
    int blockNumber;

        
    
    int option;

    int BlocoCache;
    int LinhaCache;
    int DeslocamentoCache;
    
    
    int MissLeitura=0;
    int HitLeitura=0;
    int MissEscrita=0;
    int HitEscrita=0;

    //--------------------------------------------------------------------------//
    
    for(int i=0; i<8;i++){
        Dest= MainMem[i].destino;
        rot=  MainMem[i].rotulo;
        VerifyCache(&MainMem, &CacheMem, Dest, rot, i, 1, "00",&MissLeitura, &HitLeitura, &BlocoCache, &LinhaCache, &DeslocamentoCache);
        MissLeitura=0;
        HitLeitura=0;
    }
    PrintCache(&CacheMem);
   
   
  
   
    
    for(int finish=0;finish<10;){
        free(&Rotulo);
        free(&Destino);
        free(&blockNumberC);
        free(&Deslocamento);
        free(&blockNumber);
        free(&endereco);
        free(&teste);

        printf("\n----Digite uma opcao----");
        printf("\n1-Leitura 7 bits");
        printf("\n2-Escrita 7 bits");
        printf("\n3-Estatisticas");
        printf("\n4-Sair\n");
        scanf("%d", &option);
   
      
        printf("\n PRIMEIRA VEZ: Rotulo %s Destino %s BlockNumberC %s Deslocamento %s blockNumber %d",Rotulo, Destino, blockNumberC, Deslocamento, blockNumber) ;
        
        
        switch(option){
            case 1:
            
            printf("Endereco:\n");
            scanf("%s", &endereco);
            decode(&endereco, &Rotulo, &Destino, &blockNumberC, &blockNumber, &Deslocamento);
            VerifyCache(&MainMem, &CacheMem, Destino, Rotulo, blockNumber, 1, Deslocamento, &MissLeitura, &HitLeitura, &BlocoCache, &LinhaCache, &DeslocamentoCache);
           // PrintMainMemory(&MainMem);
            PrintCache(&CacheMem);
            printCacheDado(&CacheMem, BlocoCache, LinhaCache, DeslocamentoCache);
            
            printf("\n Segunda VEZ: Rotulo %s Destino %s BlockNumberC %s Deslocamento %s blockNumber %d",Rotulo, Destino, blockNumberC, Deslocamento, blockNumber) ;

            
            
            break;
            
            case 2:
            break;
            
            case 3:
            statistics(MissLeitura, HitLeitura, MissEscrita, HitEscrita);
            break;
            
            case 4:
            finish=10;
            break;
        }
        
       
    }
    
     
   
  
    
}