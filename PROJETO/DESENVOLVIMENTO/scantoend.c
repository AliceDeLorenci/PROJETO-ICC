#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(){

    int dia[8] = {0,0,0,0,0,0,0,0};
    int tecla;

    while((scanf("%d",&tecla))>0){  //enquanto houver entrada...
            dia[tecla] = 1;  //posicao no vetor correspondente ao dia escolhido
            //getchar();
        }
    int i;
    for(i=0; i<8; i++){
        printf("%d ",dia[i]);
    }
    printf("\n");

    return 0;
}