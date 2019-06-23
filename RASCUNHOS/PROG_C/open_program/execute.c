/*
#include <stdio.h>


int main(int argc, char *argv[]){

    printf("%d\n",argc);  //argc also ocunts ./prog command
    int i;
    for(i=1; i<argc; i++){
        printf("%s\n",argv[i]);
    }


    return 0;
}
*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* for fork */ /* for execv */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */



int main()
{

    /*Spawn a child to run the program.*/
    pid_t pid=fork();
    if (pid==0) { /* child process */
        static char *argv[]={"echo","Foo is my name.",NULL};
        execv("/bin/echo",argv);
        exit(127); /* only if execv fails */
    }
    else { /* pid!=0; parent process */
        waitpid(pid,0,0); /* wait for child to exit */
    }
    return 0;

}





