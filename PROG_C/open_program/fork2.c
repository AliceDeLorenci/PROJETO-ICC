#include <unistd.h>  /* fork() */ 
#include <sys/types.h>  /* pid_t */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define   MAX_COUNT  200
#define   BUF_SIZE   100

int main(){

    int    i;
    char   buf[BUF_SIZE];

    pid_t pid = fork();  //getting ID of child process

    printf("Child process ID: %d\n",pid);   //child process shall return as 0
                                            //parent process shall return child process id

    pid = getpid();

    for (i = 1; i <= MAX_COUNT; i++) {
          sprintf(buf, "This line is from pid %d, value = %d\n", pid, i);
          write(1, buf, strlen(buf)); 
     } 


    return 0;

}

