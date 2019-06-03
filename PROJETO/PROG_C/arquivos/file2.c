#include <stdio.h>

#define filepath "./PASTA/dados.txt"

/*****************************************************
 * FILE *arqptr;
 * arqptr = fopen(<nome_arquivo> , <mode_abertura>);
 * 
 * MODO DE ABERTURA:
 * r : read
 * w : write
 * r+ : read and write
 * w+ : read and write / creates
 * a : writes at end / creates
 * a+ : writes at end and reads /creates
******************************************************/

int main(){
    char s[50];

    FILE *Arq;
    Arq = fopen(filepath,"a+");
/*
    scanf("%s",s);
    fprintf(Arq,"%s\t",s);
*/
    while(!feof(Arq)){  //while doesn't reach EOF
        fscanf(Arq,"%s",s);
        printf("%s ",s);
    }

    fclose(Arq);


    return 0;
}