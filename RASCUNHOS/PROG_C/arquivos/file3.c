#include <stdio.h>
#include <stdlib.h>


int main(){

    FILE *Arq;
    Arq = fopen("teste.txt","a");
    fprintf(Arq,"hata ");
    fclose(Arq);

    return 0;
}