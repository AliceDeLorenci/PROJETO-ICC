/*******************************************************************************************************

FORKING A PROGRAM
This consists in creating a child process, which is basically a duplicate of the parent program

https://stackoverflow.com/questions/5460421/how-do-you-write-a-c-program-to-execute-another-program
https://www.geeksforgeeks.org/fork-system-call/   - BEST TUTORIAL
http://man7.org/linux/man-pages/man2/fork.2.html
http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/create.html

********************************************************************************************************/

#include <unistd.h>  // fork()
#include <stdio.h>
#include <sys/types.h>  // pid_t  -> variable type of a process ID
#include <string.h>


#define   MAX_COUNT  200
#define   BUF_SIZE   100

int main(){

    pid_t pid;
    int    i;
    char   buf[BUF_SIZE];

    fork();  // creating child program  -> duplicating program
             // both processes have identical but separate address spaces
             // therefore one doesn't interfere with the other 

    /* the code bellow shall be executed by both the child and parent process */

    pid = getpid();  //gets process id

    for (i = 1; i <= MAX_COUNT; i++) {
          sprintf(buf, "This line is from pid %d, value = %d\n", pid, i);
          write(1, buf, strlen(buf)); 
     } 


    return 0;

}