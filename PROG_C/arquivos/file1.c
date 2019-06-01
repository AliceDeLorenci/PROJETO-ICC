#include <stdio.h>

#define filepath "./PASTA/dados.txt"

int main(){

#ifdef PRINT
    char a[] = "Hello File!\n";
    FILE *Arquivo;

    Arquivo = fopen(filepath,"wt");

    if(Arquivo == NULL){
        printf("ERROR\n");
    }

    fprintf(Arquivo,"%s",a);
    //fprintf works just like printf(), but
    //you need to specify de file

    fclose(Arquivo);
#endif

#ifdef SCAN
    char s[20];
    FILE *Arquivo;

    Arquivo = fopen(filepath,"rt");

    if(Arquivo == NULL){
        printf("ERROR\n");
    }

    fgets(s,20,Arquivo);
    /******************
    fscanf(Arquivo,"%s",s);
    *******************/
    fclose(Arquivo);

    printf("%s",s);
#endif

    return 0;

}
