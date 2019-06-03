#include <stdio.h>

#define file "arduino_arq.ino"

int main(){
	FILE *Arq;
	Arq = fopen(file,"w");
	fprintf(Arq,"teste");
	fclose(Arq);

	return 0;
}

