#include <stdio.h>
#include <stdlib.h>

//  sprintf (<string_pointer>, "text <%type> text", variable);
//  sscanf (<string_pointer>, "<%type> <%type>", variable1, variable2);

int main(){

    int a = 4, b = 10;
    char string[20], ch;
    sprintf(string,"Olá %d de novo %d",a,b);
    sscanf(string,"%c",&ch);
    printf("%c",ch);


    return 0;
}