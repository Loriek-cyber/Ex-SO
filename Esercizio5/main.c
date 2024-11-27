#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>


void exit1(){
    char *msg = "Child process terminated";
    write(2,msg,sizeof(msg));
}
void exit2(){
    char *msg = "Child process terminated";
    write(2,msg,sizeof(msg));
}


int main(int argc, char *argv[]) {
    atexit(exit1);
    printf("Prima");
    pid_t pid = fork();
    if(pid==0){
        atexit(exit2);
        printf("Child process\n");
        _exit(-1);
    }
    wait(NULL);
    printf("Dopo\n");
    _exit(0);
}