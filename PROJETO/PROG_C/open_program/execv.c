/****************************************************************************************************************

USING EXEC
Replaces current program or copy with the new program

https://stackoverflow.com/questions/5460421/how-do-you-write-a-c-program-to-execute-another-program
http://man7.org/linux/man-pages/man3/exec.3.html
https://www.geeksforgeeks.org/exec-family-of-functions-in-c/

*****************************************************************************************************************/

#include <unistd.h>  /* fork() */ /* execv() */
#include <sys/types.h>  /* pid_t */
#include <stdio.h>
#include <string.h>

int main(){

	write(1,"Replacement beginning in 3... 2... ",strlen("Replacement beginning in 3... 2... "));
	
	//Why text wasn't being printed using printf() ?
	//Probably because of buffering

	char *args[] = {"./replace",NULL};  //arguments that will be passed to new program
										//must begin with EXECULTABLE name
										//must end with NULL

	execv("./replace",args);

	printf("hahahahaha");  //note this will be ignored, as the process was replaced

	return 0;
}
