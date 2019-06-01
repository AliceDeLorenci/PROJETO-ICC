#include <stdio.h>
#include <stdlib.h>
#include <string.h>




// Recebe vetores a[1..m] e b[1..n] com m >= 1 e n >= 0
// e devolve o número de ocorrências de a em b.

int trivial (char a[], int m, char b[], int n) 
{
   int i, j, k, ocorre = 0;
   m = m-1;
   n = n-1;
   for (k = m; k <= n; k++) {
      int temp = 0;
      for (i = m, j = k; i >= 0; i--, j--){
         if (a[i] != b[j]) {
            temp = 1;
            break;
         }
      }
      if (temp == 0) 
         ocorre++;
   }
   return ocorre;
}


int main(){
   int m, n, ocorre;
   m = 5;
   n = 15;
   char a[] = "hello";
   char b[] = "hellohellohello";
   ocorre = trivial (a, m, b, n);
   printf("%d %ld %ld",ocorre,strlen(a),strlen(b));

}