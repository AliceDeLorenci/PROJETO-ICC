// before compiling this program, make an executable out of
// executable.c file:
// gcc executable.c -o exec

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>   /* waitpid() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char txt[] = "This process shall be forked, and child process replaced\n";
	write(1,txt,strlen(txt));

	pid_t pid=fork();
	if(pid==0)  //child process
	{
		char *const argv[] = {"./exec",NULL};
		execv("./exec",argv);
		printf("If this is message is printed, an error ocurred\n");
	}
	else  //parent process
	{
		waitpid(pid,0,0); /* wait for child to exit */
		printf("PARENT PROCESS HERE\n");
	}
	
	return 0;
}
