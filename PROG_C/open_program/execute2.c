#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

	 

     pid_t pid;   //variable capable of storing process id
     char *const parmList[] = {"/bin/ls", "-l", NULL};

     if ((pid = fork()) == -1)
        perror("fork error");
     else if (pid == 0) {
        execv("/bin/ls", parmList);
        printf("Return not expected. Must be an execv error.n");
     }


	return 0;
}

