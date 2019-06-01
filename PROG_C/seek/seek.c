#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define file "./teste.txt"

int main(){

    FILE *Arq;
    Arq = fopen(file,"a+");

    //fseek(FILE *pointer, long int offset, int position)
    //pointer: pointer to a FILE object that identifies the stream.
    //offset: number of bytes to offset from position
    //position: position from where offset is added.

    //moving pointer to end
    fseek(Arq, -30, SEEK_END); 

    //SEEK_END : It denotes end of the file.
    //SEEK_SET : It denotes starting of the file.
    //SEEK_CUR : It denotes file pointer’s current position.

    //printing position of pointer
    printf("%ld", ftell(Arq)); 

    char busca[20];
    fscanf(Arq,"%s",busca);
    printf("%s",busca);

    fprintf(Arq,"HERE!");  //writes at end of file

    fclose(Arq);

    return 0;
}


