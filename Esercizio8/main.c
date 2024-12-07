//pipe tutorial
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

//fd [0] is the read end -> so every process should read from there
//fd [1] is the write end -> so every process should write to there


int main(){
    //we create a pipe
    int fd[2];
    //pipe () returns 0 on success, -1 on failure
    
    if(pipe(fd)==-1){
        printf("an error has accur while opening the pipe\n");
    }
    
    pid_t id = fork();

    if(id ==0){
        close(fd[0]); // we never read from this process
        //we will ask the user in the child process for a number x
        int x=4;
        write(fd[1], &x,sizeof(int));
        close(fd[1]); //we close the write end of the pipe
        //wen we close the write end we tell everybody that is listening that we are finish to write 
        //so the parent process can read from the pipe
        
    }
    else{
        close(fd[1]);
        int y;
        while(read(fd[0],&y,sizeof(int))==0){
            printf("Error on the read\n");
        }
        close(fd[0]);
        printf("we got %d from child\n",y);
        close(fd[0]);
    }

    return 0;
}