#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/*
int main(){
    char busca[100];

    FILE *Arq;
    Arq = fopen("eof.txt","a");
    if(Arq == NULL){
        printf ("\n\nErro no arquivo!\n\n"); 
        exit(0);
    }

    while(feof(Arq)==0){  
        while(busca[0] != '#'  && feof(Arq)==0 ){
            fscanf(Arq,"%s",busca);
        }  //para quando for '#'
        printf("%c",busca[1]);  
    }
}*/

int main() { 
    FILE *ArqIn; 
    char caracter;  
    if  ( (ArqIn=fopen("./eof.txt","r")) != 0 )  {                                                 
        while ( feof(ArqIn) == 0 )                                                 
        {                                                           
            fscanf(ArqIn,"%c",&caracter);
            if(caracter == '1'){
                int num;
                num = (int)caracter;   //pega o correspondente na tabela ascii
                printf("%d",num);
            }                                                           
            printf("%c",caracter);                                                  
        }        
        fclose(ArqIn);                                             
    }                                             
    else  printf ("Erro na leitura do arquivo de entrada!");
    return 0;
}