/*
● Tipo di file -> ls -l filename
● Permessi
● ID number del proprietario del file
● Dimensione del file (se regolare)
*/

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void exit_para(){
    printf("Error on the handling of the signal\n");
}

void exit_handler(int sig){
    printf("Signal %d received\n", sig);
    printf("that file dosn't exist\n");
}

int main(int argc, char *argv[]) {
    
    if(argc!=2){
        printf("Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    pid_t pid;
    char *filename = argv[1];

    pid = fork();
    if(pid>0)
        signal(SIGCHLD,exit_handler);
    if(pid==0){
        // Child process
        execl("/bin/ls","ls","-l",filename,NULL);
        printf("Error on the execution of the command\n");
        _exit(-1);
        kill(getpid(),SIGCHLD);
    }

    wait(NULL);
    
    printf("the file %s is a file\n", filename);


}